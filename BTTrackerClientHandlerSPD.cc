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
#include "BTTrackerStructBaseSPD.h"
#include "BTSPDPeerBlackListReqMsg_m.h"

Register_Class(BTTrackerClientHandlerSPD);

BTTrackerClientHandlerSPD::BTTrackerClientHandlerSPD():
        b_IsClient_A_Relay(false)
{

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
        return processRelayAnnounce(amsg);

    }
    else
    {

        int iRetCode(A_INVALID_EVENT);

        BTTrackerMsgAnnounceSPD* pSPDMsg= check_and_cast<BTTrackerMsgAnnounceSPD*>(amsg);

        //if relay is making announce for true info hash and setting relays in true peer portion of peer list is disabled
        //do not follow the normal announce. in that case we do not add the peer to peer array
        if(getHostModule()->isExcludeRelaysInTruePeerList() && pSPDMsg->isRelay())
        {
            iRetCode = processAnnounceForTrueHashFromRelay(amsg);
        }
        else
        {
            //let the super class to handle the normal announce procedure
            iRetCode = BTTrackerClientHandlerBase::processAnnounce( amsg);
            //after that mark if this client as seeder if it is a seeder.

            if(cPeer != -1 && iRetCode < A_INVALID_EVENT)
            {
                updateSPDFieldsinTrackerStruct(pSPDMsg);
            }
        }

        return iRetCode;
    }
}

void BTTrackerClientHandlerSPD::updateSPDFieldsinTrackerStruct(BTTrackerMsgAnnounceSPD* pSPDMsg)
{
    //get the corresponding peer

    BTTrackerStructBase* peerTemp=(BTTrackerStructBase*)getHostModule()->peers()[cPeer];

    //when peer announce with the STOP_EVENT peer struct may be removed in process announce and we will get NULL values
    if( peerTemp != NULL)
    {
        BTTrackerStructBaseSPD * peer = check_and_cast<BTTrackerStructBaseSPD *>(peerTemp);

        peer->setPublishInPeerList(pSPDMsg->publishInPeerList());

        //set client is seeder if it is a seeder. but only if it is not set as a seeder already
        if(pSPDMsg->seeder())
        {
            // update the peer's status and the seeds' count only if it is not marked as a seed already
            if(!peer->isSeed())
            {
                peer->setIsSeed(true);
                getHostModule()->setSeeds(getHostModule()->seeds() + 1);
                BT_LOG_DETAIL(btLogSinker, "BTTrackerClientHndlrSPD::fillPeersInResponse",
                        "marking a seed. Current Seed Count ["<<getHostModule()->seeds()<<"]");
            }
        }
    }

}

void BTTrackerClientHandlerSPD::updateRelayPeerDetailsFromAnnounceMsg(BTTrackerMsgAnnounce* _pMsg, int _iPeerIndex, bool _bSetIsSeeder)
{
    BTTrackerStructBase* peer = (BTTrackerStructBase*)getHostModule()->relayPeers()[_iPeerIndex];
    // update
    peer->setIpAddress(IPvXAddress(getSocket()->getRemoteAddress()));
    peer->setPeerId(_pMsg->peerId());
    peer->setPeerPort(_pMsg->peerPort());
    peer->setKey(_pMsg->key());
    peer->setLastAnnounce(simTime());

    if (_bSetIsSeeder)
    {
        peer->setIsSeed((_pMsg->event() == A_COMPLETED) ? true : false);
    }
}

int BTTrackerClientHandlerSPD::processRelayAnnounce(BTTrackerMsgAnnounce* amsg)
{
    BT_LOG_INFO(btLogSinker, "BTTrackerClientHndlrSPD::processAnnounce", "Announce request for relay hash from client[address="
            << getSocket()->getRemoteAddress() << ", port=" << getSocket()->getRemotePort() << "], name ["<< amsg->peerId()<<"] with event ["<<amsg->event()<<"]");


    // the position of the peer in the pool
    cPeer = -1;

    // sanity checks - failures

    // no peer id
    if (strlen(amsg->peerId()) == 0)
    {
        return A_INVALID_PEERID;
    }
    // invalid port
    if (amsg->peerPort() == 0)
    {
        return A_INVALID_PORT;
    }

    // search to find if the peer exists in the pool or not
    cPeer = getHostModule()->containsRelay(amsg->peerId());

    // differentiate based on the actual message event field
    switch (amsg->event())
    {
    // started event
    case A_STARTED:

        // insert the peer to the peers pool
        if (cPeer == -1) // do the magic only if the peer does not exist
        {
            // temporary peer struct with the announce info
            BTTrackerStructBase* tpeer = createTrackerStructObj(amsg);

            cPeer = getHostModule()->addRelayPeer(tpeer);
        }
        else // the peer exists, update its fields
        {
            // update
            updateRelayPeerDetailsFromAnnounceMsg(amsg, cPeer, true );
        }

        // valid announce with started event
        return A_VALID_STARTED;
        break;

        // completed event
    case A_COMPLETED:
    {

        // check if the peer is in the peers pool, the peer should have sent an announce with started event before
        if (cPeer == -1)
        {
            // completed event with no started event before from the same peer
            return A_NO_STARTED;
        }

        // ok the peer is in the pool, update his status and proceed like a normal announce

        // get the peer
        BTTrackerStructBase* peer = (BTTrackerStructBase*) getHostModule()->relayPeers()[cPeer];

        // update the peer's status and the seeds' count only for the first completed event
        if (!peer->isSeed()) {
            //Commented by MAnoj . 2015-01-25
            // TODO :: uncomment this and correct the behavior if relays
            //can be seeders with respect to relay hash.
            //getHostModule()->setSeeds(getHostModule()->seeds() + 1);
        }

        // update
        updateRelayPeerDetailsFromAnnounceMsg(amsg, cPeer, true );

        // valid announce with completed event
        return A_VALID_COMPLETED;
        break;
    }

        // normal announce
    case A_NORMAL:

        // check if the peer is in the peers pool, the peer should have sent an announce with started event before
        if (cPeer == -1)
        {
            // normal announce event with no started event before from the same peer
            return A_NO_STARTED;
        }

        // update
        updateRelayPeerDetailsFromAnnounceMsg(amsg, cPeer, false );

        // valid normal announce
        return A_VALID_NORMAL;
        break;

        // stopped event
    case A_STOPPED:

        // check if the peer is in the peers pool, the peer should have sent an announce with started event before
        if (cPeer == -1)
        {
            // stopped event with no started event before from the same peer
            return A_NO_STARTED;
        }

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

        // valid announce with stopped event
        return A_VALID_STOPPED;
        break;

        // invalid message event field
    default:
        return A_INVALID_EVENT;
    }
}

void BTTrackerClientHandlerSPD::fillRelayPeers(BTTrackerMsgResponse *rmsg, BTTrackerMsgAnnounceSPD *pSPDMsg, BTTrackerMsgAnnounce *amsg, bool no_peer_id)
{
    //then we start our work
    cArray & relayPeers = getHostModule()->relayPeers();
    int iAvailableTruePeerCount = rmsg->peersArraySize();
    int iAvaialbeRelayPeerCount = getHostModule()->getMaxNumberOfAvailableRelayPeersToFill();
    if (pSPDMsg->isRelay())
    {
        iAvaialbeRelayPeerCount--;
        // reason for -1 : if the relay peer is making this request and actual relay peer array size we are
        // taking about is relayPeers.size() -1, because we can't send id of a peer to itself
    }

    BT_LOG_INFO(btLogSinker, "BTTrackerClientHndlrSPD::fillRelayPeers","fillRelayPeers -"
                                    "relay peer count ["<<getHostModule()->realyPeersNum()<<"] relay pool size ["<<
                                    getHostModule()->getRelayPoolSize()<<"] relay excluded size ["<<
                                    getHostModule()->getExcludedRelaySetSize()<<"] is Relay ["<<pSPDMsg->isRelay()<<"]");

    int iMaxTruePeerCount(0);
    int iMaxRelayPeersCount(0);
    determinePeerMix(pSPDMsg->relayPeerRatio(), iAvailableTruePeerCount, iAvaialbeRelayPeerCount, iMaxTruePeerCount, iMaxRelayPeersCount);

    //if the true peer count needs to be changed
    if(iAvailableTruePeerCount != iMaxTruePeerCount){
        //now shrink the Peer array to the required size
        rmsg->setPeersArraySize(iMaxTruePeerCount);
    }


    //if there are relay peers to fill
    if(  iMaxRelayPeersCount > 0 )
    {
        // temporary peer to add to the response
        PEER ttpeer;
        //number of relay peers which are included as true peers.
        int iExcludedRelayCount(0);

        // peers added
        set<int> added_peers;

        //if we don't have that much relay peers make the maximum to the amount we have
        if ( iMaxRelayPeersCount > iAvaialbeRelayPeerCount  )
        {
            iMaxRelayPeersCount = iAvaialbeRelayPeerCount;


            BT_LOG_INFO(btLogSinker, "BTTrackerClientHndlrSPD::fillRelayPeers","fillRelayPeers -"
                                            "reduced  iMaxRelayPeersCount to ["<<iMaxRelayPeersCount<<"] to because only ["<<
                                            iAvaialbeRelayPeerCount<<"] relay peers available. ");
        }

        for ( ; (int)added_peers.size() < iMaxRelayPeersCount  ; )

        {
            int iRndPeer = getHostModule()->getNextIndexOfRelayPeerToFill();
            //int iRndPeer = intrand(relayPeers.size());

            if(added_peers.find(iRndPeer) != added_peers.end())
            {
                //we have already added this peer. continue
                continue;
            }

            //if there is peer at this index add it
            if(relayPeers[iRndPeer] != NULL)
            {

                bool bExcludeRelayPeer(false);

                if (getHostModule()->isExcludeRelaysInTruePeerList() == false)
                {
                    //if relay peers are not excluded from the true peer list,
                    //check whether this relay peer already in true peers list
                    for(int j=0; j< (int)rmsg->peersArraySize(); j++)
                    {
                        if( strcmp ((rmsg->peers(j)).peerId.c_str(),  ((BTTrackerStructBase*)relayPeers[iRndPeer])->peerId().c_str() ) == 0 )
                        {
                            bExcludeRelayPeer=true;
                            break;
                        }
                    }

                }
                else
                {
                    //this means relay peers are not added in the true peer list,
                    //and relay peers are not considered as true peers when they are participating in the swarm.
                    //if that is the case a relay peer is in true peer set means it is a relay peer which has the vulnerability
                    //and now participate in the swarm as a true peer.
                    //Hence we should not add that peer as a relay peer.
                    if ( getHostModule()->containsPeer(((BTTrackerStructBase*)relayPeers[iRndPeer])->peerId()) != -1 )
                    {
                        bExcludeRelayPeer = true;
                        getHostModule()->markRelayPeerAsExcluded(iRndPeer);
                        //we need to renew the available relay peer count since we just excluded a one
                        iAvaialbeRelayPeerCount = getHostModule()->getMaxNumberOfAvailableRelayPeersToFill();

                    }

                }

                if(!bExcludeRelayPeer)
                {
                    //This announcing peer also could be a relay peer.
                    //So this particular index may be give us the same peer from relay peer array.
                    //We should not add the same peer requesting in the response
                    if(amsg->peerId()  == ((BTTrackerStructBase*)relayPeers[iRndPeer])->peerId())
                        continue;

                    added_peers.insert(iRndPeer);
//                    BT_LOG_DETAIL(btLogSinker, "BTTrackerClientHndlrSPD::fillPeersInResponse",
//                            "fillPeersInResponse - added peer "<< ((BTTrackerStructBase*)relayPeers[iRndPeer])->peerId()
//                            <<"index ["<<iRndPeer<<"]");
                }
                else
                {
                    iExcludedRelayCount++;
                    //there may be case where we don't have enough relay peers to add
                    //since we have excluded many relay peers due to exclusion criteria
                    //iMaxRelayPeersCount is not calculated with considering that.

                    if ( iAvaialbeRelayPeerCount - iExcludedRelayCount < iMaxRelayPeersCount)
                    {
                        BT_LOG_INFO(btLogSinker, "BTTrackerClientHndlrSPD::fillRelayPeers","fillRelayPeers -"
                                "reducing iMaxRelayPeersCount from ["<<iMaxRelayPeersCount<<"] to ["<<
                                iAvaialbeRelayPeerCount - iExcludedRelayCount<<"] since not enough relay peers to add");

                        iMaxRelayPeersCount = iAvaialbeRelayPeerCount - iExcludedRelayCount;
                    }
                }
            }
        }

        getHostModule()->checkSelectedRelaysAreViable(added_peers);

        fillPeersinToMsg(rmsg, iMaxTruePeerCount, added_peers, relayPeers, no_peer_id);
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
        BT_LOG_DEBUG(btLogSinker, "BTTrackerClientHndlrSPD::fillPeersInResponse", "fillPeersInResponse - Avoiding filling peers"
                " for relay hash announce. Client details [address="<< getSocket()->getRemoteAddress()
                << ", port=" << getSocket()->getRemotePort() << "]");
        return;
    }

    //This message should be a BTTrackerMsgAnnounceSPD message
    BTTrackerMsgAnnounceSPD* pSPDMsg= dynamic_cast<BTTrackerMsgAnnounceSPD*>(amsg);
    if(pSPDMsg == NULL)
    {
        throw cRuntimeError
            ("BTTrackerClientHandlerSPD::fillPeersInResponse - received a Message from client which is not a BTTrackerMsgAnnounceSPD message");
    }

//    BT_LOG_INFO(btLogSinker, "BTTrackerClientHndlrSPD::fillPeersInResponse", "Is seed ["<<seed<<"] current true peer count ["<<
//            getHostModule()->peers().size()<<"] seed count ["<<);

    PEER_FILL_METHOD fillMethod = getHostModule()->getPeerFillMethod();
    if (fillMethod == FILL_ALL)
    {
        // let super class to fill true peers on its will
        BTTrackerClientHandlerBase::fillPeersInResponse(amsg, rmsg, seed, no_peer_id);
    }
    else if (fillMethod == ONLY_SEEDERS)
    {
        fillOnlySeeders(amsg, rmsg, pSPDMsg->seeder(), no_peer_id);
    }
    else if(fillMethod == HIDE_DOWNLOADERS)
    {
        fillWithoutDownloaders(amsg, rmsg, pSPDMsg->seeder(), no_peer_id);
    }
    else
    {
        throw cRuntimeError("Unknown peer fill method [%d] specified for tracker", fillMethod);
    }

    //then we start our work
    fillRelayPeers(rmsg, pSPDMsg, amsg, no_peer_id);

    if (getHostModule()->isblackListerPeerFilteringEnabled())
    {
        removeBlackListedPeersFromResponse(rmsg);
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
    BT_LOG_INFO(btLogSinker, "BTTrackerClientHndlrSPD::determinePeerMix",
            "Relay Peer Percentage ["<<dRelayPeerPcntg<<"] Available True Peer Count ["<<iCurrenTruePeerCountinRes<<
            "], Available Relay Peer Count["<<_iAvailableRelayPeerCount<<"]. In Response True Peer count ["<<_iTruePeerCount
            <<"] Relay Peer Count ["<<_iRelayPeerCount<<"]");
}

void BTTrackerClientHandlerSPD::fillWithoutDownloaders(BTTrackerMsgAnnounce* amsg, BTTrackerMsgResponse* rmsg, bool seed, bool no_peer_id)
{
    // get the peers pool
    cArray& peers               = getHostModule()->peers();
    BT_LOG_INFO(btLogSinker, "BTTrackerClientHandlerSPD::fillWithoutDownloaders",
            "fillWithoutDownloaders, peer array size ["<<peers.size()<<"] is seed ["<<seed<<"]");
    // peers added
    set<int> added_peers            = set<int>();


    int iMaxPeersInReply = getHostModule()->maxPeersInReply();

    int iStart = intrand(peers.size());
    int iLimit = peers.size();

    int iCurrentIndex = iStart;
    do
    {
        if (iCurrentIndex >= iLimit)//if we reached the end go the beginning
            iCurrentIndex = 0;
        else
            iCurrentIndex++;    //else keep going

        // the selected peer is the peer that made the announce, ignore
        if(iCurrentIndex == cPeer)
        {
            continue;
        }
        if(peers[iCurrentIndex] == NULL)
        {
            continue;
        }

        BTTrackerStructBaseSPD* pPeerStruct = check_and_cast<BTTrackerStructBaseSPD*>(peers[iCurrentIndex]);
        // whether this peer is like to be published in the peer list
        //if it don't like don't add
        if ( pPeerStruct->isPublishInPeerList() == false )
        {
//            BT_LOG_DETAIL(btLogSinker, "BTTrackerClientHandlerSPD::fillOnlySeeders",
//                    "peer doesn't like to published. ignoring");
            continue;
        }

        // the response is returned to a seed (i.e., do not include seeds in the response)
        if(seed && (BTTrackerStructBase*)peers[iCurrentIndex] && ((BTTrackerStructBase*)peers[iCurrentIndex])->isSeed())
        {
            continue;
        }

        // add the peer to the "added peers" pool
        if((BTTrackerStructBase*)peers[iCurrentIndex])
        {
            added_peers.insert(iCurrentIndex);
        }
    }
    while(iCurrentIndex != iStart && ((int)added_peers.size() <= iMaxPeersInReply ) );

    if (added_peers.size() > 0)
    {
        // traverse the set and fill the response
        fillPeersinToMsg(rmsg, 0, added_peers, peers, no_peer_id);
    }

}

void BTTrackerClientHandlerSPD::fillOnlySeeders(BTTrackerMsgAnnounce* amsg, BTTrackerMsgResponse* rmsg, bool seed, bool no_peer_id)
{
    // get the peers pool
    cArray& peers               = getHostModule()->peers();
    int iSeedCount              = getHostModule()->seeds();
    BT_LOG_INFO(btLogSinker, "BTTrackerClientHandlerSPD::fillOnlySeeders",
            "filling only seeders, current number of available seeders ["<< iSeedCount<<"] peer array size ["<<peers.size()
            <<"] is seed ["<<seed<<"]");
    // peers added
    set<int> added_peers            = set<int>();
    // iterator for the added_peers
    set<int>::iterator it;
    // the number of peers in the reply
    size_t max_peers            = 0;

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
        max_peers = (iSeedCount <= (int)getHostModule()->maxPeersInReply()) ? iSeedCount : getHostModule()->maxPeersInReply();
    }

//    for (int i = 0 ; i < peers.size(); i++)
//    {
//        BT_LOG_DETAIL(btLogSinker, "BTTrackerClientHandlerSPD::fillOnlySeeders","peer at index ["<<i<<"] is ["
//                << ((BTTrackerStructBase*)peers[i])->peerId()<<"]");
//    }
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

        BT_LOG_DETAIL(btLogSinker, "BTTrackerClientHndlrSPD::fillPeersinToMsg",
                "fillPeersinToMsg - adding peer "<< tpeer->peerId()<<"]");


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


BTTrackerStructBase * BTTrackerClientHandlerSPD::createTrackerStructObj(BTTrackerMsgAnnounce* amsg)
{

    BTTrackerStructBase * pRet = new BTTrackerStructBaseSPD(IPvXAddress(getSocket()->getRemoteAddress()), string(amsg->peerId()),
            amsg->peerPort(), string(amsg->key()), simTime(), (amsg->event() == A_COMPLETED) ? true : false);

    return pRet;
}


void BTTrackerClientHandlerSPD::dataArrived(cMessage* msg, bool urgent)
{

    BTSPDPeerBlackListReqMsg* pMsg = dynamic_cast<BTSPDPeerBlackListReqMsg*>(msg);

    if (pMsg != NULL)
    {
        BT_LOG_DEBUG(btLogSinker,"BTTrackerClientHandlerSPD::dataArrived","dataArrived - received BTSPDPeerBlackListReqMsg... attacker array size ["
                <<pMsg->getAttackersArraySize()<<"]");

        for (unsigned int i = 0 ; i < pMsg->getAttackersArraySize() ; i++)
        {
            getHostModule()->blackListClient(pMsg->getAttackers(i) , getSocket()->getRemoteAddress().get4().str());
        }
    }
    else
    {
        BTTrackerClientHandlerBase::dataArrived(msg, urgent );

    }
}

void BTTrackerClientHandlerSPD::removeBlackListedPeersFromResponse(BTTrackerMsgResponse* _pMsg)
{
    BTTrackerMsgResponse oriMsg(*_pMsg);

    std::set<int> peers;


    BT_LOG_DEBUG(btLogSinker,"BTTrackerClientHandlerSPD","removeBlackListedPeersFromResponse - response contained  ["
            <<_pMsg->peersArraySize()<<"] elements before removing black listed peers");


    std::set<int>::iterator itr = peers.begin();
    for ( unsigned int i = 0 ; i < _pMsg->peersArraySize()  ; i++)
    {
        string peerIP = _pMsg->peers(i).ipAddress.str();
        if ( ! getHostModule()->isClientBlackListed(peerIP))
        {
            peers.insert(i);
        }
        else
        {
            BT_LOG_DETAIL(btLogSinker,"BTTrackerClientHandlerSPD","removeBlackListedPeersFromResponse - excluding peer  ["
                    <<peerIP<<"] since it is black listed");
        }
    }

    //now set them to the response

    //first set it to zero, and then to the required sized to make the insertion faster.
    //if we set to the required size directly implementation tries to copy the existing elements.
    _pMsg->setPeersArraySize(0);
    _pMsg->setPeersArraySize(peers.size());

    itr = peers.begin();

    for (unsigned int i = 0 ; itr != peers.end() ; ++itr, ++i)
    {
        _pMsg->setPeers(i, oriMsg.peers(*itr));
    }

    BT_LOG_DEBUG(btLogSinker,"BTTrackerClientHandlerSPD","removeBlackListedPeersFromResponse - after removing black listed peers there are  ["
            <<_pMsg->peersArraySize()<<"] elements ");
}

int BTTrackerClientHandlerSPD::processAnnounceForTrueHashFromRelay(BTTrackerMsgAnnounce* amsg)
{
    BT_LOG_INFO(btLogSinker, "BTTrackerClientHandlerSPD::processAnnounceForTrueHashFromRelay", "Announce request from relay for true hash. client[address="
            << getSocket()->getRemoteAddress() << ", port=" << getSocket()->getRemotePort() << "] with event ["<<amsg->event()<<"] Client ["<<amsg->peerId()<<"]");


    bool bSeed(false);
    bool bPeerPresent = getHostModule()->containRelayinSwarm(amsg->peerId(), bSeed);


    // sanity checks - failures
    // invalid info hash
    if(amsg->infoHash() != getHostModule()->infoHash())
    {
        return A_INVALID_IHASH;
    }
    // no peer id
    if(strlen(amsg->peerId()) == 0)
    {
        return A_INVALID_PEERID;
    }
    // invalid port
    if(amsg->peerPort() == 0)
    {
        return A_INVALID_PORT;
    }



    // differentiate based on the actual message event field
    switch(amsg->event())
    {
        // started event
        case A_STARTED:

            if (!bPeerPresent)
            {
                getHostModule()->addRelayPeerintoSwarm(amsg->peerId(), false);
                getHostModule()->incrementRelayStartedCount();
            }

            // valid announce with started event
            return A_VALID_STARTED;
            break;

        // completed event
        case A_COMPLETED:
            if (!bSeed)
            {
                getHostModule()->addRelayPeerintoSwarm(amsg->peerId(), true);

                getHostModule()->incrementRelaySeedCount();

                getHostModule()->incrementRelayCompletedCount();
            }

            // valid announce with completed event
            return A_VALID_COMPLETED;
            break;

        // normal announce
        case A_NORMAL:
            if (!bPeerPresent)
            {
                getHostModule()->addRelayPeerintoSwarm(amsg->peerId(), false);
            }
            // valid normal announce
            return A_VALID_NORMAL;
            break;

        // stopped event
        case A_STOPPED:

            if (bPeerPresent)
            {
                getHostModule()->removeRelayPeerFromSwarm(amsg->peerId());

                if(bSeed)
                {
                    getHostModule()->decrementRelaySeedCount();
                }
            }


            // valid announce with stopped event
            return A_VALID_STOPPED;
            break;

        // invalid message event field
        default:
            return A_INVALID_EVENT;
    }
}
