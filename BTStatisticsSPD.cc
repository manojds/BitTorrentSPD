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

#include "BTStatisticsSPD.h"
#include "../BitTorrent/BTLogImpl.h"



Define_Module(BTStatisticsSPD);

BTStatisticsSPD::BTStatisticsSPD() {
    // TODO Auto-generated constructor stub

}

BTStatisticsSPD::~BTStatisticsSPD() {
    delete dwSuccess_Relay;
    delete numBlockFail_Relay;

}

void BTStatisticsSPD::initialize()
{
    BTStatistics::initialize();

    BT_LOG_INFO(btLogSinker, "BTStatisticsSPD::initialize", "Initializing ....");


    dwSuccess_Relay = new  cStdDev("BitTorrent Relay:Download Duration");
    dwSuccess_Relay_vec.setName("BitTorrent Relay:Download Duration");

    numBlockFail_Relay = new  cStdDev("BitTorrent Relay:Failed Downloads:Number of Completed Blocks");
    numBlockFail_Relay_vec.setName("BitTorrent Relay:Failed Downloads:Number of Completed Blocks");

}

void BTStatisticsSPD::handleMessage(cMessage* msg)
{
    switch (msg->getKind())
    {
        case BT_STATS_RELAY_DWL:
        {
            BT_LOG_DEBUG(btLogSinker,"BTStatisticsSPD::handleMessage","BT_STATS_RELAY_DWL msg received !");

            BTStatisticsDWLMsg* dwMsg = dynamic_cast<BTStatisticsDWLMsg*>(msg);
            double dwTime = dwMsg->downloadTime();
            double rmBlocks = dwMsg->remainingBlocks();
            if (rmBlocks == 0 )
            {
                dwSuccess_Relay->collect(dwTime);
                dwSuccess_Relay_vec.record(dwTime);

                BT_LOG_INFO(btLogSinker, "BTStatisticsSPD::handleMessage",
                        "Download success count is now ["<<dwSuccess->getCount()<<
                        "] just completed node ["<<msg->getSenderModule()->getParentModule()->getFullName()<<"] Current average ["
                        <<dwSuccess->getMean()<<"] just completed value ["<<dwTime <<"]");
            }
            else
            {
                numBlockFail_Relay->collect(rmBlocks);
                numBlockFail_Relay_vec.record(rmBlocks);
            }
            delete msg;
            break;
        }

        default:
        {
            BTStatistics::handleMessage(msg);
            break;
        }
    }

}

void BTStatisticsSPD::finish()
{
    BT_LOG_INFO(btLogSinker,"BTStatisticsSPD::doFinish","Finishing ...");

    dwSuccess_Relay->record();
    numBlockFail_Relay->record();
}
