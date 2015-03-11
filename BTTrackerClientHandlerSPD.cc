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

#include "BTTrackerClientHandlerSPD.h"
#include "../BitTorrent/BTLogImpl.h"
#include "BTTrackerMsgSPD_m.h"

Register_Class(BTTrackerClientHandlerSPD);

BTTrackerClientHandlerSPD::BTTrackerClientHandlerSPD() {
    // TODO Auto-generated constructor stub

}

BTTrackerClientHandlerSPD::~BTTrackerClientHandlerSPD() {
    // TODO Auto-generated destructor stub
}

BTTrackerSPD* BTTrackerClientHandlerSPD::getHostModule()
{
    // get the host module and check its type
    BTTrackerSPD* hostMod = check_and_cast<BTTrackerSPD*>(TCPServerThreadBase::getHostModule());
    //mjp
    // return the correct module
    return hostMod;
}


/**
 * Handle an announce for a relay Hash. And marks clients as a seeder if it is a seeder. (for hiding leachers from others)
 * Returns the status of the process (i.e., a constant value which indicates what should the tracker reply with).
 */
int BTTrackerClientHandlerSPD::processAnnounce(BTTrackerMsgAnnounce* amsg)
{
    //we act only if the info hash is equal to relay info hash
    //otherwise we let super class to handle it
    if(amsg->infoHash() == getHostModule()->relayInfoHash())
    {
        BT_LOG_INFO(btLogSinker, "BTTrackerClientHndlrSPD::processAnnounce", "Announce request for relay hash from client[address="
                << getSocket()->getRemoteAddress() << ", port=" << getSocket()->getRemotePort() << "] with event ["<<amsg->event()<<"]");

        // temporary peer struct with the announce info
        BTTrackerStructBase* tpeer = NULL;
        // a peer from the pool
        BTTrackerStructBase* peer = NULL;
        // the position of the peer in the pool
        cPeer = -1;

        // sanity checks - failures

        // no peer id
        if (strlen(amsg->peerId()) == 0) {
            return A_INVALID_PEERID;
        }
        // invalid port
        if (amsg->peerPort() == 0) {
            return A_INVALID_PORT;
        }

        // init the temp peer struct
        tpeer = new BTTrackerStructBase(
                IPvXAddress(getSocket()->getRemoteAddress()),
                string(amsg->peerId()), amsg->peerPort(), string(amsg->key()),
                simTime(), (amsg->event() == A_COMPLETED) ? true : false);

        // search to find if the peer exists in the pool or not
        cPeer = getHostModule()->containsRelay(tpeer);

        // differentiate based on the actual message event field
        switch (amsg->event()) {
        // started event
        case A_STARTED:

            // insert the peer to the peers pool
            if (cPeer == -1) // do the magic only if the peer does not exist
            {
                cPeer = getHostModule()->relayPeers().add(tpeer);
                getHostModule()->setRealyPeersNum(
                        getHostModule()->realyPeersNum() + 1);
            }
            else // the peer exists, update its fields
            {
                // get the peer
                peer = (BTTrackerStructBase*) getHostModule()->relayPeers()[cPeer];
                // update
                peer->setIpAddress(tpeer->ipAddress());
                peer->setPeerId(tpeer->peerId());
                peer->setPeerPort(tpeer->peerPort());
                peer->setKey(tpeer->key());
                peer->setLastAnnounce(tpeer->lastAnnounce());
                peer->setIsSeed(tpeer->isSeed());
                //Ntinos Katsaros: 22/11/2008
                delete tpeer;
            }

            // valid announce with started event
            return A_VALID_STARTED;
            break;

            // completed event
        case A_COMPLETED:

            // check if the peer is in the peers pool, the peer should have sent an announce with started event before
            if (cPeer == -1) {
                // completed event with no started event before from the same peer
                return A_NO_STARTED;
            }

            // ok the peer is in the pool, update his status and proceed like a normal announce

            // get the peer
            peer = (BTTrackerStructBase*) getHostModule()->relayPeers()[cPeer];

            // update the peer's status and the seeds' count only for the first completed event
            if (!peer->isSeed()) {
                peer->setIsSeed(true);
                //Commented by MAnoj . 2015-01-25
                // TODO :: uncomment this and correct the behavior if relays
                //can be seeders with respect to relay hash.
                //getHostModule()->setSeeds(getHostModule()->seeds() + 1);
            }

            // update
            peer->setIpAddress(tpeer->ipAddress());
            peer->setPeerId(tpeer->peerId());
            peer->setPeerPort(tpeer->peerPort());
            peer->setKey(tpeer->key());
            peer->setLastAnnounce(tpeer->lastAnnounce());

            //Ntinos Katsaros: 22/11/2008
            delete tpeer;

            // valid announce with completed event
            return A_VALID_COMPLETED;
            break;

            // normal announce
        case A_NORMAL:

            // check if the peer is in the peers pool, the peer should have sent an announce with started event before
            if (cPeer == -1) {
                // normal announce event with no started event before from the same peer
                return A_NO_STARTED;
            }

            // get the peer
            peer = (BTTrackerStructBase*) getHostModule()->relayPeers()[cPeer];

            // update
            peer->setIpAddress(tpeer->ipAddress());
            peer->setPeerId(tpeer->peerId());
            peer->setPeerPort(tpeer->peerPort());
            peer->setKey(tpeer->key());
            peer->setLastAnnounce(tpeer->lastAnnounce());
            peer->setIsSeed(false);

            //Ntinos Katsaros: 22/11/2008
            delete tpeer;

            // valid normal announce
            return A_VALID_NORMAL;
            break;

            // stopped event
        case A_STOPPED:

            // check if the peer is in the peers pool, the peer should have sent an announce with started event before
            if (cPeer == -1) {
                // stopped event with no started event before from the same peer
                return A_NO_STARTED;
            }

            // get the peer
            peer = (BTTrackerStructBase*) getHostModule()->relayPeers()[cPeer];

            // remove him and if the peer was a seeder change the seeds count

            //Commented by MAnoj . 2015-01-25
            // TODO :: uncomment this and correct the behavior if relays
            //can be seeders with respect to relay hash.

//            if (peer->isSeed()) {
//                getHostModule()->setSeeds(getHostModule()->seeds() - 1);
//            }
            //end of the commented block by MAnoj.

            //getHostModule()->peers().remove(cPeer);
            getHostModule()->cleanRemoveRelayPeer(cPeer);
            getHostModule()->setRealyPeersNum(getHostModule()->realyPeersNum() - 1);

            //Ntinos Katsaros: 22/11/2008
            delete tpeer;

            // valid announce with stopped event
            return A_VALID_STOPPED;
            break;

            // invalid message event field
        default:

            //Ntinos Katsaros: 22/11/2008
            delete tpeer;

            return A_INVALID_EVENT;
        }
    }
    else
    {
        //let the super class to handle the normal announce procedure
        int iRetCode= BTTrackerClientHandlerBase::processAnnounce( amsg);

        //after that mark if this client as seeder if it is a seeder.

        if(cPeer != -1 && iRetCode < A_INVALID_EVENT)
        {
            BTTrackerMsgAnnounceSPD* pSPDMsg= dynamic_cast<BTTrackerMsgAnnounceSPD*>(amsg);


            //get the corresponding peer

            BTTrackerStructBase* peer=(BTTrackerStructBase*)getHostModule()->peers()[cPeer];

            if(pSPDMsg->seeder())
            {
                // update the peer's status and the seeds' count only if it is not marked as a seed already
                if(!peer->isSeed())
                {
                    peer->setIsSeed(true);
                    getHostModule()->setSeeds(getHostModule()->seeds() + 1);
                }
            }
        }

        return iRetCode;

    }
}

/**
 * Fill the response with peers.
 * for true hash
 */
void BTTrackerClientHandlerSPD::fillPeersInResponse(BTTrackerMsgAnnounce* amsg, BTTrackerMsgResponse* rmsg, bool seed, bool no_peer_id)
{
    //if it is relay hash we don't fill peers.
    if(strcmp(amsg->infoHash(), getHostModule()->relayInfoHash().c_str()) == 0)
    {
        BT_LOG_DETAIL(btLogSinker, "BTTrackerClientHndlrSPD::fillPeersInResponse", "Avoiding filling peers for relay hash announce. "
                "Client details [address="<< getSocket()->getRemoteAddress() << ", port=" << getSocket()->getRemotePort() << "]");
        return;
    }

    //This message should be a BTTrackerMsgAnnounceSPD message
    BTTrackerMsgAnnounceSPD* pSPDMsg= dynamic_cast<BTTrackerMsgAnnounceSPD*>(amsg);
    if(pSPDMsg == NULL)
    {
        throw cRuntimeError
            ("BTTrackerClientHandlerSPD::fillPeersInResponse - received a Message from client which is not a BTTrackerMsgAnnounceSPD message");
    }


    if(getHostModule()->sendSeersOnly() == true)
    {
        fillOnlySeeders(amsg, rmsg, pSPDMsg->seeder(), no_peer_id);
    }
    else
    {
        // let super class to fill true peers on its will
        BTTrackerClientHandlerBase::fillPeersInResponse(amsg, rmsg, seed, no_peer_id);

    }


    //then we start our work


    cArray& relayPeers=getHostModule()->relayPeers();

    int iAvailableTruePeerCount=rmsg->peersArraySize();
    int iAvaialbeRelayPeerCount=relayPeers.size();

    int iMaxTruePeerCount(0);
    int iMaxRelayPeersCount(0);

    determinePeerMix(pSPDMsg->relayPeerRatio(), iAvailableTruePeerCount, iAvaialbeRelayPeerCount , iMaxTruePeerCount, iMaxRelayPeersCount);

    //if the true peer count needs to be changed
    if (iAvailableTruePeerCount != iMaxTruePeerCount)
    {
        //now shrink the Peer array to the required size
        rmsg->setPeersArraySize(iMaxTruePeerCount);
    }

    //if there are relay peers to fill
    if(  iMaxRelayPeersCount != 0 )
    {
        // temporary peer from the peers pool
        BTTrackerStructBase* tpeer;
        // temporary peer to add to the response
        PEER ttpeer;

        // peers added
        set<int> added_peers;


        for (int i=0; ((int)added_peers.size() < iMaxRelayPeersCount) && (i < (int)relayPeers.size()) ; i++ )
        {
            //if there is peer at this index add it
            if(relayPeers[i] != NULL)
            {
                //This announcing peer is also could be a relay peer.
                //So this particular index may be give us the same peer from relay peer array.
                //We should not add the same peer requesting in the response
                if(amsg->peerId()  == ((BTTrackerStructBase*)relayPeers[i])->peerId())
                    continue;
                //also check whether this peer already in true peers list
                //bcz it is participating in the swarm
                bool bPresent(false);
                for(int j=0; j< (int)rmsg->peersArraySize(); j++)
                {
                    if( strcmp ((rmsg->peers(j)).peerId.c_str(),  ((BTTrackerStructBase*)relayPeers[i])->peerId().c_str() ) == 0 )
                    {
                        bPresent=true;
                        break;
                    }

                }

                if(!bPresent)
                    added_peers.insert(i);
            }
        }


        fillPeersinToMsg(rmsg, iMaxTruePeerCount, added_peers, relayPeers, no_peer_id);

//        rmsg->setPeersArraySize(iMaxTruePeerCount+added_peers.size());
//
//        set<int>::iterator it= added_peers.begin();
//        int i=0;
//        for( ; it != added_peers.end(); it++, i++)
//        {
//            // get the peer from the pool
//            tpeer = (BTTrackerStructBase*)relayPeers[*it];
//
//
//            // copy some fields/values
//            if(!no_peer_id)
//            {
//                ttpeer.peerId       = tpeer->peerId().c_str();
//            }
//            ttpeer.peerPort     = tpeer->peerPort();
//            ttpeer.ipAddress    = tpeer->ipAddress();
//
//            // insert the peer to the response
//            rmsg->setPeers(iMaxTruePeerCount+i, ttpeer);
//        }
    }
}

void BTTrackerClientHandlerSPD::determinePeerMix(double _dRequestedRelayPeerPcntg, int iCurrenTruePeerCountinRes,
        int _iAvailableRelayPeerCount, int & _iTruePeerCount, int & _iRelayPeerCount )
{
    int iMaxPeersInRes=getHostModule()->maxPeersInReply();
    bool bUseRelayPropotioninRequest=getHostModule()->useRelayPropotioninRequest();

    double dDelta=0.000001;

    double dRelayPeerPcntg(0.0);

    if(bUseRelayPropotioninRequest == false)
        dRelayPeerPcntg=getHostModule()->relayPeerPropotionInReply();
    else
        dRelayPeerPcntg=_dRequestedRelayPeerPcntg;

    //if ratio is negative or greater than one, it is invalid
    if( (dRelayPeerPcntg + dDelta) < 0 || (dRelayPeerPcntg - dDelta) > 1 )
    {
        throw cRuntimeError("BTTrackerClientHandlerSPD::determinePeerMix - invalid relay peer ratio [%f] specified", dRelayPeerPcntg);

    }
    else if(dRelayPeerPcntg < dDelta) // if requested relay peer percentage is zero
    {
        _iTruePeerCount=iCurrenTruePeerCountinRes;
        _iRelayPeerCount=0;
    }
    else if(  (1-dDelta) < dRelayPeerPcntg &&
            dRelayPeerPcntg < (1+dDelta) )    //if requested relay peer ratio is one
    {
        _iTruePeerCount= 0;

        if(iMaxPeersInRes < _iAvailableRelayPeerCount)
            _iRelayPeerCount=iMaxPeersInRes;
        else
            _iRelayPeerCount=_iAvailableRelayPeerCount;
    }
    //if we don't have atleast one true peer or atleast one relay peer
    else if (iCurrenTruePeerCountinRes==0 || _iAvailableRelayPeerCount==0)
    {
        //both should be zero. because we can't fulfill the percentage requirement
        _iRelayPeerCount=0;
        _iTruePeerCount=0;

    }
    else
    {
        int iMaxPossibleTruePeers=(1-dRelayPeerPcntg)*iMaxPeersInRes;
        int iMaxPossibleRelayPeers= dRelayPeerPcntg*iMaxPeersInRes;

        //if we have don't have enough true peers or relay peers to reach max number of peers

        if ( _iAvailableRelayPeerCount < iMaxPossibleRelayPeers || iCurrenTruePeerCountinRes < iMaxPossibleTruePeers)
        {
            double dAvailableRelayPcntg=(double)_iAvailableRelayPeerCount/(iCurrenTruePeerCountinRes+_iAvailableRelayPeerCount);

            if(dAvailableRelayPcntg < dRelayPeerPcntg)
            {
                //then peer count should be based on number of available relay peers
                _iRelayPeerCount=_iAvailableRelayPeerCount;
                _iTruePeerCount=(int) ((_iRelayPeerCount*(1-dRelayPeerPcntg))/ dRelayPeerPcntg);

            }
            else
            {
                //then peer count should be based on number of available true peers
                _iTruePeerCount= iCurrenTruePeerCountinRes;
                _iRelayPeerCount=(int)((_iTruePeerCount*dRelayPeerPcntg)/(1-dRelayPeerPcntg));
            }
        }
        else
        {
            //we have enough relay peers and true peers. so we take the maximum values
            _iTruePeerCount=iMaxPossibleTruePeers;
            _iRelayPeerCount= iMaxPossibleRelayPeers;

        }
    }
    BT_LOG_DEBUG(btLogSinker, "BTTrackerClientHndlrSPD::determinePeerMix",
            "Relay Peer Percentage ["<<dRelayPeerPcntg<<"] Available True Peer Count ["<<iCurrenTruePeerCountinRes<<
            "], Available Relay Peer Count["<<_iAvailableRelayPeerCount<<"]. In Response True Peer count ["<<_iTruePeerCount
            <<"] Relay Peer Count ["<<_iRelayPeerCount<<"]");
}

void BTTrackerClientHandlerSPD::fillOnlySeeders(BTTrackerMsgAnnounce* amsg, BTTrackerMsgResponse* rmsg, bool seed, bool no_peer_id)
{
    // get the peers pool
    cArray& peers               = getHostModule()->peers();
    int iSeedCount              = getHostModule()->seeds();
    BT_LOG_INFO(btLogSinker, "BTTrackerClientHandlerSPD::fillOnlySeeders",
            "filling peers, current number of available seeders ["<< iSeedCount<<"] peer array size ["<<peers.size()<<"]");
    // peers added
    set<int> added_peers            = set<int>();
    // iterator for the added_peers
    set<int>::iterator it;
    // the number of peers in the reply
    size_t max_peers            = 0;
    // temporary peer from the peers pool
    BTTrackerStructBase* tpeer;
    // temporary peer to add to the response
    PEER ttpeer;
    // random peer
    int rndpeer             = -1;

    if ( iSeedCount < 1 )//no seeds to add
        return;
    else if(seed) // response to a seed
    {
        //return;
        //we are not supposed to add any peers. but to activate seeders (to activate their choking algorithm)
        //we need to send some peers in the response.
        //so we will send one seeder.

        if(iSeedCount > 1)
        {
            max_peers=1;
        }
        else//there is only one seed. that is this peer
            return;

    }
    else // response to a normal peer
    {
        // how many peers we have to add
        max_peers = (iSeedCount <= getHostModule()->maxPeersInReply()) ? iSeedCount : getHostModule()->maxPeersInReply();
    }

    // random selection
    while(added_peers.size() < max_peers)
    {
        // get a random peer
        rndpeer = intrand(peers.size());

        // the random peer is the peer that made the announce, ignore
        if(rndpeer == cPeer)
        {
            continue;
        }
        // the random peer is already added, ignore
        if(added_peers.find(rndpeer) != added_peers.end())
        {
            continue;
        }
        // only add seeders, i.e. if it is not a seeder do not add
        if( (BTTrackerStructBase*)peers[rndpeer] && (((BTTrackerStructBase*)peers[rndpeer])->isSeed() ==false ))
        {
            continue;
        }

        // add the peer to the "added peers" pool
        if((BTTrackerStructBase*)peers[rndpeer])
        {
            added_peers.insert(rndpeer);
        }
    }

    // traverse the set and fill the response
    fillPeersinToMsg(rmsg, 0, added_peers, peers, no_peer_id);

//    rmsg->setPeersArraySize(added_peers.size());
//    for(it = added_peers.begin(); it != added_peers.end(); it++)
//    {
//        // get the peer from the pool
//        tpeer = (BTTrackerStructBase*)peers[*it];
//
//        // copy some fields/values
//        if(!no_peer_id)
//        {
//            ttpeer.peerId       = tpeer->peerId().c_str();
//        }
//        ttpeer.peerPort     = tpeer->peerPort();
//        ttpeer.ipAddress    = tpeer->ipAddress();
//
//        // insert the peer to the response
//        rmsg->setPeers(--max_peers, ttpeer);
//    }

}


void BTTrackerClientHandlerSPD::fillPeersinToMsg(BTTrackerMsgResponse* rmsg, int _iStartIndex,
        const std::set<int> & added_peers, const cArray & peerPool, bool no_peer_id)
{
    // temporary peer from the peers pool
    BTTrackerStructBase* tpeer;
    // temporary peer to add to the response
    PEER ttpeer;

    rmsg->setPeersArraySize(_iStartIndex+added_peers.size());
    set<int>::iterator it= added_peers.begin();
    int i=0;
    for( ; it != added_peers.end(); it++, i++)
    {
        // get the peer from the pool
        tpeer = (BTTrackerStructBase*)peerPool[*it];


        // copy some fields/values
        if(!no_peer_id)
        {
            ttpeer.peerId       = tpeer->peerId().c_str();
        }
        ttpeer.peerPort     = tpeer->peerPort();
        ttpeer.ipAddress    = tpeer->ipAddress();

        // insert the peer to the response
        rmsg->setPeers(_iStartIndex+i, ttpeer);
    }

}

