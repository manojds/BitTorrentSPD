/*
 * BTPeerWireSPDRelay.cc
 *
 *  Created on: Jan 21, 2015
 *      Author: manojd
 */

#include "BTPeerWireSPDRelay.h"
#include "../BitTorrent/BTPeerWireClientHandlerBase.h"
#include "../BitTorrent/BTLogImpl.h"
#include "BTStatisticsSPD.h"
#include "BTHostIntrnlMsgsSPD_m.h"

Define_Module(BTPeerWireSPDRelay);

BTPeerWireSPDRelay::BTPeerWireSPDRelay():
        b_isParticipatingInSwarm(false),
        b_ParticipatedInSwarm(false),
        b_Downloader(false),
        b_PatchInfoAvailable(false),
        evtRelayTrackerComm(NULL)
{

}

BTPeerWireSPDRelay::~BTPeerWireSPDRelay() {
    // TODO Auto-generated destructor stub
}

void BTPeerWireSPDRelay::initialize()
{
    BTPeerWireSPD::initialize();

    //we set patch info to nothing, bcz patch info is not same as our platform
    //patch info can be learned from other peers.
    s_PatchInfo="";
    b_PatchInfoAvailable=false;

}

void BTPeerWireSPDRelay::doStartNode()
{

    BTPeerWireSPD::doStartNode();

    Enter_Method_Silent();

    evtRelayTrackerComm = new cMessage(toString(INTERNAL_TRACKER_REALY_COM_MSG), INTERNAL_TRACKER_REALY_COM_MSG);
    scheduleAt(simTime(), evtRelayTrackerComm);


}

void BTPeerWireSPDRelay::handleMessage(cMessage *msg)
{
    if ((!msg->isSelfMessage()) && msg->arrivedOn("relayTrackerIn"))
    {
        handleMsgFromRelayTracker(msg);
        delete msg;

    }
    else
    {
        //This is not related to us. let the super handle this message.
        BTPeerWireSPD::handleMessage(msg);
    }
}

void BTPeerWireSPDRelay::handleMsgFromRelayTracker(cMessage *msg)
{
    if (getState() < EXITING)
    {
        BT_LOG_DEBUG( btLogSinker,
                        "BTPeerWireSPDRelay::handleMsgFromRelayTracker",
                        "["<< this->getParentModule()->getFullName()<<"] tracker response arrived.");

        BTTrackerMsgResponse* trackerResponse_msg =
                check_and_cast<BTTrackerMsgResponse*>(msg);

        double      relayAnnounceInterval_var=
                trackerResponse_msg->announceInterval();

        //Scheduling next contact with the tracker.
        scheduleAt(simTime() + relayAnnounceInterval_var, evtRelayTrackerComm);

    }

}

void BTPeerWireSPDRelay::handleSelfMessage(cMessage* msg)
 {
    switch (msg->getKind())
    {
    case INTERNAL_TRACKER_REALY_COM_MSG:
        BT_LOG_INFO(
                btLogSinker,
                "BTPeerWireSPDRelay::handleSelfMessage",
                "["<< this->getParentModule()->getFullName()<<"] instructing communication with the tracker...");

        switch (getState())
        {
        case NORMAL:
        case ENDGAME:
        case SEEDER:
        case COMPLETED:
        case SEEDING:
        {
            send(new cMessage(toString(EVT_CONN), EVT_CONN), "relayTrackerOut");
            break;
        }

        case EXITING:
        {
            send(new cMessage(toString(EVT_STOP), EVT_STOP), "relayTrackerOut");
            break;
        }

        default:
            error("%s:%d at %s() Invalid client state (STATE = %d). \n",
                    __FILE__, __LINE__, __func__, getState());
            break;

        }

        break;

    case INTERNAL_EXIT_SAFE_MSG:
    {
        if ( evtRelayTrackerComm != NULL)
        {
            cancelAndDelete(evtRelayTrackerComm);
            evtRelayTrackerComm = NULL;
        }

        BTPeerWireSPD::handleSelfMessage(msg);
        break;
    }

    default:
        BTPeerWireSPD::handleSelfMessage(msg);
        break;

    }
}

cMessage * BTPeerWireSPDRelay::createTrackerCommMsg()
{
    cMessage * pMsg= BTPeerWireSPD::createTrackerCommMsg();

    BTRequestTrackerCommSPD * pTrackerCommMsg=check_and_cast<BTRequestTrackerCommSPD *>(pMsg);

    pTrackerCommMsg->setDownloader(b_Downloader);
    return pTrackerCommMsg;
}

void BTPeerWireSPDRelay::scheduleTrackerCommAt(simtime_t t)
{
    if(b_isParticipatingInSwarm)
    {
        BTPeerWireSPD::scheduleTrackerCommAt(t);
    }
}

void BTPeerWireSPDRelay::notifynodeCreationToStatModule()
{
    p_StatModule->nodeCreated(this->getParentModule()->getFullName(), RELAY_PEER);
}



void BTPeerWireSPDRelay::startActiveParticipationInSwarm()
{
    if(b_isParticipatingInSwarm == false)
    {
        BT_LOG_INFO( btLogSinker, "BTPeerWireSPDRelay::startActiveParticipationInSwarm","["<<this->getParentModule()->getFullName()<<"]"
                "startActiveParticipationInSwarm - Starting to act as Relay. ");

        b_isParticipatingInSwarm    = true;
        b_ParticipatedInSwarm       = true;

        startTrackerComm();

        p_StatModule->nodeIsActiveInSwarm(this->getParentModule()->getFullName());

    }

}

void BTPeerWireSPDRelay::stopParticipationInSwarm()
{
    if(b_isParticipatingInSwarm == true)
    {
        BT_LOG_ESSEN( btLogSinker, "BTPeerWireSPDRelay::stopParticipationInSwarm","["<<this->getParentModule()->getFullName()<<"]"
                "Stopping participating in swarm");

        b_isParticipatingInSwarm = false;

        stopTrackerComm();
        pauseChokingAlgos();
        closeAllConnections();

        p_StatModule->nodeLeftTheSwarm(this->getParentModule()->getFullName());
    }

}

void BTPeerWireSPDRelay::checkRcvdConnIsViable(const PEER & peer)
{
    //currently we don't have anything to do here as a relay

}

void BTPeerWireSPDRelay::newConnectionFromPeerEstablished(PEER peer, TCPServerThreadBase* thread)
{
    BT_LOG_INFO( btLogSinker, "BTPeerWireSPDRelay::newConnectionFromPeerEstablished",
            "["<< this->getParentModule()->getFullName()<<"] ConnMngmnt - New connection arrived from peer ["<<peer.peerId<<"]");

    BTPeerWireSPD::newConnectionFromPeerEstablished(peer, thread);

    std::map<IPvXAddress, PEER>::iterator itr = initiatedPeers.find(peer.ipAddress);
    if(itr == initiatedPeers.end())
    {
        initiatedPeers[peer.ipAddress]=peer;
    }
    else
    {
        std::stringstream ss;
        ss<<"["<< this->getParentModule()->getFullName()<<"] ConnMngmnt - Connection came from the same peer  twice. PeerID ["<<
                peer.peerId<<"] IPaddress ["<<peer.ipAddress<<"]";

        BT_LOG_ERROR( btLogSinker, "BTPeerWireSPDRelay::newConnectionFromPeerEstablished", ss.str().c_str());


        throw cRuntimeError(ss.str().c_str());
    }

    //then if we have participated in the swarm previously,
    //and we have some received connections try to startParticipateIntheSwarm.
    //if we left the swarm since incoming connections reaches zero, this will trigger re-participate in the swarm.
    //the if check is necessary to avoid first time particpation, because first time participation triggered
    //when patch info is received.
    if (b_ParticipatedInSwarm)
    {
        startActiveParticipationInSwarm();
    }

}

void BTPeerWireSPDRelay::newConnectionToPeerEstablished(PEER peer, TCPServerThreadBase* thread)
{

    BT_LOG_INFO( btLogSinker, "BTPeerWireSPDRelay::newConnectionToPeerEstablished",
            "["<< this->getParentModule()->getFullName()<<"] ConnMngmnt - Connection Established with peer ["<<peer.peerId<<"]");

    BTPeerWireSPD::newConnectionToPeerEstablished(peer, thread);
}

void BTPeerWireSPDRelay::connectionLostFromPeer(PEER peer, bool isActiveConn)
{
    BT_LOG_INFO( btLogSinker, "BTPeerWireSPDRelay::connectionLostFromPeer",
            "["<< this->getParentModule()->getFullName()<<"] ConnMngmnt - Connection Lost with peer ["<<peer.ipAddress<<"]");


    //we remove this peer from initiator list if it is a initiator
    initiatedPeers.erase(peer.ipAddress);

    if(initiatedPeers.size() == 0)
    {
        stopParticipationInSwarm();
    }

    BTPeerWireSPD::connectionLostFromPeer(peer, isActiveConn);
}


void BTPeerWireSPDRelay::beADownloader()
{
    BT_LOG_INFO( btLogSinker, "BTPeerWireSPDRelay::pauseChokingAlgos","["<<this->getParentModule()->getFullName()<<"]"
            "Switching to downloader mode....");

    b_Downloader=true;

}
void BTPeerWireSPDRelay::setPatchInfo(const std::string & _sPatchInfo)
{
    s_PatchInfo= _sPatchInfo;
    b_PatchInfoAvailable=true;
}

void BTPeerWireSPDRelay::pauseChokingAlgos()
{
    //if get state is exiting we have already stopped choking algorithms.
    //so nothing to pause
    if(getState() < EXITING)
    {
        BT_LOG_INFO( btLogSinker, "BTPeerWireSPDRelay::pauseChokingAlgos","["<<this->getParentModule()->getFullName()<<"]"
                "Pausing Choking Algorithms...");

        if(evtChokeAlg->isScheduled())
            cancelEvent(evtChokeAlg);

        if(evtOptUnChoke->isScheduled())
            cancelEvent(evtOptUnChoke);
    }

}

void BTPeerWireSPDRelay::startTrackerComm()
{
    BT_LOG_INFO( btLogSinker, "BTPeerWireSPDRelay::startTrackerComm","["<<this->getParentModule()->getFullName()<<"]"
            "Starting Tracker Communication...");

    if(evtTrackerComm->isScheduled() == false)
    {
        scheduleTrackerCommAt(simTime());
    }
}

void BTPeerWireSPDRelay::stopTrackerComm()
{
    BT_LOG_INFO( btLogSinker, "BTPeerWireSPDRelay::stopTrackerComm","["<<this->getParentModule()->getFullName()<<"]"
            "Stopping Tracker Communication...");

    if(evtTrackerComm->isScheduled() == true)
    {
        cancelEvent(evtTrackerComm);
    }
}



void BTPeerWireSPDRelay::writeStats()
{
    BTStatisticsDWLMsg* msgDWL = new BTStatisticsDWLMsg("BT_STATS_RELAY_DWL",BT_STATS_RELAY_DWL);
    msgDWL->setDownloadTime(SIMTIME_DBL(downloadDuration()));
    msgDWL->setRemainingBlocks(localBitfield()->numRemainingBlocks());
    sendDirect(msgDWL,  btStatistics, btStatistics->findGate("direct_in"));


}

const char* BTPeerWireSPDRelay::toString(int type)
{
    switch (type)
    {
        case INTERNAL_TRACKER_REALY_COM_MSG :
            return "INTERNAL_TRACKER_REALY_COM_MSG";
            break;
        default:
            return BTPeerWireSPD::toString(type);
            break;
    }
    return NULL;
}

