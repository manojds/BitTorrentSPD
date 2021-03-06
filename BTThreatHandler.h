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

#ifndef __INET_BTTHREATHANDLER_H_
#define __INET_BTTHREATHANDLER_H_

#include <omnetpp.h>
#include "../tcpapp/TCPGenericCliAppBase.h"
#include <queue>
#include <string>
#include <map>

using namespace std;

class Victim
{
public:
    std::string address;
    std::string sNodeName;
    bool        activeConn;
};

class INET_API BTThreatHandler : public TCPGenericCliAppBase
{
public:
    BTThreatHandler();
    virtual ~BTThreatHandler();

    virtual void newAddrFound(const std::string & _sNodeName, const std::string & _sIP, const std::string & _sPort, bool isActiveConn);
    virtual void connectionLost(const std::string & _sIP);

    virtual bool activateAdversary();
    virtual void cleanAdversary();

  protected:

    virtual void handleMsgFromBT(cMessage*);

    /* inherited methods from TCPGenericCliAppBase */
    virtual void initialize();
    virtual void handleMessage(cMessage*);
    virtual void handleTimer(cMessage *msg);
    virtual void socketEstablished(int, void*);
    //virtual void socketDataArrived(int, void*, cPacket*, bool);
    //virtual void socketPeerClosed(int, void*);
    virtual void socketFailure(int, void*, int);
    // end of the overridden methods



    virtual void findAndSetIPAddress();
    virtual void scheduleNextAttackAt(simtime_t t);
    virtual void tryNextAttack();
    virtual void sendAttackMsg(const Victim & victim);




    bool isMalicious();

  private:
    //static int          i_CurrentMaliciousNodeCount;
    bool                b_Malicious;
    bool                b_IsThreatEpidemic;
    bool                b_IsAttackOnCurrentConns;
    bool                b_AttackIsOngoing;
    cMessage*           p_ScheduleAttackMsg;
    cSimpleModule*      p_SecStatistics;
    simtime_t           t_AttackRetryDelay;
    double              d_AttackingPorbability;
    std::queue<Victim>  q_LearnedNodes;
    std::map<string,Victim>    map_CurrentConns;
};

#endif
