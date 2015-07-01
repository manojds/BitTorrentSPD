//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "BTSPDConnTracker.h"
#include "BTSPDCommonMsgTypes.h"
#include "BTSPDConnTrack_m.h"
#include <string.h>
#include <sstream>
#include <fstream>
#include "../BitTorrent/BTLogImpl.h"

Define_Module(BTSPDConnTracker);

#define WRITE_CONN_MAP_TO_FILE_MSG_TYPE     2001

using namespace std;

BTSPDConnTracker::BTSPDConnTracker():
        i_LastConnDumpFileIndex(0),
        evt_DumpToFile(NULL)
{

}

BTSPDConnTracker::~BTSPDConnTracker()
{
    if(evt_DumpToFile != NULL )
        cancelAndDelete(evt_DumpToFile);
}

void BTSPDConnTracker::initialize()
{
    BT_LOG_INFO(btLogSinker, " BTSPDConnTracker::initialize","initializing.....\n");

    i_DumpingInterval = par("dumpingInterval");
    s_FileName = par("OutPutFile").stringValue();

    b_enableConnMapDumping = par("enableConnMapDumping");


    constructTerminalNameMapping();

    if(b_enableConnMapDumping)
    {
        evt_DumpToFile = new cMessage("WRITE_CONN_MAP_TO_FILE_MSG_TYPE", WRITE_CONN_MAP_TO_FILE_MSG_TYPE);
        scheduleAt(simTime()+i_DumpingInterval, evt_DumpToFile);
    }
}

void BTSPDConnTracker::constructTerminalNameMapping()
{
    int iTerminalTypeCount = par("terminalTypeCount");

    for (int i = 0; i < iTerminalTypeCount; ++i)
    {
        stringstream strm;
        strm<< "overlayTerminal"<<i;
        string sParName = strm.str();

        strm.str("");
        strm<< "overlayTerminal-"<<i;
        string sActualName = strm.str();

        string sTerminalType = par(sParName.c_str()).stringValue();
        map_TerminalNames[sActualName] = sTerminalType;
    }
}

void BTSPDConnTracker::finish()
{
    time_t timer;
    time(&timer);

    char pFullFileName[256];

    struct timeb tbNow;
    char szNow[128];

    ftime(&tbNow);
    strftime(szNow, sizeof (szNow), "%m%d_%H%M%S", localtime(&tbNow.time));


#ifndef WINNT
snprintf(pFullFileName, 256,"%s_%s.txt", s_FileName.c_str(), szNow);
#else
_snprintf(pFullFileName, 256,"%s_%s.txt", s_FileName.c_str(), szNow);
#endif /* WINNT */

    dumpConnMapToFile(map_AllConnections, pFullFileName);
}

void BTSPDConnTracker::handleMessage(cMessage *msg)
{
    if( msg->isSelfMessage() )
    {
        handleSelfMessage(msg);
    }
    else
    {
        if (msg->getKind() == BTSPD_CONN_TRACK_NODE_CREATION_MSG_TYPE)
        {
            handleNewNodeCreationMsg(msg);
        }
        else if (msg->getKind() == BTSPD_CONN_TRACK_NEWCONN_MSG_TYPE  )
        {
            handleNewConnectionMsg(msg);
        }
        else if (msg->getKind() == BTSPD_CONN_TRACK_CONN_DROP_MSG_TYPE  )
        {
            handleConnectionLostMsg(msg);
        }
        else if (msg->getKind() == BTSPD_CONN_TRACK_CONN_DWL_COMPLETE_MSG_TYPE  )
        {
            handleDwlCompleteMsg(msg);
        }
        else
        {
            throw cRuntimeError("BTSPDConnTrackerFunc::handleMessage - Unknown Message received. kind [%d] name [%s]",
                    msg->getKind(),msg->getName() );
        }
        delete msg;
    }
}

void BTSPDConnTracker::handleSelfMessage(cMessage* msg)
{
    if (msg->getKind() == WRITE_CONN_MAP_TO_FILE_MSG_TYPE)
    {
        dumpConnectionsToFile();
        scheduleAt(simTime() + i_DumpingInterval, msg);
    }
    else
    {
        throw cRuntimeError("BTSPDConnTrackerFunc::handleSelfMessage - Unknown Message received. kind [%d] name [%s]",
                msg->getKind(),msg->getName() );
    }

}

void BTSPDConnTracker::dumpConnectionsToFile()
{
    BT_LOG_INFO(btLogSinker, " BTSPDConnTracker::dumpConnectionsToFile","dumping connections.....\n");

    i_LastConnDumpFileIndex++;
    stringstream strm;
    strm<<s_FileName<<"_"<<i_LastConnDumpFileIndex;

    dumpConnMapToFile(map_CurrentConnections, strm.str()+".txt");
    dumpConnMapToFile(map_AllConnections, strm.str()+"_All.txt");
}

void BTSPDConnTracker::handleNewNodeCreationMsg(cMessage* _pMsg)
{
    BTSPDConnTrackNodeCreationMsg* pMsg =
            check_and_cast<BTSPDConnTrackNodeCreationMsg*>(_pMsg);

    map_IPtoName[pMsg->myIP()] = pMsg->myName();

    std::set<std::string> & setConns = map_AllConnections[pMsg->myName()];
    stringstream strm;
    strm<<"z1 NodeCreationTime["<<pMsg->creationTime()<<"]";
    setConns.insert(strm.str());
}

void BTSPDConnTracker::handleNewConnectionMsg(cMessage* _pMsg)
{
    BTSPDConnTrackNewConnMsg* pMsg = check_and_cast<BTSPDConnTrackNewConnMsg*>(_pMsg);

//    BT_LOG_DEBUG(btLogSinker, " BTSPDConnTracker::storeConnMap","Got new connection detail from ["<<
//            pMsg->myName()<<"] to ["<< pMsg->remoteIP()<<"] \n");

    std::set<std::string> & setCurrConns = map_CurrentConnections[pMsg->myName()];
    setCurrConns.insert(pMsg->remoteIP());

    std::set<std::string> & setAllConns = map_AllConnections[pMsg->myName()];

    setAllConns.insert(pMsg->remoteIP());
}

void BTSPDConnTracker::handleConnectionLostMsg(cMessage* _pMsg)
{
    BTSPDConnTrackConnDropMsg* pMsg = check_and_cast<BTSPDConnTrackConnDropMsg*>(_pMsg);

    std::set<std::string> & setConns = map_CurrentConnections[pMsg->myName()];

    setConns.erase(pMsg->remoteIP());
}

void BTSPDConnTracker::handleDwlCompleteMsg(cMessage* _pMsg)
{
    BTSPDConnTrackDwlCompeteMsg* pMsg = check_and_cast<BTSPDConnTrackDwlCompeteMsg*>(_pMsg);

    std::set<std::string> & setConns = map_AllConnections[pMsg->myName()];
    stringstream strm;
    strm<<"z2 DownloadCompletionTime["<<pMsg->completionTime()<<"], "<<
            "DownloaDuration["<<pMsg->duration()<<"]";
    setConns.insert(strm.str());
    //also insert in to the current conn map such that  download completion is visible on current conn file

    std::set<std::string> & setCurrConns = map_CurrentConnections[pMsg->myName()];
    setCurrConns.insert(strm.str());

}

void BTSPDConnTracker::dumpConnMapToFile(std::map<std::string, std::set<std::string> > & _mapConnMap,
        const std::string & _sFileName)
{
    ofstream myfile (_sFileName.c_str());
    if (myfile.is_open() == false)
    {
      throw cRuntimeError("Failed to open file [%s] for connection map dump", _sFileName.c_str());
      return;
    }

    stringstream strm;
    strm<<"Snapshot taken at simulation time - "<<simTime()<< " seconds"<<endl<<endl;

    strm<<"----------Legend----------"<<endl;
    map<string, string>::iterator itrTerminalTypes = map_TerminalNames.begin();
    for ( ; itrTerminalTypes != map_TerminalNames.end() ; itrTerminalTypes++)
    {
        strm<<itrTerminalTypes->first<<" - " <<itrTerminalTypes->second<<endl;

    }
    strm<<"----------End of Legend----------"<<endl<<endl;

    map<string, set<string> >::iterator itrConnMap=
            _mapConnMap.begin();


    for( ;  itrConnMap != _mapConnMap.end() ; itrConnMap++)
    {
        strm<< getNodeNameWithTErminalType(itrConnMap->first) <<" : ";
        set<string> & setConns= itrConnMap->second;

        set<string>::iterator itrConns = setConns.begin();
        int iConnCount=0;
        for ( ; itrConns != setConns.end() ; itrConns++ )
        {
            std::map<std::string, std::string>::iterator itrIP2Name =
                    map_IPtoName.find(*itrConns);

            if ( itrIP2Name == map_IPtoName.end())
            {
                strm<< (*itrConns);
            }
            else
            {
                strm<< getNodeNameWithTErminalType(itrIP2Name->second);
                iConnCount++;

            }
            strm<<", ";

        }
        strm<<"ConnectionCount-"<<iConnCount<<", ";
        strm<<endl<<endl;

        //cout<<strm.str();
    }

    myfile<<strm.str();

    myfile.close();
}

std::string BTSPDConnTracker::getNodeNameWithTErminalType(const std::string & _sNodeName)
{
    string sRet(_sNodeName);

    size_t pos = _sNodeName.find_first_of('[');
    if (pos != string::npos)
    {
        string sNodePrefix = _sNodeName.substr(0, pos);
        map<string, string>::iterator  itr = map_TerminalNames.find(sNodePrefix);
        if ( itr != map_TerminalNames.end() )
        {
            sRet = itr->second;
            sRet.append(_sNodeName.substr(pos));
        }
    }
    return sRet;
}

void BTSPDConnTracker::splitStringByCommas(const char * _pStr, std::vector<std::string>& _vector)
{
    char pLocStr[strlen(_pStr) + 1];
    strncpy(pLocStr, _pStr, strlen(_pStr) + 1);

    char *p = strtok(pLocStr, ",");
    while (p) {
        //printf("Token: %s\n", p);
        _vector.push_back(p);
        p = strtok(NULL, ",");
    }

}
