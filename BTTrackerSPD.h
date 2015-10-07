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

#ifndef BTTRACKERRELAYENABLED_H_
#define BTTRACKERRELAYENABLED_H_
#include "../BitTorrent/BTTrackerBase.h"
#include "BTSPDCommon.h"
#include "BTSPDTrackerBlackList.h"


class INET_API BTTrackerSPD: public BTTrackerBase {
public:
    BTTrackerSPD();
    virtual ~BTTrackerSPD();

    const string& relayInfoHash() const;

    int containsRelay(BTTrackerStructBase* obj) const;
    cArray& relayPeers();
    cArray& relayPeersInSwarm();
    size_t  realyPeersNum() const;
    void    setRealyPeersNum(size_t peersNum);

    double  relayPeerPropotionInReply() const;
    void    setRelayPeerPropotionInReply(double relayPeerPropotionInReply);
    bool    useRelayPropotioninRequest() const;
    PEER_FILL_METHOD    getPeerFillMethod() const;
    void    cleanRemoveRelayPeer(int);
    int     getNextIndexOfRelayPeerToFill();

    void    blackListClient(const std::string & _targetIP, const std::string & _sourceIP);
    bool    isClientBlackListed(const std::string & _clientIP);
    bool    isblackListerPeerFilteringEnabled();
    bool    isExcludeRelaysInTruePeerList();

    int     containRealyinSwarm(BTTrackerStructBase* obj) const;

    void    setRelaySeeds(int count);
    int     getRelaySeeds();
    void    incrementRelaySeedCount();
    void    decrementRelaySeedCount();



    void    cleanAndRemoveRelayPeerInSwarm(int index);
protected:
    virtual void initialize();

    virtual void handleMessage(cMessage*);

    void    setRelayInfoHash(const string& infoHash);

    void    cleanRemoveRelayPeer(BTTrackerStructBase* peer);

    virtual void writeStats();







    int                 i_NextIndexToFill;
    size_t              realyPeersNum_var;    // relay peers counter
    double              relayPeerPropotionInReply_var;
    bool                useRelayPropotioninRequest_var;
    PEER_FILL_METHOD    fillMethod;
    string              realyIfoHash;
    cArray              relayPeers_var;   // relay peers container
    cArray              relayPeersInSwarm_var;//container for relay peers who participating in the swarm
    int                 i_RelaySeedCount;
    BTSPDTrackerBlackList blckList;
    bool                b_filterBlackListedPeers;
    bool                b_ExcludeRelaysInTruePeerList;
};

#endif /* BTTRACKERRELAYENABLED_H_ */
