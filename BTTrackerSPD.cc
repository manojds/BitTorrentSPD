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

#include "BTTrackerSPD.h"
#include "../BitTorrent/BTLogImpl.h"

Define_Module(BTTrackerSPD);

BTTrackerSPD::BTTrackerSPD():
        i_NextIndexToFill(0),
        fillMethod(FILL_ALL),
        i_RelaySeedCount(0),
        i_RelayCompletedCount(0),
        i_RelayStartedCount(0),
        b_filterBlackListedPeers(false),
        b_ExcludeRelaysInTruePeerList(false),
        b_PoolRelayPeers(false),
        d_RelayPoolFraction(1),
        i_LastConsolidatedRelayIndex(0)
{
    // TODO Auto-generated constructor stub

}

BTTrackerSPD::~BTTrackerSPD() {
    // TODO Auto-generated destructor stub
}

void BTTrackerSPD::initialize()
{
    BTTrackerBase::initialize();

    relayPeerPropotionInReply_var   = (double)par("relayPeerPropotionInReply");
    useRelayPropotioninRequest_var  = par("useRelayPropotioninRequest");
    fillMethod                      = (PEER_FILL_METHOD)(int)par("fillMethod");
    realyIfoHash                    = par("realyInfoHash").stdstringValue ();

    b_filterBlackListedPeers        = par("filterBlackListedPeers");

    b_ExcludeRelaysInTruePeerList   = par("excludeRelaysFromTruePeerList");

    b_PoolRelayPeers                = par("poolRelayPeers");

    d_RelayPoolFraction             = par("relayPoolFraction");

    b_ObscureSeeders                = par("obscureSeeders");

    unsigned int uiBlackListThreshold = (int)par("blackListThreshold");

    BT_LOG_ESSEN(btLogSinker, "BTTrackerClientHandlerB::initialize", "TrackerSPD initializing.... \n"
            "PoolRelayPeers                 - "<<b_PoolRelayPeers<<"\n"
            "relayPoolFraction              - "<<d_RelayPoolFraction<<"\n"
            "fill Method                    - "<<fillMethodToString(fillMethod)<<"\n"
            "useRelayPeerPropotionInRequest - "<<useRelayPropotioninRequest_var<<"\n"
            "relay peer Proportion          - "<<relayPeerPropotionInReply_var<<"\n"
            "ExcludeRelaysInTruePeerList    - "<<b_ExcludeRelaysInTruePeerList<<"\n"
            "ObscureSeeders                 - "<<b_ObscureSeeders<<"\n"
            "filterBlackListedPeers         - "<<b_filterBlackListedPeers<<"\n"
            "BlackListThreshold             - "<<uiBlackListThreshold);



    relayPeersNum_var   = 0;

    blckList.initialize(uiBlackListThreshold);

    WATCH(relayPeerPropotionInReply_var);
    WATCH(relayPeersNum_var);
    WATCH_OBJ(relayPeers_var);
}

/**
 * Returns the position of obj inside the relay peers container (if it is contained)
 * or -1 if obj is not found.
 */
int BTTrackerSPD::containsRelay(BTTrackerStructBase* obj) const
{
    // temp peer
    BTTrackerStructBase* tpeer;

    // traverse the peers pool to find obj
    for(int i=0; i<relayPeers_var.size(); i++)
    {
        // get peer i
        tpeer = (BTTrackerStructBase*)relayPeers_var[i];
        // user operator ==
        if(tpeer && obj && (*obj == *tpeer))
        {
            return i;
        }
    }

    // not found
    return -1;
}

int BTTrackerSPD::containsRelay(const std::string & _sPeerID) const
{
    int iIndex(-1);

    std::map<std::string, int>::const_iterator itr = map_RelayPeers.find(_sPeerID);
    if ( itr != map_RelayPeers.end())
    {
        iIndex = itr->second;
    }

    return iIndex;
}

/**
 * Get the maximum number of peers which can be included in a response.
 */
double BTTrackerSPD::relayPeerPropotionInReply() const
{
    return relayPeerPropotionInReply_var;
}

/**
 * Set the maximum number of peers which can be included in a response.
 */
void BTTrackerSPD::setRelayPeerPropotionInReply(double relayPeerPropotionInReply)
{
    relayPeerPropotionInReply_var = relayPeerPropotionInReply;
}

/*
 * Get the flag which indicate whether to use the requested relay peer ration by the client
 */
bool BTTrackerSPD::useRelayPropotioninRequest() const
{
    return useRelayPropotioninRequest_var;
}

PEER_FILL_METHOD BTTrackerSPD::getPeerFillMethod() const
{
    return fillMethod;

}

/**
 * Get the relay peers count.
 */
size_t BTTrackerSPD::realyPeersNum() const
{
    return relayPeersNum_var;
}

/**
 * Set the relay peers count.
 */
void BTTrackerSPD::setRealyPeersNum(size_t peersNum)
{
    relayPeersNum_var = peersNum;
}

/**
 * Get the relay info hash of tracker.
 * This is the info hash of the .torrent file which the tracker monitors.
 */
const string& BTTrackerSPD::relayInfoHash() const
{
    return realyIfoHash;
}

/**
 * Set the relay info hash of tracker.
 * This is the info hash of the .torrent file which the tracker monitors.
 */
void BTTrackerSPD::setRelayInfoHash(const string& infoHash)
{
    realyIfoHash = infoHash;
}

/**
 * Get the relay peers container.
 */
cArray& BTTrackerSPD::relayPeers()
{
    return relayPeers_var;
}



//int BTTrackerSPD::getNextIndexOfRelayPeerToFill()
//{
//    int iRet(i_NextIndexToFill);
//
//    i_NextIndexToFill = i_NextIndexToFill + intrand(5) + 1 ;
//
//    if ( i_NextIndexToFill >= relayPeers_var.size() )
//    {
//        i_NextIndexToFill = 0;
//    }
//
//    return iRet;
//}

void BTTrackerSPD::blackListClient(const std::string & _targetIP, const std::string & _sourceIP)
{
    if (b_filterBlackListedPeers)
        blckList.requestToBlackListPeer(_targetIP, _sourceIP);
}

bool BTTrackerSPD::isClientBlackListed(const std::string & _clientIP)
{
    if (b_filterBlackListedPeers)
        return blckList.isPeerBlackListed(_clientIP);
    else
        return false;
}

bool BTTrackerSPD::isblackListerPeerFilteringEnabled()
{
    return b_filterBlackListedPeers;
}

bool BTTrackerSPD::isExcludeRelaysInTruePeerList()
{
    return b_ExcludeRelaysInTruePeerList;
}

bool BTTrackerSPD::isObscureSeedersEnabled()
{
    return b_ObscureSeeders;
}
void BTTrackerSPD::handleMessage(cMessage* msg)
{
    // local handling of the cleanup message
    if(msg->getKind() == EVT_CLN)
    {
        BT_LOG_INFO(btLogSinker, "BTTrackerSPD::handleMessage", "Event Cleanup timer fired. current time ["<<simTime()<<"], trying to clean relay peers..");

        // traverse the peers pool and remove the inactive entries
        for(int i=0; i<relayPeers_var.size(); i++)
        {
            // get an entry
            BTTrackerStructBase* tpeer = (BTTrackerStructBase*)relayPeers_var[i];
            // the entry is not null and is inactive
            if(tpeer && (simTime() - tpeer->lastAnnounce() >= (simtime_t)cleanupInterval_var))
            {
                BT_LOG_INFO(btLogSinker, "BTTrackerSPD::handleMessage","Removing relay peer ["<< tpeer->peerId()
                        <<"] due to inactivity.. Time ["<<simTime()<<"]");
                cleanRemoveRelayPeer(i);
            }

        }

    }

    BTTrackerBase::handleMessage(msg);
}

/**
 * Remove a relay peer from the peer set ensuring memory deallocation.
 */
void BTTrackerSPD::cleanRemoveRelayPeer(BTTrackerStructBase* peer)
{
    cleanRemoveRelayPeer(relayPeers().find(peer));
}

void BTTrackerSPD::cleanRemoveRelayPeer(int index)
{
    if (index>=0)
    {

        BTTrackerStructBase* peer = (BTTrackerStructBase*)relayPeers()[index];

        BT_LOG_INFO(btLogSinker, "BTTrackerClientHandlerB::cleanRemoveRelayPeer", "Removing relay peer ["<<peer->peerId()<<
                "] IP ["<<peer->ipAddress()<<"] port ["<<peer->peerPort()<<"]");

        relayPeers().remove(index);
        relayPeersNum_var--;
        removeRelayPeerFromtheMap(peer->peerId());
        //if it is a excluded one remove it from teh excluded set
        set_ExcludedRelays.erase(index);

        removePeerFromThePool(index);

        delete peer;
    }
    else
        opp_error("Cannot delete peer entry. Indicated peer not found in the set.");
}



void BTTrackerSPD::insertRelayPeerIntoMap(const std::string & _sPeerID, int _iIndex)
{
    std::map<std::string, int>::iterator itr = map_RelayPeers.find(_sPeerID);
    if ( itr == map_RelayPeers.end())
    {
        map_RelayPeers[_sPeerID] = _iIndex;
    }
    else
    {
        throw cRuntimeError("BTTrackerSPD::insertPeerIntoMap - Relay Peer [%s] already present in the map. current index [%s], requested index [%s]",
                _sPeerID.c_str(), itr->second, _iIndex);
    }

}
void BTTrackerSPD::removeRelayPeerFromtheMap(const std::string & _sPeerID)
{
    std::map<std::string, int>::iterator itr = map_RelayPeers.find(_sPeerID);
    if ( itr != map_RelayPeers.end())
    {
        map_RelayPeers.erase(itr);
    }
    else
    {
        throw cRuntimeError("BTTrackerSPD::removePeerFromtheMap - Relay Peer [%s] not present in the map.", _sPeerID.c_str());
    }
}


/*!
 * Marks a relay peers as excluded.
 * After that, this particular peer will not be used as a relay peer.
 */
void BTTrackerSPD::markRelayPeerAsExcluded(int _iPeerIndex)
{
    BT_LOG_INFO(btLogSinker, "BTTrackerSPD::markRelayPeerAsExcluded", "Excluding relay peer  ["<<_iPeerIndex<<
            "] from relay peers, peer ID ["<<((BTTrackerStructBase*)relayPeers()[_iPeerIndex])->peerId() <<"]");

    set_ExcludedRelays.insert(_iPeerIndex);

    removePeerFromThePool(_iPeerIndex);
}

int BTTrackerSPD::addRelayPeer(BTTrackerStructBase* tpeer)
{
    int iIndex = relayPeers_var.add(tpeer);
    relayPeersNum_var++;
    insertRelayPeerIntoMap(tpeer->peerId(), iIndex);

    consolidateRelayPeerPool();

    return iIndex;

}

bool BTTrackerSPD::containRelayinSwarm(const std::string & _sPeerID, bool & _bIsSeed) const
{
    _bIsSeed = false;
    std::map<std::string, bool>::const_iterator itr = relayPeersInSwarm_var.find(_sPeerID);

    if (relayPeersInSwarm_var.end() != itr)
    {
        _bIsSeed = itr->second;
        return true;
    }
    else
    {
        return false;
    }
}

void BTTrackerSPD::removePeerFromThePool(int _iPeerIndex)
{
    if (b_PoolRelayPeers)
    {
        int ret = set_RelayPeerPool.erase(_iPeerIndex);

        //if Peer is removed from the Pool, Consolidate again
        if (ret > 0)
        {
            consolidateRelayPeerPool();
        }
    }
}

void BTTrackerSPD::consolidateRelayPeerPool()
{
    if (b_PoolRelayPeers)
    {
        int iAddedCount(0);
        int iRelayPoolSize = d_RelayPoolFraction * peersNum_var;
        int iPoolSizeb4Consolidation = set_RelayPeerPool.size();    //only for debug

        //we go full round around relay peer array if necessary
        //and also do work only if relay pool size lower than the specified pool size

        for ( unsigned int i = 0 ; (i < relayPeers_var.size()) && (set_RelayPeerPool.size() < iRelayPoolSize) ; i++ )
        {
            i_LastConsolidatedRelayIndex++;

            if (i_LastConsolidatedRelayIndex >= relayPeers_var.size() )
            {
                i_LastConsolidatedRelayIndex = 0;
            }

            BTTrackerStructBase* peer = (BTTrackerStructBase*) relayPeers_var[i_LastConsolidatedRelayIndex];

            if (peer == NULL)
                continue;

            //if peer is already not in the pool an peer is not on the excluded set add peer to the pool.

            if (set_RelayPeerPool.find(i_LastConsolidatedRelayIndex) == set_RelayPeerPool.end() &&
                    set_ExcludedRelays.find(i_LastConsolidatedRelayIndex) == set_ExcludedRelays.end() )
            {
                set_RelayPeerPool.insert(i_LastConsolidatedRelayIndex);
                iAddedCount++;

            }
        }

        BT_LOG_ESSEN(btLogSinker, "BTTrackerSPD::consolidateRelayPeerPool", "Consolidated Relay peer Pool, Current Pool size ["<<set_RelayPeerPool.size()
                << "], ideal Pool Size as of now ["<<iRelayPoolSize <<"], pool size before consolidation ["<<iPoolSizeb4Consolidation<<"] Relay peer Array size ["<<
                relayPeers_var.size()<<"], available relay peers num ["<< relayPeersNum_var<<"] LastConsolidatedIndex ["<< i_LastConsolidatedRelayIndex<<
                "], Relay Exclude set size [" <<set_ExcludedRelays.size()<<"] Added ["<<iAddedCount <<"] relays to the pool.");

        //assertions
        if ( iRelayPoolSize >  (relayPeersNum_var - set_ExcludedRelays.size()) )
        {
            ASSERT(set_RelayPeerPool.size() == (relayPeersNum_var - set_ExcludedRelays.size()) );
        }
    }
}

int BTTrackerSPD::getMaxNumberOfAvailableRelayPeersToFill()
{
    if (b_PoolRelayPeers)
    {
        return set_RelayPeerPool.size();
    }
    else
    {
        return relayPeersNum_var - set_ExcludedRelays.size();
    }
}

int BTTrackerSPD::getRelayPoolSize()
{
    return set_RelayPeerPool.size();
}

int BTTrackerSPD::getExcludedRelaySetSize()
{
    return set_ExcludedRelays.size();
}

void BTTrackerSPD::checkSelectedRelaysAreViable(const set<int> & _setRelays)
{
#ifdef MJP_DEBUG
    set<int>::const_iterator itr = _setRelays.begin();

    for ( ; _setRelays.end() != itr ; ++itr )
    {
        if (b_PoolRelayPeers)
        {
            //if relay peer pooling is enabled, the peer should be in the pool
            ASSERT ( set_RelayPeerPool.find(*itr) !=  set_RelayPeerPool.end() );
        }
        else if (b_ExcludeRelaysInTruePeerList)
        {
            //if relay peers are excluded from the true peers when participating in the swarm
            //the relay peer should NOT be in excluded peer list
            ASSERT ( set_ExcludedRelays.find(*itr) ==  set_ExcludedRelays.end() );
        }
    }

#endif
}

int BTTrackerSPD::getNextIndexOfRelayPeerToFill()
{
    int index (0);
    while (true)
    {
        index = intrand(relayPeers().size() + 1);

        if (b_PoolRelayPeers)
        {
            //use peers which are only in pool
            if (set_RelayPeerPool.find(index) !=  set_RelayPeerPool.end())
            {
                return index;
            }
            else
                continue; // if peer is not in the pool, try another one
        }
        else
        {
            return index;
        }
    }

}

void BTTrackerSPD::addRelayPeerintoSwarm(const std::string & _sPeerID, bool isSeed)
{
    relayPeersInSwarm_var[_sPeerID] = isSeed;
}

void BTTrackerSPD::removeRelayPeerFromSwarm(const std::string & _sPeerID)
{
    relayPeersInSwarm_var.erase(_sPeerID);

}

void BTTrackerSPD::setRelaySeeds(int count)
{
    i_RelaySeedCount = count;

}

int BTTrackerSPD::getRelaySeeds()
{
    return i_RelaySeedCount;
}

void BTTrackerSPD::incrementRelaySeedCount()
{
    i_RelaySeedCount++;
}

void BTTrackerSPD::decrementRelaySeedCount()
{
    i_RelaySeedCount--;
}

void BTTrackerSPD::incrementRelayCompletedCount()
{
    i_RelayCompletedCount++;
}

void BTTrackerSPD::incrementRelayStartedCount()
{
    i_RelayStartedCount++;
}
void BTTrackerSPD::writeStats()
{
    BTTrackerBase::writeStats();

    BT_LOG_ESSEN(btLogSinker, "BTTrackerSPD::writeStats", "******** Tracker Stats Relay ******** - Time ["<<simTime() <<"] Total Relay Count ["<<realyPeersNum()
            <<"] Relay peer Started Count in Swarm ["<<i_RelayStartedCount<<"] Relay peer count in swarm ["<<relayPeersInSwarm_var.size()<<
            "] Relay seeder count ["<<i_RelaySeedCount<<"], relay completed count ["<<i_RelayCompletedCount<<"]");

}
