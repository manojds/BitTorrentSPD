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

#ifndef BTTRACKERCLIENTSPD_H_
#define BTTRACKERCLIENTSPD_H_

#include "../BitTorrent/BTTrackerClientBase.h"

class INET_API BTTrackerClientSPD:public BTTrackerClientBase {
public:
    BTTrackerClientSPD();
    virtual ~BTTrackerClientSPD();

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage*);

    virtual BTTrackerMsgAnnounce * createAnnounceMsg();

    bool    b_Downloader;   //flag to indicate that this client is a downloader or a relay
    bool    b_IsSeeder;     //flag to indicate whether this client is a seeder
    double  d_DownloaderRelayPeerRatio;
    double  d_Relay_RelayPeerRatio;
};

#endif /* BTTRACKERCLIENTSPD_H_ */
