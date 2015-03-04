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
#include "BTSPDPatchInfoMsgs_m.h"
#include "BTPeerWireSPD.h"

Register_Class(BTPeerWireClientHandlerSPD)

BTPeerWireClientHandlerSPD::BTPeerWireClientHandlerSPD() {



}

void BTPeerWireClientHandlerSPD::init(TCPSrvHostApp *hostmodule, TCPSocket *socket)
{
    BTPeerWireClientHandlerBase::init(hostmodule, socket);

    s_PatchPlatform= (getHostModule()->getParentModule()->par("plaformType").str());

}

BTPeerWireClientHandlerSPD::~BTPeerWireClientHandlerSPD() {

}


void BTPeerWireClientHandlerSPD::dataArrived(cMessage* mmsg, bool urgent)
{

    cPacket * PacketMsg = dynamic_cast<cPacket *>(mmsg);
    if (PacketMsg == NULL)
    {
        opp_error("MJP - Message (%s)%s is not a cPacket -- ",
                  mmsg->getClassName(), mmsg->getName());
        delete mmsg;
        return;
    }

    cPacket * msg = PacketMsg->getEncapsulatedPacket();

    if(msg->getKind() == BTSPD_GET_PATCH_PLATFORM_INFO_MSG_TYPE)
    {
        BT_LOG_INFO(btLogSinker, "BTPWClientHndlrSPD::dataArrived", "[" << getHostModule()->getParentModule()->getFullName()
                << "] Patch Platform information request arrived....");

        delete PacketMsg;


        if (getState() < CONNECTED)
        {
            BT_LOG_INFO(btLogSinker, "BTPWClientHndlrSPD::dataArrived", "[" << getHostModule()->getParentModule()->getFullName()
                    << "] the connection is being torn down. Discarding received message ...");
            return;
        }

        sendPatchInfo();

    }
    else
    {
        BTPeerWireClientHandlerBase::dataArrived( mmsg, urgent);

    }
}

void BTPeerWireClientHandlerSPD::sendPatchInfo()
{

    BT_LOG_INFO(btLogSinker, "BTPWClientHndlrSPD::sendPatchInfo", "[" << getHostModule()->getParentModule()->getFullName()
                    << "] sending Patch Platform information response. Patch platform is ["<<s_PatchPlatform<<"]");

    BTSPDPatchInfoMsg * msg=new BTSPDPatchInfoMsg("BTPSPD_PATCH_INFO_RES_MSG",BTPSPD_PATCH_INFO_RES_MSG_TYPE);
    msg->setPlatform(s_PatchPlatform.c_str());
    msg->setByteLength(s_PatchPlatform.size());
    sendMessage(msg);

}



