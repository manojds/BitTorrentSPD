/*
 * BTSPDTrackerBlackList.cpp
 *
 *  Created on: Jul 12, 2015
 *      Author: manojd
 */

#include "BTSPDTrackerBlackList.h"
#include "../BitTorrent/BTLogImpl.h"

BTSPDTrackerBlackList::BTSPDTrackerBlackList(unsigned int _uiBlackListThreshold) :
ui_BlackListThreshold(_uiBlackListThreshold)
{


}

BTSPDTrackerBlackList::~BTSPDTrackerBlackList()
{
    map<string, set<string>* >::iterator itr = map_BlackListCandidates.begin();
    for( ; itr != map_BlackListCandidates.end() ; itr++)
    {
        set<string>* pSet = itr->second;
        delete pSet;
    }
    map_BlackListCandidates.clear();
}

void BTSPDTrackerBlackList::requestToBlackListPeer(const string & _sTarget, const string & _sReqSource)
{
    if ( isPeerBlackListed(_sTarget) )
    {
        //peer is already black listed. nothing to do
        return;
    }

    BT_LOG_INFO(btLogSinker, " BTSPDTrackerBlackList::requestToBlackListPeer","black list request from peer["
            <<_sReqSource<<"] target ["<<_sTarget<<"]");

    map<string, set<string>* >::iterator itrMap = map_BlackListCandidates.find(_sTarget);

    set<string>* sourceSet = NULL;
    if (itrMap != map_BlackListCandidates.end())
    {
        sourceSet = itrMap->second;
    }
    else
    {
        sourceSet = new set<string>();
    }

    sourceSet->insert(_sReqSource);

    //check whether peer has exceeded the blacklist threshold
    if (sourceSet->size() >= ui_BlackListThreshold)
    {
        BT_LOG_INFO(btLogSinker, " BTSPDTrackerBlackList::requestToBlackListPeer","black listing peer["<<_sTarget<<"]");

        map_BlackListCandidates.erase(itrMap);
        delete sourceSet;
        sourceSet = NULL;

        set_BlackList.insert(_sTarget);
    }
}

bool BTSPDTrackerBlackList::isPeerBlackListed(const string & _sPeer)
{
    bool bRet(false);

    set<std::string>::iterator itr = set_BlackList.find(_sPeer);

    if (itr != set_BlackList.end())
    {
        bRet = true;
    }

    return bRet;
}

