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


Register_Class(BTPeerWireClientHandlerSPDRelay);

BTPeerWireClientHandlerSPDRelay::BTPeerWireClientHandlerSPDRelay()
{
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
        BT_LOG_INFO(btLogSinker, "BTPWClientHndlrSPDR::dataArrived", "[" << getHostModule()->getParentModule()->getFullName()
                << "] Patch Platform information reponse arrived.... from ["<< getRemotePeerID()<<"]");

        msg=PacketMsg->decapsulate();
        delete PacketMsg;

        if (getState() < CONNECTED)
        {
            BT_LOG_INFO(btLogSinker, "BTPWClientHndlrSPDR::dataArrived", "[" << getHostModule()->getParentModule()->getFullName()
                    << "] the connection is being torn down. Discarding received message ...from ["<< getRemotePeerID()<<"]");
            delete msg;
            return;
        }

        patchInfoReceived(msg);

    }
    else
    {
        if(msg->getKind() == HANDSHAKE_MSG)
        {
            sendGetPatchInfoRequest();
        }
        BTPeerWireClientHandlerSPD::dataArrived( mmsg, urgent);


    }
}

void BTPeerWireClientHandlerSPDRelay::patchInfoReceived(cPacket * msg)
{
    BTSPDPatchInfoMsg * pPatchInfoMsg= check_and_cast<BTSPDPatchInfoMsg *>(msg);

    BTPeerWireSPDRelay* pPWSPD= check_and_cast<BTPeerWireSPDRelay*>(peerWireBase);
    pPWSPD->setPatchInfo(pPatchInfoMsg->platform());

    BT_LOG_INFO(btLogSinker, "BTPWClientHndlrSPDR::patchInfoReceived", "[" << getHostModule()->getParentModule()->getFullName()
                        << "] Patch platform received as ["<< pPatchInfoMsg->platform()<<"]");

    decideToBeDownloaderOrNot();

    pPWSPD->startParticipationInSwarm();

    delete msg;

}

void BTPeerWireClientHandlerSPDRelay::decideToBeDownloaderOrNot()
{
    //first retrieve my platform
    BTPeerWireSPDRelay* pPWHost= check_and_cast<BTPeerWireSPDRelay*>(peerWireBase);

    if(pPWHost->getPlatFormType() == pPWHost->getPatchInfo())
    {
        pPWHost->beADownloader();
    }

}

void BTPeerWireClientHandlerSPDRelay::sendGetPatchInfoRequest()
{
    BTPeerWireSPDRelay* pPWHost= check_and_cast<BTPeerWireSPDRelay*>(peerWireBase);
    if(pPWHost->isPatchInfoAvailable() == false)
    {
        BT_LOG_INFO(btLogSinker, "BTPWClientHndlrSPDR::sendGetPatchInfoRequest", "[" << getHostModule()->getParentModule()->getFullName()
                            << "] sending patch info request ... to ["<<getRemotePeerID()<<"]");

        cPacket * msg=new cPacket("BTSPD_GET_PATCH_PLATFORM_INFO_MSG",BTSPD_GET_PATCH_PLATFORM_INFO_MSG_TYPE);
        msg->setByteLength(1);
        sendMessage(msg);
    }
    else
    {
        BT_LOG_INFO(btLogSinker, "BTPWClientHndlrSPDR::sendGetPatchInfoRequest", "[" << getHostModule()->getParentModule()->getFullName()
                            << "] Patch information is available as ["<<pPWHost->getPatchInfo()<<"]. Avoid sending patch info request");
    }

}

//relays are supposed to upload. so act as they have completed the download
float BTPeerWireClientHandlerSPDRelay::getDownloadRate()
{
    return uploadRate;
}
