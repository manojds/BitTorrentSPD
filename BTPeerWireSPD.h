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

#ifndef BTPEERWIRESPD_H_
#define BTPEERWIRESPD_H_
#include "../BitTorrent/BTPeerWireBase.h"
#include "BTSPDCommon.h"
#include "BTStatisticsSPD.h"

class BTThreatHandler;

class INET_API BTPeerWireSPD :public BTPeerWireBase
{
public:
    BTPeerWireSPD();
    virtual ~BTPeerWireSPD();

    const std::string & getPatchInfo(){return s_PatchInfo;}
    const std::string & getPlatFormType(){ return s_PlatFormType; }

protected:

    virtual void initialize();

    virtual void handleSelfMessage(cMessage* msg);
    virtual cMessage * createTrackerCommMsg();


    //reschedule the tracker communication at the given time.
    //this function cancel any scheduled tracker communication and reschedule it for the given time
    virtual void RescheduleTrackerCommAt(simtime_t t);

    virtual IPvXAddress getMyIPAddr();

    virtual void newConnectionFromPeerEstablished(PEER peer, TCPServerThreadBase* thread);
    virtual void newConnectionToPeerEstablished(PEER peer, TCPServerThreadBase* thread);
    virtual void peerFoundFromTracker(PEER peer);
    virtual void connectionLostFromPeer(PEER peer, bool isActiveConn);
    virtual void checkRcvdConnIsViable(const PEER & peer);

    virtual void notifyNewAddrToThreatHndlr(const PEER & peer, bool isActiveConn);

    virtual void handleNodeCreationEvent();
    virtual void notifynodeCreationToStatModule();
    virtual void notifyNewConnToConnMapper(const PEER & peer, bool isActive);
    virtual void notifyConnDropToConnMapper(const PEER & peer);
    virtual void notifyDwlCompleteToConnMapper(simtime_t _tDuration);
    virtual void notifyNodeCreationToConnMapper();

    virtual void downloadCompleted(simtime_t _tDuration);

    virtual void scheduleConnections(BTTrackerMsgResponse*);

    virtual void disconnectAllActiveConns();

    virtual void checkConnections();
    virtual void checkPassiveConnLimit();
    virtual void disconnectBadConnections();

    virtual void onLeavingSwarm();
    virtual void onReadyToLeaveSwarm();


    bool                b_enableConnMapDumping;
    bool                b_PublishTrackerOnCompletion;
    bool                b_PublishMeByTracker;
    bool                b_DisconnectBadConnections;
    bool                b_DownloadCompleted;
    bool                b_DoNotActivelyParticipateOnCompletion;
    bool                b_PassiveConnectionsBlocked;
    int                 i_PassiveConnCount;
    int                 i_MaxPassiveConnCount;
    PEER_FILL_METHOD    fillMethod;

    BTThreatHandler*    p_ThreatHndlr;
    cSimpleModule*      p_ConnTracker;
    BTStatisticsSPD*    p_StatModule;
    cMessage*           p_NotifyNodeCreation;

    std::string         s_PlatFormType;
    std::string         s_PatchInfo;

};

#endif /* BTPEERWIRESPD_H_ */
