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

#include "BTTrackerClientSPD.h"
#include "BTTrackerMsgSPD_m.h"
#include "BTHostIntrnlMsgsSPD_m.h"
#include "../BitTorrent/BTLogImpl.h"

BTTrackerClientSPD::BTTrackerClientSPD():
b_Downloader(true)
{

}

BTTrackerClientSPD::~BTTrackerClientSPD() {
}

void BTTrackerClientSPD::handleMessage(cMessage* msg)
{
    if( msg->arrivedOn("btorrentIn"))
    {
        //if arrived from peer wire try to determine whether we are a downloader or not
        BTRequestTrackerCommSPD * pTrackerCommReq=dynamic_cast<BTRequestTrackerCommSPD *>(msg);

        if ( pTrackerCommReq != NULL)
            b_Downloader=pTrackerCommReq->downloader();
        else
        {
            BT_LOG_INFO(btLogSinker,"BTTrackerClientSPD::handleMessage","["<<this->getParentModule()->getFullName()<<
                    "] received a message from PeerWireModule which is not a BTRequestTrackerCommSPD message");

            throw cRuntimeError("[%s] - BTTrackerClientSPD - received a message from PeerWireModule which is not a BTRequestTrackerCommSPD message",this->getParentModule()->getFullName());
            //default case
            b_Downloader=true;
        }
    }

    BTTrackerClientBase::handleMessage(msg);

}

BTTrackerMsgAnnounce * BTTrackerClientSPD::createAnnounceMsg()
{
    BTTrackerMsgAnnounceSPD * pMsg=new BTTrackerMsgAnnounceSPD();


    if(b_Downloader)
        pMsg->setRelayPeerRatio(d_DownloaderRelayPeerRatio);
    else
        pMsg->setRelayPeerRatio(d_Relay_RelayPeerRatio);

    return pMsg;

}
