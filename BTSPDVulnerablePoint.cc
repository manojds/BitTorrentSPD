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
}

bool BTSPDVulnerablePoint::isVulnerable()
{
    return b_Vulnerable;

}

void BTSPDVulnerablePoint::vulnerabilityFixed()
{
    b_Vulnerable= false;
}


BTSPDVulnerablePClientHndlr::BTSPDVulnerablePClientHndlr()
{}

BTSPDVulnerablePClientHndlr::~BTSPDVulnerablePClientHndlr()
{}

void BTSPDVulnerablePClientHndlr::established()
{
    BT_LOG_INFO(btLogSinker, "BTSPDVulnerablePClientHndlr::established",
            "connection with client[address=" << getSocket()->getRemoteAddress() << ", port=" << getSocket()->getRemotePort() << "] established");
}

void BTSPDVulnerablePClientHndlr::dataArrived(cMessage* mmsg, bool)
{
    if(mmsg->getKind() == BTSPD_ATTACK_MSG_TYPE)
    {
        BT_LOG_INFO(btLogSinker, "BTSPDVulnerablePClientHndlr::dataArrived", "[" << getHostModule()->getParentModule()->getFullName()
                << "] Attack Message received - vulnerability has been exploited........");


        delete mmsg;

        BTSPDVulnerablePoint * pHostMod=check_and_cast<BTSPDVulnerablePoint*>(getHostModule());

        if(pHostMod->isVulnerable())
        {

            BT_LOG_INFO(btLogSinker, "BTSPDVulnerablePClientHndlr::dataArrived", "[" << getHostModule()->getParentModule()->getFullName()
                            << "] I am vulnerable and vulnerability has been exploited........");

            BTThreatHandler* p_ThreatHndlr=
                    (BTThreatHandler*)(pHostMod->getParentModule()->getSubmodule("threatHandler"));

            p_ThreatHndlr->hasBeenAttacked();
        }
        else
        {
            BT_LOG_INFO(btLogSinker, "BTSPDVulnerablePClientHndlr::dataArrived", "[" << getHostModule()->getParentModule()->getFullName()
                                        << "] I am not vulnerable, so no problem........");
        }

    }
    else
    {
        throw cRuntimeError("BTSPDVulnerablePClientHndlr::dataArrived - unknown message received. kind [%d] name [%s]",
                mmsg->getKind(), mmsg->getName());
    }
}

void BTSPDVulnerablePClientHndlr::timerExpired(cMessage*)
{

}
