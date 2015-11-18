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

#ifndef BTSTATISTICSRELAY_H_
#define BTSTATISTICSRELAY_H_

#include <string>
#include <map>

#include "../BitTorrent/BTStatistics.h"
#include "BTSPDStatisticNodeStructFactory.h"

# define BT_STATS_RELAY_DWL         764
# define BT_STATS_REGULAR_MSG       765

using std::string;
using std::map;



/*!
 * class which collects statistics of BTTorrent Relays Hosts
 */
class INET_API BTStatisticsSPD :public BTStatistics
{
public:
    BTStatisticsSPD();
    virtual ~BTStatisticsSPD();

    virtual void handleMessage(cMessage* msg);

    virtual void finish();

    virtual void nodeCreated(const std::string & _sNodeName, NODE_TYPE nodeType = NORMAL_PEER);
    virtual void nodeExited(const std::string & _sNodeName);
    virtual void nodeIsActiveInSwarm(const std::string & _sNodeName);
    virtual void nodeLeftTheSwarm(const std::string & _sNodeName);
    virtual void nodeCompletedTheDownload(const std::string & _sNodeName);

    virtual void incrementTargetCompleteCount();

protected:

    virtual void initialize();
    virtual void statTimerFired();

    int         i_StartedNormalPeerCount;
    int         i_StartedRelayCount;

    int         i_LiveNormalCount;
    int         i_LiveRelayCount;

    int         i_ActiveNormalCount;
    int         i_ActiveRelayCount;

    int         i_CompletedNormalCount;
    int         i_CompletedRelayCount;

    int         i_Statinterval;
    cMessage*   p_StatMsg;

    cStdDev*    dwSuccess_Relay;
    cOutVector  dwSuccess_Relay_vec;

    cStdDev*    numBlockFail_Relay;
    cOutVector  numBlockFail_Relay_vec;

    std::string s_FileName;


    BTSPDStatisticNodeStructFactory m_Factory;


    map<string, NodeStruct*>    map_Peers;
};

#endif /* BTSTATISTICSRELAY_H_ */
