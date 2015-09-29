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

Define_Module(BTTrackerClientSPD);

BTTrackerClientSPD::BTTrackerClientSPD():
b_Downloader(true),
b_PublishMeInPeerList(true),
b_IsSeeder(false)
{


}

void BTTrackerClientSPD::initialize() {

    BTTrackerClientBase::initialize();

    d_DownloaderRelayPeerRatio = par("downloaderRelayPeerRatio");
    d_Relay_RelayPeerRatio = par("relay_RelayPeerRatio");

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
        {
            b_Downloader=pTrackerCommReq->downloader();
            b_PublishMeInPeerList = pTrackerCommReq->publishInPeerList();
			b_IsSeeder=pTrackerCommReq->seeder();
        }
        else
        {
            BT_LOG_INFO(btLogSinker,"BTTrackerClientSPD::handleMessage","["<<this->getParentModule()->getFullName()<<
                    "] received a message from PeerWireModule which is not a BTRequestTrackerCommSPD message");

            throw cRuntimeError("[%s] - BTTrackerClientSPD - received a message from PeerWireModule which is not a BTRequestTrackerCommSPD message",this->getParentModule()->getFullName());
            //default case
            b_Downloader=true;
            b_PublishMeInPeerList = true;
			b_IsSeeder=false;
        }
    }

    BTTrackerClientBase::handleMessage(msg);

}

BTTrackerMsgAnnounce * BTTrackerClientSPD::createAnnounceMsg()
{
    BTTrackerMsgAnnounceSPD * pMsg=new BTTrackerMsgAnnounceSPD();


    double dRelayPeerRatio=0.0;

    if(b_Downloader)
        dRelayPeerRatio=d_DownloaderRelayPeerRatio;

    else
        dRelayPeerRatio=d_Relay_RelayPeerRatio;


    BT_LOG_DETAIL(btLogSinker,"BTTrackerClientSPD::handleMessage","["<<this->getParentModule()->getFullName()<<
            "using relay peer ratio ["<<dRelayPeerRatio<<"] And Downloader flag ["<<b_Downloader<<"] seeder flag ["<<b_IsSeeder<<"]"<<
            "] publish in peer list flag ["<<b_PublishMeInPeerList<<"]");

    pMsg->setRelayPeerRatio(dRelayPeerRatio);
    pMsg->setPublishInPeerList(b_PublishMeInPeerList);
	pMsg->setSeeder(b_IsSeeder);

	pMsg->setIsRelay(!b_Downloader);

    return pMsg;

}
