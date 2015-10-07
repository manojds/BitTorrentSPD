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
        b_filterBlackListedPeers(false),
        b_ExcludeRelaysInTruePeerList(false)
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

    b_ExcludeRelaysInTruePeerList     = par("excludeRelaysFromTruePeerList");

    unsigned int uiBlackListThreshold = (int)par("blackListThreshold");

    realyPeersNum_var   = 0;

    blckList.initialize(uiBlackListThreshold);

    WATCH(relayPeerPropotionInReply_var);
    WATCH(realyPeersNum_var);
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
    return realyPeersNum_var;
}

/**
 * Set the relay peers count.
 */
void BTTrackerSPD::setRealyPeersNum(size_t peersNum)
{
    realyPeersNum_var = peersNum;
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

/**
 * Get the relay peers who are participating in the swarm.
 */
cArray& BTTrackerSPD::relayPeersInSwarm()
{
    return relayPeersInSwarm_var;
}

void BTTrackerSPD::cleanRemoveRelayPeer(int index)
{
    if (index>=0)
    {
        BTTrackerStructBase* peer = (BTTrackerStructBase*)relayPeers()[index];
        relayPeers().remove(index);
        delete peer;
    }
    else
        opp_error("Cannot delete peer entry. Indicated peer not found in the set.");
}

int BTTrackerSPD::getNextIndexOfRelayPeerToFill()
{
    int iRet(i_NextIndexToFill);

    i_NextIndexToFill = i_NextIndexToFill + intrand(5) + 1 ;

    if ( i_NextIndexToFill >= relayPeers_var.size() )
    {
        i_NextIndexToFill = 0;
    }

    return iRet;
}

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

void BTTrackerSPD::handleMessage(cMessage* msg)
{
    // local handling of the cleanup message
    if(msg->getKind() == EVT_CLN)
    {

        // traverse the peers pool and remove the inactive entries
        for(int i=0; i<relayPeers_var.size(); i++)
        {
            // get an entry
            BTTrackerStructBase* tpeer = (BTTrackerStructBase*)relayPeers_var[i];
            // the entry is not null and is inactive
            if(tpeer && (simTime() - tpeer->lastAnnounce() >= (simtime_t)cleanupInterval_var))
            {
                BT_LOG_INFO(btLogSinker, "BTTrackerSPD::handleMessage","Removing relay peer ["<< tpeer->peerId()
                        <<"] due to inactivity");
                cleanRemoveRelayPeer(tpeer);
                realyPeersNum_var--;
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
    cleanRemovePeer(relayPeers().find(peer));
}


int BTTrackerSPD::containRealyinSwarm(BTTrackerStructBase* obj) const
{
    // temp peer
    BTTrackerStructBase* tpeer;

    // traverse the peers pool to find obj
    for(int i=0; i<relayPeersInSwarm_var.size(); i++)
    {
        // get peer i
        tpeer = (BTTrackerStructBase*)relayPeersInSwarm_var[i];
        // user operator ==
        if(tpeer && obj && (*obj == *tpeer))
        {
            return i;
        }
    }

    // not found
    return -1;
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

void BTTrackerSPD::cleanAndRemoveRelayPeerInSwarm(int index)
{
    if (index>=0)
    {
        BTTrackerStructBase* peer = (BTTrackerStructBase*)relayPeersInSwarm_var[index];
        relayPeersInSwarm_var.remove(index);
        delete peer;
    }
    else
        opp_error("Cannot delete peer entry. Indicated peer not found in the set.");
}

void BTTrackerSPD::writeStats()
{
    BTTrackerBase::writeStats();

    BT_LOG_INFO(btLogSinker, "BTTrackerSPD::writeStats", "******** Tracker Stats ******** - Relay peer count in swarm ["<<relayPeersInSwarm().size()<<
            "] Relay seeder count ["<<i_RelaySeedCount<<"]");



}
