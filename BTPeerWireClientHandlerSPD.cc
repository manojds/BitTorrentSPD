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

#include "BTPeerWireClientHandlerSPD.h"
#include "BTLogImpl.h"
#include "BTSPDCommonMsgTypes.h"

Register_Class(BTPeerWireClientHandlerSPD)

BTPeerWireClientHandlerSPD::BTPeerWireClientHandlerSPD() {

}

BTPeerWireClientHandlerSPD::~BTPeerWireClientHandlerSPD() {

}


void BTPeerWireClientHandlerSPD::dataArrived(cMessage* mmsg, bool urgent)
{
    if(mmsg->getKind() == BTSPD_ATTACK_MSG_TYPE)
    {
        BT_LOG_INFO(btLogSinker, "BTPWClientHndlrSPD::dataArrived", "[" << getHostModule()->getParentModule()->getFullName()
                << "] Attack Message received........");

        if (getState() < CONNECTED)
        {
            BT_LOG_INFO(btLogSinker, "BTPWClientHndlrSPD::dataArrived", "[" << getHostModule()->getParentModule()->getFullName()
                    << "] the connection is being torn down. Discarding received message ...");
            delete mmsg;
            return;
        }

        delete mmsg;

        //Now send a attack message to the Threat handler module
        //first find the corresponding gate
        cGate* pOutGate= getHostModule()->gate("threatHandlerOut");
        if(pOutGate->isConnectedOutside())
        {
            //sends the message only if gate is conencted, i.e. threat handler is present

            getHostModule()->send(new cMessage("BTSPD_ATTACK_MSG",BTSPD_ATTACK_MSG_TYPE), pOutGate);
        }
        else
        {
            BT_LOG_INFO(btLogSinker, "BTPWClientHndlrSPD::dataArrived", "[" << getHostModule()->getParentModule()->getFullName()
                            << "] Threat Hnalder module is not connected. avoid forwarding the attack message");

        }

    }
    else
    {
        BTPeerWireClientHandlerBase::dataArrived( mmsg, urgent);

    }


}

