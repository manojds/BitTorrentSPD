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

#include "BTPeerWireSPD.h"
#include "../BitTorrent/BTLogImpl.h"
#include "../BTTrackerClientBase.h"
#include "BTHostIntrnlMsgsSPD_m.h"

Define_Module(BTPeerWireSPD);

int BTPeerWireSPD::i_CurrentMaliciousNodeCount(0);

BTPeerWireSPD::BTPeerWireSPD() {

}

BTPeerWireSPD::~BTPeerWireSPD() {
}

void BTPeerWireSPD::initialize()
{
    BTPeerWireBase::initialize();

    int iMaxMaliciousNodes= par("maliciousNodeCount");

    if(i_CurrentMaliciousNodeCount < iMaxMaliciousNodes)
        b_Malicious=true;

    BT_LOG_INFO(btLogSinker,"BTPeerWireSPD::initialize","["<<this->getParentModule()->getFullName()<<"] ***** node initialized. Malicious["<<
            b_Malicious<<" Current malicious node count ["<<i_CurrentMaliciousNodeCount<<"] Max malicious node count ["<<iMaxMaliciousNodes<<"]");
}

void BTPeerWireSPD::handleSelfMessage(cMessage* msg)
{
    switch (msg->getKind())
    {
        case INTERNAL_TRACKER_COM_MSG:
        {
            BT_LOG_INFO(btLogSinker,"BTPeerWireSPD::handleSelfMessage","["<<this->getParentModule()->getFullName()<<"] instructing communication with the tracker...");

            cMessage * pMsg= createTrackerCommMsg();

            send( pMsg,"btorrentOut");

            break;
        }
        default:
            BTPeerWireBase::handleSelfMessage(msg);
            break;

    }
}

cMessage * BTPeerWireSPD::createTrackerCommMsg()
{
    cMessage * pMsg(NULL);

    switch (getState())
    {
        case NORMAL:
        case ENDGAME:
        case SEEDER:
        {
            pMsg= new BTRequestTrackerCommSPD(toString(EVT_CONN),EVT_CONN);

            break;
        }
        case COMPLETED:
        case SEEDING:
        {
            pMsg= new BTRequestTrackerCommSPD(toString(EVT_COMP),EVT_COMP);
            break;
        }
        case EXITING:
        {
            pMsg= new BTRequestTrackerCommSPD(toString(EVT_STOP),EVT_STOP);
            break;
        }
        default:
            error("%s:%d at %s() Invalid client state (STATE = %d). \n", __FILE__, __LINE__, __func__,getState());

    }

    return pMsg;

}


