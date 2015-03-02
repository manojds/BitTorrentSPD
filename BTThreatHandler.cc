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

#include "BTThreatHandler.h"
#include "../BitTorrent/BTLogImpl.h"
#include "BTSPDCommonMsgTypes.h"
#include <IPAddressResolver.h>
#include <IInterfaceTable.h>
#include <InterfaceEntry.h>
#include "../../networklayer/ipv4/IPv4InterfaceData.h"
#include "../../networklayer/ipv6/IPv6InterfaceData.h"
#include "../tcpapp/GenericAppMsg_m.h"
#include "BTSPDSecurityStatisticsMsgs_m.h"

Define_Module(BTThreatHandler);

#define ATTACK_SCHEDULE_MSG_TYPE    501
#define ACTIVATE_ADVERSRY_MSG_TYPE  502

//int BTThreatHandler::i_CurrentMaliciousNodeCount(0);

BTThreatHandler::BTThreatHandler():
        b_Malicious(false),
        b_AttackIsOngoing(false),
        p_ScheduleAttackMsg(NULL),
        t_AttackRetryDelay(60)
{}

BTThreatHandler::~BTThreatHandler()
{
    delete p_ScheduleAttackMsg;
}

void BTThreatHandler::initialize()
{
    TCPGenericCliAppBase::initialize();

    b_Malicious= par("malicious");

    BT_LOG_INFO(btLogSinker,"BTThreatHandler::initialize","["<<this->getParentModule()->getFullName()<<
            "] Threat Handler initialized.  Malicious["<< (b_Malicious?"true":"false") <<"] ");

    const char * pModPath=par("securityStatisticsModulePath").stringValue();

    p_SecStatistics = (cSimpleModule*)simulation.getModuleByPath(pModPath);


    p_ScheduleAttackMsg= new cMessage("BTSPD_ATTACK_SCHEDULE_MSG",ATTACK_SCHEDULE_MSG_TYPE);
}

void BTThreatHandler::handleMessage(cMessage *msg)
{
    if(msg->arrivedOn("btorrentIn"))
    {
        handleMsgFromBT(msg);
    }
    else
    {
        TCPGenericCliAppBase::handleMessage(msg);

    }
}

void BTThreatHandler::handleMsgFromBT(cMessage* msg)
{
    BT_LOG_INFO (btLogSinker,"BTThreatHandler::handleMsgFromBT","["<<getParentModule()->getFullName()<<"]  Message of kind ["<<
            msg->getKind()<<"] name ["<<msg->getName() <<"] received from PeerWire module");
    //decode the message
    //if attack message go in to malicious mode

    switch(msg->getKind())
    {
    case BTSPD_ATTACK_MSG_TYPE:

        activateAdversary();
        break;

    default:
        throw cRuntimeError("BTThreatHandler::handleMsgFromBT- Unknown message arrived. kind [%d] name [%s]",
                msg->getKind(),msg->getName() );
        break;

    }

    delete msg;
}


void BTThreatHandler::handleTimer(cMessage *msg)
{

    switch(msg->getKind())
    {
    case ATTACK_SCHEDULE_MSG_TYPE:
        tryNextAttack();
        break;

    case ACTIVATE_ADVERSRY_MSG_TYPE:
        break;

    default:
        throw cRuntimeError("BTThreatHandler::handleTimer- Unknown message arrived. kind [%d] name [%s]",
                msg->getKind(),msg->getName() );
        break;

    }

    delete msg;
}

void BTThreatHandler::activateAdversary()
{
    scheduleAt(simTime(), new cMessage("ACTIVATE_ADVERSRY", ACTIVATE_ADVERSRY_MSG_TYPE))
}

void BTThreatHandler::compromised()
{
    if(b_Malicious == false )
    {
        BT_LOG_INFO (btLogSinker,"BTThreatHandler::activateAdversary","["<<getParentModule()->getFullName()<<
                "] ******* I have been compromised. Activating the Adversary");
        b_Malicious= true;


        BTSPDSecurityStatus * pMsg=new BTSPDSecurityStatus("BTSPD_INFECTED_MSG",BTSPD_INFECTED_MSG_TYPE);
        pMsg->setModuleType(getParentModule()->getComponentType()->getFullName());

        sendDirect(pMsg,  p_SecStatistics, p_SecStatistics->findGate("direct_in"));
    }
}

void BTThreatHandler::cleanAdversary()
{
    if(b_Malicious == true )
    {
        BT_LOG_INFO (btLogSinker,"BTThreatHandler::cleanAdversary","["<<getParentModule()->getFullName()<<
                "]  Adversary neutralized !");
        b_Malicious= false;

        while(!q_LearnedAddrses.empty())
            q_LearnedAddrses.pop();
    }

}

void BTThreatHandler::tryNextAttack()
{
    if(b_AttackIsOngoing == false)
    {
        if(q_LearnedAddrses.size() > 0)
        {
            b_AttackIsOngoing= true;
            //set the address on which we are attacking
            std::string sHostIP=q_LearnedAddrses.front();
            par("connectAddress")= sHostIP.c_str();

            BT_LOG_INFO(btLogSinker,"BTThreatHandler::tryNextAttack","["<<getParentModule()->getFullName()<<"]  connecting to ["<<
                    q_LearnedAddrses.front()<<"] to attack...");

            //port would be taken from the configuration


            findAndSetIPAddress();

            connect();
        }
    }
    else
    {
        scheduleNextAttackAt ( simTime()+ t_AttackRetryDelay);
    }

}

void BTThreatHandler::scheduleNextAttackAt(simtime_t t)
{
    if( p_ScheduleAttackMsg->isScheduled() == false )
    {
        scheduleAt(t, p_ScheduleAttackMsg);
    }
}

void BTThreatHandler::socketEstablished(int connId, void *ptr)
{
    TCPGenericCliAppBase::socketEstablished(connId, ptr);

    sendAttackMsg();

    q_LearnedAddrses.pop();
    //and then close the socket, bcz we need it no more
    close();

    b_AttackIsOngoing=false;
    //and attempt on next address
    scheduleNextAttackAt(simTime());
}


void BTThreatHandler::sendAttackMsg()
{
    BT_LOG_INFO(btLogSinker,"BTThreatHandler::sendAttackMsg","["<<getParentModule()->getFullName()<<"]  attacking on ["<<
            q_LearnedAddrses.front()<<"] ");


    cPacket *msg = new cPacket("BTSPD_ATTACK_MSG", BTSPD_ATTACK_MSG_TYPE);
    GenericAppMsg* wrapper = new GenericAppMsg(msg->getName(), TCP_I_DATA);
    wrapper->encapsulate(msg);

    wrapper->setByteLength(1);

    socket.send(wrapper);
}



void BTThreatHandler::socketFailure(int, void*, int)
{
    BT_LOG_WARN(btLogSinker,"BTThreatHandler::socketFailure","["<<getParentModule()->getFullName()<<"]  socket failed ! ");

    scheduleNextAttackAt ( simTime()+ t_AttackRetryDelay);
}



void BTThreatHandler::newAddrFound(const std::string & _sIP, const std::string & _sPort)
{
    BT_LOG_INFO(btLogSinker,"BTThreatHandler::newAddrFound","["<<getParentModule()->getFullName()<<"]  New address found ["<<
            _sIP<<":"<<_sPort<< "]");

    //we act on new addresses only if we are malicious
    if(b_Malicious)
    {
        q_LearnedAddrses.push(_sIP);

        scheduleNextAttackAt(simTime());
    }
}



bool BTThreatHandler::isMalicious()
{
    return b_Malicious;
}

void BTThreatHandler::findAndSetIPAddress()
{
    IInterfaceTable* ift    = NULL;
    InterfaceEntry* iff = NULL;
    cModule* mod        = this;
    IPvXAddress         ipaddress_var;

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
            // update the address parameter - just in case other objects use it (e.g., TCPSocket...)
            par("address").setStringValue(ipaddress_var.str().c_str());
            break;
        }
        // try with IPv6
        else
        {
            // update the address value
            ipaddress_var = IPvXAddress(iff->ipv6Data()->getPreferredAddress().str().c_str());
            // update the address parameter - just in case other objects use it (e.g., TCPSocket...)
            par("address").setStringValue(ipaddress_var.str().c_str());
            break;
        }
    }
}
