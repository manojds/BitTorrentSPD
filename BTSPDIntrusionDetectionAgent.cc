
#include "BTSPDIntrusionDetectionAgent.h"
#include "../BitTorrent/BTLogImpl.h"
#include "BTSPD_Utils.h"
#include "BTSPDPeerBlackListReqMsg_m.h"
#include "../tcpapp/GenericAppMsg_m.h"


Define_Module(BTSPDIntrusionDetectionAgent);


#define NOTIFY_TRACKER_MSG_TYPE     200

BTSPDIntrusionDetectionAgent::BTSPDIntrusionDetectionAgent():
        p_NOtifyTrackerMsg(NULL),
        b_ConenctingToTracker(false)
{

}

BTSPDIntrusionDetectionAgent::~BTSPDIntrusionDetectionAgent()
{

}

void BTSPDIntrusionDetectionAgent::initialize()
{
    TCPGenericCliAppBase::initialize();

    p_NOtifyTrackerMsg = new cMessage("NOTIFY_TRACKER_MSG_TYPE", NOTIFY_TRACKER_MSG_TYPE);
}

void BTSPDIntrusionDetectionAgent::handleMessage(cMessage *msg)
{
    if ( msg->getKind() == NOTIFY_TRACKER_MSG_TYPE)
    {
        connectToTracker();
    }
    else
    {
        TCPGenericCliAppBase::handleMessage(msg);
    }
}

void BTSPDIntrusionDetectionAgent::attackDetected(const std::string _sSourceIP)
{
    BT_LOG_DEBUG(btLogSinker,"BTSPDIntrusionDetectionAgent::attackDetected","["<<
            getParentModule()->getFullName()<<"] attack detected. source ["<<_sSourceIP<<"]");

    set_Attackers.insert(_sSourceIP);

    scheduleConnectWithTracker();
}

void BTSPDIntrusionDetectionAgent::scheduleConnectWithTracker()
{

    if ( ! p_NOtifyTrackerMsg->isScheduled() )
        scheduleAt(simTime(), p_NOtifyTrackerMsg);
}

void BTSPDIntrusionDetectionAgent::connectToTracker()
{
    if (!b_ConenctingToTracker)
    {
        b_ConenctingToTracker = true;

        BT_LOG_INFO(btLogSinker,"BTSPDIntrusionDetectionAgent::connectToTracker","["<<
                getParentModule()->getFullName()<<"] connecting to tracker. address ["<<
                par("connectAddress").stdstringValue()<<"] port ["<<(int)par("connectPort")<<"]");

        BTSPD_Utils::findAndSetIPAddress(this);
        connect();
    }

}

void BTSPDIntrusionDetectionAgent::socketEstablished(int connId, void *ptr)
{
    TCPGenericCliAppBase::socketEstablished(connId, ptr);
    sendAttackerInfoToTracker();
}

void BTSPDIntrusionDetectionAgent::sendAttackerInfoToTracker()
{
    BT_LOG_INFO(btLogSinker,"BTSPDIntrusionDetectionAgent::sendAttackerInfoToTracker","["<<
            getParentModule()->getFullName()<<"] sendAttackerInfoToTracker - sending attacker list to tracker. list size is ["<<set_Attackers.size()<<"]");

    BTSPDPeerBlackListReqMsg* pMsg = new BTSPDPeerBlackListReqMsg();

    pMsg->setAttackersArraySize(set_Attackers.size());

    set<string>::iterator itr = set_Attackers.begin();
    unsigned int i = 0;

    for ( ; itr != set_Attackers.begin(); i++, itr++)
    {
        pMsg->setAttackers(i , itr->c_str());
    }

    socket.send(pMsg);

    close();

    b_ConenctingToTracker = false;

    set_Attackers.clear();

}


void BTSPDIntrusionDetectionAgent::socketFailure(int, void*, int)
{
    BT_LOG_WARN(btLogSinker,"BTSPDIntrusionDetectionAgent::socketFailure","["<<getParentModule()->getFullName()<<"] failed to connect ");

    scheduleConnectWithTracker();

}
