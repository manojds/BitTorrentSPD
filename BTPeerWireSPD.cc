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
#include "BTSPDConnTrack_m.h"
#include "BTSPDCommonMsgTypes.h"
#include <algorithm>
#include "BTPeerWireClientHandlerBase.h"
#include "../BTMsgFactory.h"

Define_Module(BTPeerWireSPD);

#define INTERNAL_NODE_CREATION_MSG_TYPE  298


BTPeerWireSPD::BTPeerWireSPD() :
        b_enableConnMapDumping(false),
        b_PublishTrackerOnCompletion(false),
        b_PublishMeByTracker(true),
        b_DisconnectBadConnections(false),
        b_DownloadCompleted(false),
        b_DoNotActivelyParticipateOnCompletion(false),
        b_PassiveConnectionsBlocked(false),
        i_PassiveConnCount(0),
        i_MaxPassiveConnCount(0),
        fillMethod(FILL_ALL),
        p_ThreatHndlr(NULL),
        p_ConnTracker(NULL),
        p_StatModule(NULL),
        p_NotifyNodeCreation(NULL)
{

}

BTPeerWireSPD::~BTPeerWireSPD()
{
    if( p_NotifyNodeCreation != NULL )
        cancelAndDelete(p_NotifyNodeCreation);
}

void BTPeerWireSPD::initialize()
{
    BTPeerWireBase::initialize();

    p_ThreatHndlr= (BTThreatHandler*)(getParentModule()->getSubmodule("threatHandler"));

    p_StatModule = check_and_cast<BTStatisticsSPD*>(btStatistics);

    s_PlatFormType= (getParentModule()->par("plaformType").str());
    //patch information is same as the platform type
    s_PatchInfo=s_PlatFormType;

    b_enableConnMapDumping      = par("enableConnMapDumping");
    b_PublishTrackerOnCompletion= par("publishtoTrackerWhenDownloadComplete");
    b_PublishMeByTracker        = par("publishMeByTracker");
    b_DisconnectBadConnections  = par("disconnectBadConnections");
    b_DoNotActivelyParticipateOnCompletion = par("doNotActivelyParticipateOnDownloadCompletion");
    fillMethod                      = (PEER_FILL_METHOD)(int)par("fillMethod");

    double  dMaxPassiveConnFraction = par("maxPassiveConnCountFraction");
    i_MaxPassiveConnCount        = maxNumConnections() * dMaxPassiveConnFraction;
    i_PassiveConnCount           = 0;


    BT_LOG_DETAIL( btLogSinker,"BTPeerWireSPD::initialize","["<<this->getParentModule()->getFullName()<<
                        "] Max Passive Connection count ["<<i_MaxPassiveConnCount<<"]");


    p_NotifyNodeCreation = new cMessage("INTERNAL_NODE_CREATION_MSG_TYPE",
            INTERNAL_NODE_CREATION_MSG_TYPE);

    scheduleAt(simTime(), p_NotifyNodeCreation);

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
        case INTERNAL_NODE_CREATION_MSG_TYPE:
            handleNodeCreationEvent();
            break;
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
            pMsg= new BTRequestTrackerCommSPD(toString(EVT_CONN),EVT_CONN);
            break;
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
    if(pMsg)
    {
        pMsg->setPublishInPeerList(b_PublishMeByTracker);
    }

    return pMsg;

}


void BTPeerWireSPD::RescheduleTrackerCommAt(simtime_t t)
{
    if (evtTrackerComm->isScheduled())
    {
        cancelEvent(evtTrackerComm);
    }

    scheduleTrackerCommAt(t);
}

void BTPeerWireSPD::downloadCompleted(simtime_t _tDuration)
{
    BT_LOG_INFO(btLogSinker,"BTPeerWireSPD::handleSelfMessage","["<<this->getParentModule()->getFullName()<<"] Download completed... in ["<<_tDuration<<" sec] ");

    p_ThreatHndlr->cleanAdversary();

    BTSPDVulnerablePoint * p_VulPnt= check_and_cast<BTSPDVulnerablePoint*>(getParentModule()->getSubmodule("vulnerability"));
    p_VulPnt->vulnerabilityFixed();

    p_StatModule->nodeCompletedTheDownload(this->getParentModule()->getFullName());

    //now I can safely publish my self in peerlist because I am not vulnerable anymore
    b_PublishMeByTracker = true;

    b_DownloadCompleted = true;

    if (b_DoNotActivelyParticipateOnCompletion)
        disconnectAllActiveConns();

    notifyDwlCompleteToConnMapper(_tDuration);

    if (b_PublishTrackerOnCompletion)
        RescheduleTrackerCommAt(simTime());



}

void BTPeerWireSPD::scheduleConnections(BTTrackerMsgResponse* msg)
{
    //if download is completed and do not actively participate is set do not
    //initiate new connections

    if(getState() >= COMPLETED && b_DoNotActivelyParticipateOnCompletion == true)
    {
        BT_LOG_INFO( btLogSinker,"BTPeerWireSPD::scheduleConnections","["<<this->getParentModule()->getFullName()<<
                "] not scheduling connection due to Active participation is disabled after download completion.");
        return;
    }
    else
    {
        BTPeerWireBase::scheduleConnections(msg);
    }

}

void BTPeerWireSPD::disconnectAllActiveConns()
{
    BT_LOG_INFO( btLogSinker,"BTPeerWireSPD::disconnectAllActiveConns","["<<this->getParentModule()->getFullName()<<
            "] Closing All Active connections with other peers.");

    BTPeerWireClientHandlerBase *thread(NULL);
    PeerEntryVector peerVector = peerState.getVector();

    for (unsigned int i=0; i<peerVector.size(); i++)
    {
        PeerEntry entry= peerVector[i];
        thread = check_and_cast<BTPeerWireClientHandlerBase *>(entry.getPeerThread());
        if (!thread)
            error("%s:%d at %s() Inconsistent thread state, could not find peer thread. \n", __FILE__, __LINE__, __func__);

        TCPServerThreadBase * pThreadBase = (TCPServerThreadBase *)thread;

        if (thread->activeConnection())
        {
            BT_LOG_INFO( btLogSinker,"BTPeerWireSPD::disconnectAllActiveConns","["<<this->getParentModule()->getFullName()<<
                    "] Disconnecting Active Connection with peer ["<< entry.getPeerID()<<"].");

            pThreadBase->timerExpired(BTMsgFactory::getInstance()->getMessageObj(toString(CLOSE_CONNECTION_TIMER),CLOSE_CONNECTION_TIMER));
        }


    }
}

void BTPeerWireSPD::newConnectionFromPeerEstablished(PEER peer, TCPServerThreadBase* thread)
{
    checkRcvdConnIsViable(peer);

    i_PassiveConnCount++;

    notifyNewAddrToThreatHndlr(peer, false);
    notifyNewConnToConnMapper(peer, false);
}

void BTPeerWireSPD::checkRcvdConnIsViable(const PEER & peer)
{
    //error checking
    if (b_DownloadCompleted == false && fillMethod == HIDE_DOWNLOADERS && b_PublishMeByTracker == false)
    {
        BT_LOG_ERROR( btLogSinker,"BTPeerWireSPD::newConnectionFromPeerEstablished","["<<
                this->getParentModule()->getFullName()<<"] remote peer"<< peer.peerId<<
                " b_DownloadCompleted is false, fillMethod is HIDE_DOWNLOADERS and b_PublishMeByTracker is false");

        throw cRuntimeError("connection received from peer when it is not intended."
                " b_DownloadCompleted is false, fillMethod is HIDE_DOWNLOADERS and b_PublishMeByTracker is false");
    }
    else if (fillMethod == ONLY_SEEDERS )
    {
        if ( getState() < SEEDING )
        {
            BT_LOG_ERROR( btLogSinker,"BTPeerWireSPD::newConnectionFromPeerEstablished","["<<
                    this->getParentModule()->getFullName()<<"] remote peer"<< peer.peerId<<
                    " I am not a seeder or not seeding, fillMethod is ONLY_SEEDERS . Current state ["<<getState()<<"]");

            throw cRuntimeError("connection received from peer when it is not intended."
                    " I am not a seeder or not seeding, fillMethod is ONLY_SEEDERS ");
        }
    }
}

void BTPeerWireSPD::newConnectionToPeerEstablished(PEER peer, TCPServerThreadBase* thread)
{
    notifyNewConnToConnMapper(peer, true);
}

void BTPeerWireSPD::peerFoundFromTracker(PEER peer)
{
   BT_LOG_DETAIL(btLogSinker, "BTPeerWireSPD::peerFoundFromTracker","["<< this->getParentModule()->getFullName()<<
			"] New Address found from tracker. node ["<< peer.peerId<<"] Address ["<<peer.ipAddress<<"]");
   notifyNewAddrToThreatHndlr(peer, true);

}

void BTPeerWireSPD::connectionLostFromPeer(PEER peer, bool isActiveConn)
{
    if (!isActiveConn)
    {
        --i_PassiveConnCount;
    }

    notifyConnDropToConnMapper(peer);
}

void BTPeerWireSPD::notifyNewAddrToThreatHndlr(const PEER & peer, bool isActiveConn)
{
    if(p_ThreatHndlr)
    {
        char pPort[32];
        snprintf(pPort, 32, "%u", peer.peerPort);
        p_ThreatHndlr->newAddrFound(peer.peerId.c_str(), peer.ipAddress.str(), pPort, isActiveConn);
    }
}

void BTPeerWireSPD::handleNodeCreationEvent()
{
    if ( b_enableConnMapDumping)
    {
        const char * pModPath=par("connTrackerModulePath").stringValue();
        //BT_LOG_INFO(btLogSinker, " BTSPDConnTrackerFunc::initialize","connTrackerModulePath is ["<<pModPath <<"]\n");
        p_ConnTracker = (cSimpleModule*)simulation.getModuleByPath(pModPath);

        notifyNodeCreationToConnMapper();
    }

    notifynodeCreationToStatModule();


}

void BTPeerWireSPD::notifynodeCreationToStatModule()
{
    p_StatModule->nodeCreated(this->getParentModule()->getFullName());
}

void BTPeerWireSPD::notifyNodeCreationToConnMapper()
{
    if ( b_enableConnMapDumping)
    {
        IPvXAddress ipAddr = getMyIPAddr();
        BT_LOG_INFO(btLogSinker,"BTPeerWireSPD::notifyNewConnToConnMapper","["<<this->getParentModule()->getFullName()
                <<"] myIP is ["<<ipAddr.str()<<"]");

        BTSPDConnTrackNodeCreationMsg* msgNodeCreation =
                new BTSPDConnTrackNodeCreationMsg("BTSPD_CONN_TRACK_NODE_CREATION_MSG_TYPE",
                        BTSPD_CONN_TRACK_NODE_CREATION_MSG_TYPE);

        msgNodeCreation->setMyName(this->getParentModule()->getFullName());
        msgNodeCreation->setMyIP(ipAddr.str().c_str());
        msgNodeCreation->setCreationTime(simTime().dbl());

        sendDirect(msgNodeCreation,  p_ConnTracker, p_ConnTracker->findGate("direct_in"));
    }
}

void BTPeerWireSPD::notifyNewConnToConnMapper(const PEER & peer, bool isActiveConn)
{
    if ( b_enableConnMapDumping)
    {
        //BT_LOG_INFO(btLogSinker,"BTPeerWireSPD::notifyNewConnToConnMapper","["<<this->getParentModule()->getFullName()<<"] sending Connection map update...");

        BTSPDConnTrackNewConnMsg* newConnMsg =
                new BTSPDConnTrackNewConnMsg("BTSPD_CONN_TRACK_NEWCONN_MSG_TYPE",
                        BTSPD_CONN_TRACK_NEWCONN_MSG_TYPE);

        newConnMsg->setMyName(this->getParentModule()->getFullName());
        newConnMsg->setRemoteIP(peer.ipAddress.str().c_str());
        newConnMsg->setActiveConn(isActiveConn);
        sendDirect(newConnMsg,  p_ConnTracker, p_ConnTracker->findGate("direct_in"));
    }
}

void BTPeerWireSPD::notifyConnDropToConnMapper(const PEER & peer)
{
    if ( b_enableConnMapDumping)
    {
        //BT_LOG_INFO(btLogSinker,"BTPeerWireSPD::notifyNewConnToConnMapper","["<<this->getParentModule()->getFullName()<<"] sending Connection map update...");

        BTSPDConnTrackConnDropMsg* connDropMsg =
                new BTSPDConnTrackConnDropMsg("BTSPD_CONN_TRACK_CONN_DROP_MSG_TYPE",
                        BTSPD_CONN_TRACK_CONN_DROP_MSG_TYPE);

        connDropMsg->setMyName(this->getParentModule()->getFullName());
        connDropMsg->setRemoteIP(peer.ipAddress.str().c_str());

        sendDirect(connDropMsg,  p_ConnTracker, p_ConnTracker->findGate("direct_in"));
    }
}



void BTPeerWireSPD::notifyDwlCompleteToConnMapper(simtime_t _tDuration)
{
    if ( b_enableConnMapDumping)
    {
        //BT_LOG_INFO(btLogSinker,"BTPeerWireSPD::notifyNewConnToConnMapper","["<<this->getParentModule()->getFullName()<<"] sending Connection map update...");

        BTSPDConnTrackDwlCompeteMsg* msgDWL =
                new BTSPDConnTrackDwlCompeteMsg("BTSPD_CONN_TRACK_CONN_DWL_COMPLETE_MSG_TYPE",
                        BTSPD_CONN_TRACK_CONN_DWL_COMPLETE_MSG_TYPE);

        msgDWL->setMyName(this->getParentModule()->getFullName());
        msgDWL->setCompletionTime(simTime().dbl());
        msgDWL->setDuration(_tDuration.dbl());

        sendDirect(msgDWL,  p_ConnTracker, p_ConnTracker->findGate("direct_in"));
    }
}




IPvXAddress BTPeerWireSPD::getMyIPAddr()
{
    IPvXAddress ipaddress_var;
    IInterfaceTable* ift    = NULL;
    InterfaceEntry* iff = NULL;
    cModule* mod        = this;

    // traverse the hierarchy to grab the interface table
    while((ift = IPAddressResolver().findInterfaceTableOf(mod)) == NULL)
        mod = mod->getParentModule();

    // no interface table found? -- something nasty is happening here
    if(ift == NULL)
        // report the error
        error("%s:%d at %s() self-address resolution failed\n", __FILE__, __LINE__, __func__);

    // traverse the interface table and grab the appropriate IP address
    for(int i=0; i<ift->getNumInterfaces(); i++)
    {
        iff = ift->getInterface(i);

        // ignore loopbacks
        if(iff->isLoopback())
            continue;

        // if the interface has an IPv4 address then use it
        if(iff->ipv4Data() != NULL)
        {
            // update the address value
            ipaddress_var = IPvXAddress(iff->ipv4Data()->getIPAddress().str().c_str());
            break;
        }
        // try with IPv6
        else
        {
            // update the address value
            ipaddress_var = IPvXAddress(iff->ipv6Data()->getPreferredAddress().str().c_str());
            break;
        }
    }
    return ipaddress_var;
}

void BTPeerWireSPD::checkConnections()
{
    disconnectBadConnections();

    checkPassiveConnLimit();

    //now let the super class to do its functionality
    BTPeerWireBase::checkConnections();
}

void BTPeerWireSPD::checkPassiveConnLimit()
{
    //passive connection throtlling is done only if we are still downloading the file.
    //because seeders donn't need to keep reserve slots for active connection because they already have the file
    if ( getState() < COMPLETED )
    {
        if ( !b_PassiveConnectionsBlocked  && (i_PassiveConnCount > i_MaxPassiveConnCount ) )
        {
            BT_LOG_INFO( btLogSinker,"BTPeerWireSPD::checkPassiveConnLimit","["<<this->getParentModule()->getFullName()<<
                        "] Stop listening because, Passive Connection count ["<<i_PassiveConnCount<<"] exceeds max ["<<i_MaxPassiveConnCount<<"]");

            b_PassiveConnectionsBlocked = true ;

            stopListening();
        }

        else if ( b_PassiveConnectionsBlocked && (i_PassiveConnCount < (i_MaxPassiveConnCount - 3) ) )
        {
            BT_LOG_INFO( btLogSinker,"BTPeerWireSPD::checkPassiveConnLimit","["<<this->getParentModule()->getFullName()<<
                        "] Start listening because, Passive Connection count ["<<i_PassiveConnCount<<"] going lower than the limit. max ["<<i_MaxPassiveConnCount<<"]");

            b_PassiveConnectionsBlocked = false ;

            startListening();
        }
    }
}

void BTPeerWireSPD::disconnectBadConnections()
{
    if (b_DisconnectBadConnections == false)
    {
        return ;
    }

    if ((maxNumConnections()-currentNumConnections_var-pendingNumConnections() -1) <= 0)
    {

        TCPServerThreadBase* thread(NULL);

        PeerEntryVector peerVector = peerState.getVector();

        //First sort the peerVector in decreasing download rate order.
        std::sort(peerVector.rbegin(), peerVector.rend());

        int iLimit = maxNumConnections()- minNumConnections();

        BT_LOG_DEBUG(btLogSinker,"BTPeerWireSPD::disconnectBadConnections","["<<this->getParentModule()->getFullName()<<"] reached maximum peer count. disconnecting ["<<iLimit<<"] peers");

        for (int i=0; i<iLimit; i++)
        {
            PeerEntry* peer= &peerVector[i];
            thread = (TCPServerThreadBase*)peer->getPeerThread();

            BT_LOG_DEBUG(btLogSinker,"BTPeerWireSPD::disconnectBadConnections","["<<this->getParentModule()->getFullName()<<"] disconnecting ["<<peer->getPeerID()<<"]");

            thread->timerExpired(BTMsgFactory::getInstance()->getMessageObj(toString(CLOSE_CONNECTION_TIMER),CLOSE_CONNECTION_TIMER));
        }
    }
}

void BTPeerWireSPD::onLeavingSwarm()
{
    if ( b_enableConnMapDumping)
    {
        //BT_LOG_INFO(btLogSinker,"BTPeerWireSPD::notifyNewConnToConnMapper","["<<this->getParentModule()->getFullName()<<"] sending Connection map update...");

        BTSPDConnTrackNodeLeaveMsg* nodeLeaveMsg =
                new BTSPDConnTrackNodeLeaveMsg("BTSPD_CONN_TRACK_NODE_LEAVE_MSG_TYPE",
                        BTSPD_CONN_TRACK_NODE_LEAVE_MSG_TYPE);

        nodeLeaveMsg->setMyName(this->getParentModule()->getFullName());
        nodeLeaveMsg->setLeaveTime(simTime().dbl());
        sendDirect(nodeLeaveMsg,  p_ConnTracker, p_ConnTracker->findGate("direct_in"));
    }

    p_StatModule->nodeExited(this->getParentModule()->getFullName());
}

void BTPeerWireSPD::onReadyToLeaveSwarm()
{
    if ( b_enableConnMapDumping)
    {
        //BT_LOG_INFO(btLogSinker,"BTPeerWireSPD::notifyNewConnToConnMapper","["<<this->getParentModule()->getFullName()<<"] sending Connection map update...");

        BTSPDConnTrackReaedyToLeaveMsg* nodeLeaveMsg =
                new BTSPDConnTrackReaedyToLeaveMsg("BTSPD_CONN_TRACK_READY_TO_LEAVE_MSG_TYPE",
                        BTSPD_CONN_TRACK_READY_TO_LEAVE_MSG_TYPE);

        nodeLeaveMsg->setMyName(this->getParentModule()->getFullName());
        nodeLeaveMsg->setReadyToLeaveTime(simTime().dbl());
        sendDirect(nodeLeaveMsg,  p_ConnTracker, p_ConnTracker->findGate("direct_in"));
    }

    p_StatModule->nodeLeftTheSwarm(this->getParentModule()->getFullName());
}



