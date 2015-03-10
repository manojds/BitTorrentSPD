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

#include "BTPeerWireSPD.h"
#include "../BitTorrent/BTLogImpl.h"
#include "../BTTrackerClientBase.h"
#include "BTHostIntrnlMsgsSPD_m.h"
#include "BTThreatHandler.h"
#include <string.h>
#include "BTSPDVulnerablePoint.h"

Define_Module(BTPeerWireSPD);


BTPeerWireSPD::BTPeerWireSPD() {

}

BTPeerWireSPD::~BTPeerWireSPD() {
}

void BTPeerWireSPD::initialize()
{
    BTPeerWireBase::initialize();

    p_ThreatHndlr= (BTThreatHandler*)(getParentModule()->getSubmodule("threatHandler"));

    s_PlatFormType= (getParentModule()->par("plaformType").str());
    //patch information is same as the platform type
    s_PatchInfo=s_PlatFormType;
}

void BTPeerWireSPD::handleSelfMessage(cMessage* msg)
{
    switch (msg->getKind())
    {
        case INTERNAL_TRACKER_COM_MSG:
        {
            BT_LOG_INFO(btLogSinker,"BTPeerWireSPD::handleSelfMessage","["<<this->getParentModule()->getFullName()<<"] instructing communication with the tracker...");

            cMessage * pMsg= createTrackerCommMsg();

            send( pMsg,"btorrentOut");

            break;
        }
        default:
            BTPeerWireBase::handleSelfMessage(msg);
            break;

    }
}

cMessage * BTPeerWireSPD::createTrackerCommMsg()
{
    BTRequestTrackerCommSPD * pMsg(NULL);

    switch (getState())
    {
        case NORMAL:
        case ENDGAME:
        case SEEDER:
        {
            pMsg= new BTRequestTrackerCommSPD(toString(EVT_CONN),EVT_CONN);
            //this seeder flag is to hide the leachers from exposing to others
            pMsg->setSeeder(true);

            break;
        }
        case COMPLETED:
        case SEEDING:
        {
            pMsg= new BTRequestTrackerCommSPD(toString(EVT_COMP),EVT_COMP);
            //this seeder flag is to hide the leachers from exposing to others
            pMsg->setSeeder(true);
            break;
        }
        case EXITING:
        {
            pMsg= new BTRequestTrackerCommSPD(toString(EVT_STOP),EVT_STOP);
            break;
        }
        default:
            error("%s:%d at %s() Invalid client state (STATE = %d). \n", __FILE__, __LINE__, __func__,getState());

    }

    return pMsg;

}

void BTPeerWireSPD::newConnectionFromPeerEstablished(PEER peer, TCPServerThreadBase* thread)
{
    notifyNewAddrToThreatHndlr(peer);

}

void BTPeerWireSPD::newConnectionToPeerEstablished(PEER peer, TCPServerThreadBase* thread)
{
    notifyNewAddrToThreatHndlr(peer);
}

void BTPeerWireSPD::notifyNewAddrToThreatHndlr(const PEER & peer)
{
    if(p_ThreatHndlr)
    {
        char pPort[32];
        snprintf(pPort, 32, "%u", peer.peerPort);
        p_ThreatHndlr->newAddrFound(peer.ipAddress.str(), pPort);
    }
}


void BTPeerWireSPD::downloadCompleted()
{
    BT_LOG_INFO(btLogSinker,"BTPeerWireSPD::handleSelfMessage","["<<this->getParentModule()->getFullName()<<"] Download completed...");

    p_ThreatHndlr->cleanAdversary();

    BTSPDVulnerablePoint * p_VulPnt= check_and_cast<BTSPDVulnerablePoint*>(getParentModule()->getSubmodule("vulnerability"));
    p_VulPnt->vulnerabilityFixed();

}


