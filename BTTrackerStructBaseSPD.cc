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

#include "BTTrackerStructBaseSPD.h"

BTTrackerStructBaseSPD::BTTrackerStructBaseSPD(const IPvXAddress& ipAddress, const string& peerId, size_t peerPort,
        const string& key, simtime_t lastAnnounce, bool isSeed):
BTTrackerStructBase(ipAddress, peerId, peerPort, key, lastAnnounce, isSeed),
b_PublishInPeerList(true)
{

}

BTTrackerStructBaseSPD::~BTTrackerStructBaseSPD()
{

}

bool BTTrackerStructBaseSPD::isPublishInPeerList() const
{
    return b_PublishInPeerList;
}

void BTTrackerStructBaseSPD::setPublishInPeerList(bool publishInPeerList)
{
    b_PublishInPeerList = publishInPeerList;
}

