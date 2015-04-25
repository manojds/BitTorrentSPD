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
#include "BTSPDConnMap_m.h"
#include <string.h>
#include <sstream>
#include "../BitTorrent/BTLogImpl.h"

Define_Module(BTSPDConnTracker);

#define WRITE_CONN_MAP_TO_FILE_MSG_TYPE     2001
#define FILE_DUMP_INTERVAL                  150

using namespace std;

BTSPDConnTracker::BTSPDConnTracker():
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

    evt_DumpToFile = new cMessage("WRITE_CONN_MAP_TO_FILE_MSG_TYPE", WRITE_CONN_MAP_TO_FILE_MSG_TYPE);
    scheduleAt(simTime()+i_DumpingInterval, evt_DumpToFile);
}

void BTSPDConnTracker::handleMessage(cMessage *msg)
{
    if( msg->isSelfMessage() )
    {
        handleSelfMessage(msg);
    }
    else
    {
//        if (msg->getKind() == BTSPD_CONN_TRACK_NEWCONN_MSG_TYPE)
//        {
//            storeConnMap(msg);
//        }
//        else if (msg->getKind() == BTSPD_IP_TO_NAME_MAPPING_MSG_TYPE  )
//        {
//            storeIPtoNameMapping(msg);
//        }
//        else
//        {
//            throw cRuntimeError("BTSPDConnTrackerFunc::handleMessage - Unknown Message received. kind [%d] name [%s]",
//                    msg->getKind(),msg->getName() );
//        }
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
    stringstream strm;

    map<string, set<string> >::iterator itrConnMap=
            map_CurrentConnections.begin();


    for( ;  itrConnMap != map_CurrentConnections.end() ; itrConnMap++)
    {
        //strm<<map_IPtoName[itrConnMap->first]<<" : ";
        strm<<itrConnMap->first<<" : ";
        set<string> & setConns= itrConnMap->second;

        set<string>::iterator itrConns = setConns.begin();
        for ( ; itrConns != setConns.end() ; itrConns++)
        {
            //strm<<map_IPtoName[*itrConns]<<", ";
            strm<<*itrConns<<", ";
        }
        strm<<endl;

        cout<<strm.str();
    }

}

void BTSPDConnTracker::storeIPtoNameMapping(cMessage* _pMsg)
{
    BTSPDIPtoNameMappingMsg* pMsg = check_and_cast<BTSPDIPtoNameMappingMsg*>(_pMsg);
    map_IPtoName[pMsg->myIP()] = pMsg->myName();
}

void BTSPDConnTracker::storeConnMap(cMessage* _pMsg)
{
    BTSPDConnMapMsg* pMsg = check_and_cast<BTSPDConnMapMsg*>(_pMsg);

//    BT_LOG_DEBUG(btLogSinker, " BTSPDConnTracker::storeConnMap","Got new connection detail from ["<<
//            pMsg->myIP()<<"] to ["<< pMsg->remoteIP()<<"] \n");

    std::set<std::string> & setConns = map_CurrentConnections[pMsg->myIP()];

    setConns.insert(pMsg->remoteIP());

//    std::vector<std::string> vecConns;
//    splitStringByCommas(pMsg->remoteIP(), vecConns);
//
//    for(int i=0 ; i < vecConns.size() ; i++)
//    {
//        setConns.insert(vecConns[i]);
//    }


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
