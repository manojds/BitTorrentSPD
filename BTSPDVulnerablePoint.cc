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

bool BTSPDVulnerablePoint::tryToExploit()
{
    BT_LOG_INFO(btLogSinker, "BTSPDVulnerablePoint::tryToExploit", "[" << getParentModule()->getFullName()
            << "]  trying to exploit vulnerability...");

    bool bRet(false);
    if(isVulnerable())
    {
        exploit();
        bRet=true;
    }
    else
    {
        BT_LOG_INFO(btLogSinker, "BTSPDVulnerablePoint::tryToExploit", "[" << getParentModule()->getFullName()
                                    << "] I am not vulnerable, so no problem........");
    }

    return bRet;
}

bool BTSPDVulnerablePoint::exploit()
{
    BT_LOG_INFO(btLogSinker, "BTSPDVulnerablePoint::exploit", "[" << getParentModule()->getFullName()
                    << "] I have been exploited........");


    BTThreatHandler* p_ThreatHndlr=
            (BTThreatHandler*)(getParentModule()->getSubmodule("threatHandler"));

    return p_ThreatHndlr->activateAdversary();
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
        delete msg;

        BT_LOG_INFO(btLogSinker, "VulnrblClientHndlr::dataArrived", "[" << getHostModule()->getParentModule()->getFullName()
                << "] Attack Message received - trying to exploit vulnerability...");

        tryToExploit();


    }
    else
    {
        throw cRuntimeError("VulnrblClientHndlr::dataArrived - unknown message received. kind [%d] name [%s]",
                msg->getKind(), msg->getName());
    }
}

void BTSPDVulnerablePClientHndlr::tryToExploit()
{
    BTSPDVulnerablePoint * pHostMod=check_and_cast<BTSPDVulnerablePoint*>(getHostModule());
    pHostMod->tryToExploit();
}


void BTSPDVulnerablePClientHndlr::timerExpired(cMessage*)
{

}

void BTSPDVulnerablePClientHndlr::peerClosed()
{
    BT_LOG_INFO(btLogSinker, "VulnrblClientHndlr::peerClosed", "[" << getHostModule()->getParentModule()->getFullName()
                                        << "] peer closed....");
}
