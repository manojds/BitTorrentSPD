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
#include <sstream>
#include <fstream>

#include "BTStatisticsSPD.h"
#include "../BitTorrent/BTLogImpl.h"

using namespace std;

Define_Module(BTStatisticsSPD);

BTStatisticsSPD::BTStatisticsSPD() :
i_StartedNormalPeerCount(0),
i_StartedRelayCount(0),
i_LiveNormalCount(0),
i_LiveRelayCount(0),
i_ActiveNormalCount(0),
i_ActiveRelayCount(0),
i_CompletedNormalCount(0),
i_CompletedRelayCount(0),
i_Statinterval(25),
p_StatMsg(NULL),
s_FileName("BTSPD_Stats.txt")
{


}

BTStatisticsSPD::~BTStatisticsSPD() {
    delete dwSuccess_Relay;
    delete numBlockFail_Relay;

    cancelAndDelete(p_StatMsg);

}

void BTStatisticsSPD::initialize()
{
    BTStatistics::initialize();

    BT_LOG_ESSEN(btLogSinker, "BTStatisticsSPD::initialize", "Initializing ....");


    dwSuccess_Relay = new  cStdDev("BitTorrent Relay:Download Duration");
    dwSuccess_Relay_vec.setName("BitTorrent Relay:Download Duration");

    numBlockFail_Relay = new  cStdDev("BitTorrent Relay:Failed Downloads:Number of Completed Blocks");
    numBlockFail_Relay_vec.setName("BitTorrent Relay:Failed Downloads:Number of Completed Blocks");

    i_Statinterval = par("statisticInterval");
    p_StatMsg = new cMessage("BT_STATS_REGULAR_MSG", BT_STATS_REGULAR_MSG);

    ofstream myfile (s_FileName.c_str());
    if (myfile.is_open() == false)
    {
      throw cRuntimeError("Failed to open file [%s] for stat writing", s_FileName.c_str());
      return;
    }

    myfile<<" ************** BT SPD Stats *********************"<<endl<<endl;

    myfile.close();

    statTimerFired();

}

void BTStatisticsSPD::handleMessage(cMessage* msg)
{
    switch (msg->getKind())
    {
        case BT_STATS_RELAY_DWL:
        {
            BT_LOG_DEBUG(btLogSinker,"BTStatisticsSPD::handleMessage","BT_STATS_RELAY_DWL msg received !");

            BTStatisticsDWLMsg* dwMsg = dynamic_cast<BTStatisticsDWLMsg*>(msg);
            double dwTime = dwMsg->downloadTime();
            double rmBlocks = dwMsg->remainingBlocks();
            if (rmBlocks == 0 )
            {
                dwSuccess_Relay->collect(dwTime);
                dwSuccess_Relay_vec.record(dwTime);

                BT_LOG_ESSEN(btLogSinker, "BTStatisticsSPD::handleMessage",
                        "Relay Download success count is now ["<<dwSuccess_Relay->getCount()<<
                        "] just completed node ["<<msg->getSenderModule()->getParentModule()->getFullName()<<"] Current average ["
                        <<dwSuccess_Relay->getMean()<<"] just completed value ["<<dwTime <<"]");
            }
            else
            {
                numBlockFail_Relay->collect(rmBlocks);
                numBlockFail_Relay_vec.record(rmBlocks);
            }
            delete msg;
            break;
        }

        case BT_STATS_REGULAR_MSG:
            statTimerFired();
            break;

        default:
        {
            BTStatistics::handleMessage(msg);
            break;
        }
    }

}


void BTStatisticsSPD::nodeCreated(const std::string & _sNodeName, NODE_TYPE _eNodeType )
{
    if ( map_Peers.find(_sNodeName) == map_Peers.end() )
    {
        NodeStruct* pNode   = m_Factory.getObject();
        pNode->s_NodeName   = _sNodeName;
        pNode->e_NodeType   = _eNodeType;

        if ( pNode->e_NodeType == NORMAL_PEER )
        {
            ++i_LiveNormalCount;
            ++i_StartedNormalPeerCount;
            //relay peers are active in the swarm as soon as they have been created.
            pNode->b_ActiveInSwarm = true;
            ++i_ActiveNormalCount;
        }
        else if ( pNode->e_NodeType == RELAY_PEER )
        {
            ++i_LiveRelayCount;
            ++i_StartedRelayCount;
            //relay peers don't participate in the swarm as soon as they have been created
            pNode->b_ActiveInSwarm = false;
        }

        map_Peers[_sNodeName] = pNode;
    }
    else
    {
        throw cRuntimeError("BTStatisticsSPD::nodeCreated - Node created event received twice for peer [%s]", _sNodeName.c_str());
    }

}

void BTStatisticsSPD::nodeExited(const std::string & _sNodeName)
{
    map<string, NodeStruct*>::iterator itr =  map_Peers.find(_sNodeName);
    if ( itr != map_Peers.end() )
    {
        NodeStruct* pNode   =  itr->second;

        map_Peers.erase(_sNodeName);

        m_Factory.releaseObject(pNode);

        pNode =NULL;
        --i_LiveNormalCount;

    }
    else
    {
        throw cRuntimeError("BTStatisticsSPD::nodeExited , node not found [%s]", _sNodeName.c_str());
    }
}

void BTStatisticsSPD::nodeIsActiveInSwarm(const std::string & _sNodeName)
{
    map<string, NodeStruct*>::iterator itr =  map_Peers.find(_sNodeName);
    if ( itr != map_Peers.end() )
    {
        NodeStruct* pNode   =  itr->second;
         if ( ! pNode->b_ActiveInSwarm )
         {
             pNode->b_ActiveInSwarm =true;

             if ( pNode->e_NodeType == NORMAL_PEER )
                 ++i_ActiveNormalCount;

             else if ( pNode->e_NodeType == RELAY_PEER )
                 ++i_ActiveRelayCount;
         }
         else
         {
             throw cRuntimeError("BTStatisticsSPD::nodeIsActiveInSwarm , Active in swarm event received while, node is already active. [%s]", _sNodeName.c_str());
         }
    }
    else
    {
        throw cRuntimeError("BTStatisticsSPD::nodeIsActiveInSwarm , node not found [%s]", _sNodeName.c_str());
    }
}

void BTStatisticsSPD::nodeLeftTheSwarm(const std::string & _sNodeName)
{
    map<string, NodeStruct*>::iterator itr =  map_Peers.find(_sNodeName);
    if ( itr != map_Peers.end() )
    {
        NodeStruct* pNode   =  itr->second;
         if ( pNode->b_ActiveInSwarm )
         {
             pNode->b_ActiveInSwarm = false;

             if ( pNode->e_NodeType == NORMAL_PEER )
                 --i_ActiveNormalCount;

             else if ( pNode->e_NodeType == RELAY_PEER )
                 --i_ActiveRelayCount;
         }
         else if (pNode->e_NodeType != RELAY_PEER )
         {
             throw cRuntimeError("BTStatisticsSPD::nodeLeftTheSwarm ,left the swarm event received while, node not active. [%s]", _sNodeName.c_str());
         }
    }
    else
    {
        throw cRuntimeError("BTStatisticsSPD::nodeLeftTheSwarm , node not found [%s]", _sNodeName.c_str());
    }
}

void BTStatisticsSPD::nodeCompletedTheDownload(const std::string & _sNodeName)
{
    map<string, NodeStruct*>::iterator itr =  map_Peers.find(_sNodeName);
    if ( itr != map_Peers.end() )
    {
        NodeStruct* pNode   =  itr->second;
         if ( ! pNode->b_DownloadCompleted )
         {
             pNode->b_DownloadCompleted = true;

             if ( pNode->e_NodeType == NORMAL_PEER )
                 ++i_CompletedNormalCount;

             else if ( pNode->e_NodeType == RELAY_PEER )
                 ++i_CompletedRelayCount;
         }
         else
         {
             throw cRuntimeError("BTStatisticsSPD::nodeCompletedTheDownload , completed event is received while already download is completed. [%s]", _sNodeName.c_str());
         }
    }
    else
    {
        throw cRuntimeError("BTStatisticsSPD::nodeCompletedTheDownload , node not found [%s]", _sNodeName.c_str());
    }
}


void BTStatisticsSPD::statTimerFired()
{
    ofstream myfile (s_FileName.c_str(), ios::app);
    if (myfile.is_open() == false)
    {
      throw cRuntimeError("Failed to open file [%s] for stat writing", s_FileName.c_str());
      return;
    }

    myfile<<simTime()<<" , [True] , Started ,"<<i_StartedNormalPeerCount<<" , Live ,"<<i_LiveNormalCount<<" , Active ,"<<i_ActiveNormalCount<<
            " , Completed ,"<<i_CompletedNormalCount<<", Average , "<<dwSuccess->getMean()<<

            " , [Relay] , Started , "<<i_StartedRelayCount<<" , Live ,"<< i_LiveRelayCount<<
            " , Active ,"<<i_ActiveRelayCount<<" , Completed ,"<<i_CompletedRelayCount<<", Average , "<<dwSuccess_Relay->getMean()<<endl;;

    myfile.close();

    scheduleAt( simTime() + i_Statinterval, p_StatMsg);


}

void BTStatisticsSPD::finish()
{
    BT_LOG_ESSEN(btLogSinker,"BTStatisticsSPD::doFinish","Finishing ...");

    BT_LOG_ESSEN(btLogSinker,"BTStatisticsSPD::doFinish","Relay Download duration Mean ["<<dwSuccess_Relay->getMean()<<
            "] STD Dev["<<dwSuccess_Relay->getStddev()<<"] Count ["<<dwSuccess_Relay->getCount()<<"]");

    dwSuccess_Relay->record();
    numBlockFail_Relay->record();
}
