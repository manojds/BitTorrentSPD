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

#include "BTSPDVulnerablePoint.h"
#include "../BTLogImpl.h"
#include "BTSPDCommonMsgTypes.h"
#include "BTThreatHandler.h"
#include "BTSPDIntrusionDetectionAgent.h"
#include "BTSPDSecurityStatisticsMsgs_m.h"

Register_Class(BTSPDVulnerablePClientHndlr);
Define_Module(BTSPDVulnerablePoint);

BTSPDVulnerablePoint::BTSPDVulnerablePoint()
{}


BTSPDVulnerablePoint::~BTSPDVulnerablePoint()
{}

void BTSPDVulnerablePoint::initialize()
{
    TCPSrvHostApp::initialize();
    b_Vulnerable= par("vulnerable");
    b_DetectAttacks = par("detectAttacks");


    const char * pModPath=par("securityStatisticsModulePath").stringValue();

    p_SecStatistics = (cSimpleModule*)simulation.getModuleByPath(pModPath);
}

bool BTSPDVulnerablePoint::isVulnerable()
{
    return b_Vulnerable;

}

void BTSPDVulnerablePoint::vulnerabilityFixed()
{
    if(b_Vulnerable)
    {
        Enter_Method_Silent();

        BT_LOG_INFO(btLogSinker, "VulnrblPnt::vulnerabilityFixed", "[" << getParentModule()->getFullName()
                    << "] Fixing the vulnerability...");
        b_Vulnerable= false;

        BTSPDSecurityStatus * pMsg=new BTSPDSecurityStatus("BTSPD_VULNERABILITY_FIXED_MSG",BTSPD_VULNERABILITY_FIXED_MSG_TYPE);
        pMsg->setModuleType(getParentModule()->getComponentType()->getFullName());

        sendDirect(pMsg,  p_SecStatistics, p_SecStatistics->findGate("direct_in"));
    }
}

bool BTSPDVulnerablePoint::tryToExploit(BTSPDAttackMessage* msg)
{
//    BT_LOG_INFO(btLogSinker, "BTSPDVulnerablePoint::tryToExploit", "[" << getParentModule()->getFullName()
//            << "]  trying to exploit vulnerability...");

    bool bRet(false);
    if(isVulnerable())
    {
        bRet= exploit(msg);

    }
    else
    {
        BT_LOG_INFO(btLogSinker, "BTSPDVulnerablePoint::tryToExploit", "[" << getParentModule()->getFullName()
                                    << "] I am not vulnerable, so no problem........");

        attackDetected(msg);
    }

    return bRet;
}

bool BTSPDVulnerablePoint::exploit(BTSPDAttackMessage* msg)
{
//    BT_LOG_INFO(btLogSinker, "BTSPDVulnerablePoint::exploit", "[" << getParentModule()->getFullName()
//                    << "] I have been exploited........");


    bool bRet(false);

    BTThreatHandler* p_ThreatHndlr=
            (BTThreatHandler*)(getParentModule()->getSubmodule("threatHandler"));

    if (p_ThreatHndlr->activateAdversary())
    {
//        //error checking
//        if (strcmp(msg->victim(), getParentModule()->getFullName()) != 0 )
//        {
//            throw cRuntimeError("Attack message received which is not intended for me. "
//                    "My Name [%s], Attacker [%s] Intended Victim [%s]", getParentModule()->getFullName(),
//                    msg->attacker(), msg->victim());
//        }

        bRet = true;
        BT_LOG_INFO (btLogSinker,"BTSPDVulnerablePoint::exploit","["<<getParentModule()->getFullName()<<
                "] ******* I have been exploited. Attacker ["<<msg->attacker()<<"] attack Type ["<<msg->attackType()
                <<"] intended victim ["<<msg->victim()<<"]");
    }

    return bRet;
}

void BTSPDVulnerablePoint::attackDetected(BTSPDAttackMessage* msg)
{
    BTSPDIntrusionDetectionAgent* pAgent =
            (BTSPDIntrusionDetectionAgent*)(getParentModule()->getSubmodule("intrutionDetectionAgent"));

    pAgent->attackDetected(msg->attackerAddr());
}


BTSPDVulnerablePClientHndlr::BTSPDVulnerablePClientHndlr()
{}

BTSPDVulnerablePClientHndlr::~BTSPDVulnerablePClientHndlr()
{}

void BTSPDVulnerablePClientHndlr::established()
{
    BT_LOG_INFO(btLogSinker, "VulnrblClientHndlr::established",
            "[" << getHostModule()->getParentModule()->getFullName()
                << "] connection with client[address=" << getSocket()->getRemoteAddress() << 
                ", port=" << getSocket()->getRemotePort() << "] established");
}

void BTSPDVulnerablePClientHndlr::dataArrived(cMessage* mmsg, bool)
{
    cPacket * PacketMsg = dynamic_cast<cPacket *>(mmsg);
    if (PacketMsg == NULL)
    {
        opp_error("MJP - Message (%s)%s is not a cPacket -- ",
                  mmsg->getClassName(), mmsg->getName());
        delete mmsg;
        return;
    }

    cPacket * msg = PacketMsg->decapsulate();
    delete mmsg;
        
    if(msg->getKind() == BTSPD_ATTACK_MSG_TYPE)
    {
        BTSPDAttackMessage* attackMsg = check_and_cast<BTSPDAttackMessage*>(msg);


        BT_LOG_INFO(btLogSinker, "VulnrblClientHndlr::dataArrived", "[" << getHostModule()->getParentModule()->getFullName()
                << "] Attack Message received - from ["<<  getSocket()->getRemoteAddress() <<"]");


        tryToExploit(attackMsg);

        delete attackMsg;


    }
    else
    {
        throw cRuntimeError("VulnrblClientHndlr::dataArrived - unknown message received. kind [%d] name [%s]",
                msg->getKind(), msg->getName());
    }
}

void BTSPDVulnerablePClientHndlr::tryToExploit(BTSPDAttackMessage* msg)
{
    BTSPDVulnerablePoint * pHostMod=check_and_cast<BTSPDVulnerablePoint*>(getHostModule());
    pHostMod->tryToExploit(msg);
}


void BTSPDVulnerablePClientHndlr::timerExpired(cMessage*)
{

}

void BTSPDVulnerablePClientHndlr::peerClosed()
{
    BT_LOG_INFO(btLogSinker, "VulnrblClientHndlr::peerClosed", "[" << getHostModule()->getParentModule()->getFullName()
                                        << "] peer closed....");
}
