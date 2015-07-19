/*
 * BTSPDTrackerBlackList.h
 *
 *  Created on: Jul 12, 2015
 *      Author: manojd
 */

#ifndef BTSPDTRACKERBLACKLIST_H_
#define BTSPDTRACKERBLACKLIST_H_
#include <string>
#include <set>
#include <map>

using std::string;
using std::set;
using std::map;

class BTSPDTrackerBlackList
{
public:
    BTSPDTrackerBlackList(unsigned int _uiBlackListThreshold);
    virtual ~BTSPDTrackerBlackList();

    void requestToBlackListPeer(const string & _sTarget, const string & _sReqSource);
    bool isPeerBlackListed(const string & _sPeer);


protected:
    unsigned int        ui_BlackListThreshold;
    //map which holds to be black listed peers.
    //key is the peer to be black list.
    //value set holds the peers who proposed to black list the peer.
    //once list size reached the ui_BlackListThreshold peer will be moved to the Black List Set.
    map<string, set<string>* > map_BlackListCandidates;
    set<std::string>    set_BlackList;
};

#endif /* BTSPDTRACKERBLACKLIST_H_ */
