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

#include "BTPeerWireClientHandlerSPDRelay.h"
#include "BTSPDCommonMsgTypes.h"
#include "../BTLogImpl.h"
#include "BTSPDPatchInfoMsgs_m.h"
#include "BTPeerWireSPDRelay.h"


Register_Class(BTPeerWireClientHandlerSPD);

BTPeerWireClientHandlerSPDRelay::BTPeerWireClientHandlerSPDRelay()
{
    s_MyPlatformInfo= (getHostModule()->getParentModule()->par("plaformType").str());
    //super class may have set the my platform type as patch platform, but
    //since I am acting as a relay that is not true.
    //So my platform type is not the patch platform type.
    //I will retrieve the patch platform type from other peers and update is accordingly.
    s_PatchPlatform="Unknown";

}

BTPeerWireClientHandlerSPDRelay::~BTPeerWireClientHandlerSPDRelay() {

}

void BTPeerWireClientHandlerSPDRelay::dataArrived(cMessage* mmsg, bool urgent)
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

    if(msg->getKind() == BTPSPD_PATCH_INFO_RES_MSG_TYPE)
    {
        BT_LOG_INFO(btLogSinker, "BTPWClientHndlrSPD::dataArrived", "[" << getHostModule()->getParentModule()->getFullName()
                << "] Patch Platform information reponse arrived....");

        msg=PacketMsg->decapsulate();
        delete PacketMsg;

        if (getState() < CONNECTED)
        {
            BT_LOG_INFO(btLogSinker, "BTPWClientHndlrSPD::dataArrived", "[" << getHostModule()->getParentModule()->getFullName()
                    << "] the connection is being torn down. Discarding received message ...");
            delete msg;
            return;
        }

        patchInfoReceived(msg);

    }
    else
    {
        BTPeerWireClientHandlerSPD::dataArrived( mmsg, urgent);

    }
}

void BTPeerWireClientHandlerSPDRelay::patchInfoReceived(cPacket * msg)
{
    BTSPDPatchInfoMsg * pPatchInfoMsg= check_and_cast<BTSPDPatchInfoMsg *>(msg);
    s_PatchPlatform=pPatchInfoMsg->platform();
    BT_LOG_INFO(btLogSinker, "BTPWClientHndlrSPD::dataArrived", "[" << getHostModule()->getParentModule()->getFullName()
                        << "] Patch platform received as ["<< s_PatchPlatform<<"]");

    decideToBeDownloaderOrNot();

}

void BTPeerWireClientHandlerSPDRelay::decideToBeDownloaderOrNot()
{
    if(s_PatchPlatform == s_MyPlatformInfo)
    {
        BTPeerWireSPDRelay * pPWHost= check_and_cast<BTPeerWireSPDRelay *>(getHostModule()->getParentModule());
        pPWHost->beADownloader();
    }

}

