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

#ifndef BTTRACKERCLIENTHANDLERRELAYENBLED_H_
#define BTTRACKERCLIENTHANDLERRELAYENBLED_H_
#include "BTTrackerSPD.h"
#include "BTTrackerMsgSPD_m.h"

class BTTrackerClientHandlerSPD : public BTTrackerClientHandlerBase
{
public:
    BTTrackerClientHandlerSPD();
    virtual ~BTTrackerClientHandlerSPD();
    BTTrackerSPD *getHostModule();
protected:
    //overrides from BTTrackerClientHandlerBase
    virtual void dataArrived(cMessage*, bool);
    virtual int processAnnounce(BTTrackerMsgAnnounce*);
    virtual void fillPeersInResponse(BTTrackerMsgAnnounce *amsg, BTTrackerMsgResponse*, bool, bool);
    virtual BTTrackerStructBase *createTrackerStructObj(BTTrackerMsgAnnounce *amsg);
    //end of overrides from BTTrackerClientHandlerBase


    virtual void fillWithoutDownloaders(BTTrackerMsgAnnounce *amsg, BTTrackerMsgResponse*, bool, bool);
    virtual void fillOnlySeeders(BTTrackerMsgAnnounce *amsg, BTTrackerMsgResponse *rmsg, bool seed, bool no_peer_id);
    virtual void determinePeerMix(double _dRequestedRelayPeerPcntg, int iCurrenTruePeerCountinRes, int _iAvailableRelayPeerCount, int & _iTruePeerCount, int & _iRelayPeerCount);
    virtual void fillPeersinToMsg(BTTrackerMsgResponse *rmsg, int _iStartIndex, const std::set<int> & added_peers, const cArray & peerPool, bool no_peer_id);
    virtual int processRelayAnnounce(BTTrackerMsgAnnounce*);
    virtual void removeBlackListedPeersFromResponse(BTTrackerMsgResponse*);
    virtual void fillRelayPeers(BTTrackerMsgResponse *rmsg, BTTrackerMsgAnnounceSPD *pSPDMsg, BTTrackerMsgAnnounce *amsg, bool no_peer_id);

    int processAnnounceForTrueHashFromRelay(BTTrackerMsgAnnounce* amsg);

    virtual void updateSPDFieldsinTrackerStruct(BTTrackerMsgAnnounceSPD* amsg);


    //boolean which indicates that the client making the announce for true info hash is a relay
    //this is added as a boolean since the super class is not flexible enough to add such functionality without much code duplication.
    //note that this variable is set in one function and used in another and used as a flag for information transfer between two functions.
    //and this works only because omnetpp is single threaded.
    bool b_IsClient_A_Relay;


};

#endif /* BTTRACKERCLIENTHANDLERRELAYENBLED_H_ */
