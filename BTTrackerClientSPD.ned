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

package inet.applications.BitTorrentSPD;
import inet.applications.tcpapp.TCPApp;
import inet.applications.BitTorrent.BTTrackerClientBase;

simple BTTrackerClientSPD extends BTTrackerClientBase
{
    parameters:
        @class(BTTrackerClientSPD);
        
        double downloaderRelayPeerRatio  = default(1.0);
        double relay_RelayPeerRatio= default(0.0);

}