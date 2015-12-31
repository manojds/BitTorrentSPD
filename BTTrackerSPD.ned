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

import inet.applications.BitTorrent.BTTrackerBase;
import inet.applications.tcpapp.TCPApp;
import inet.applications.udpapp.UDPApp;

simple BTTrackerSPD extends BTTrackerBase like TCPApp , UDPApp
{
    parameters:
        @class(BTTrackerSPD);
        double 	relayPeerPropotionInReply= default(0.5);
        bool	useRelayPropotioninRequest= default(false);
        //how to fill peers.
        // 0 - normal method, 1- fill only seeders, 2- hide downloders
        int		fillMethod= default (0);
        string 	realyInfoHash;		// the SHA-1 (20 bytes) hash value of realy torrent
        bool	filterBlackListedPeers 			= default (false);
        int		blackListThreshold 				= default (5);
        
        bool 	excludeRelaysFromTruePeerList 	= default(false);
        bool 	poolRelayPeers 					= default(false);
        //if obscureSeeders enabled tracker will never decrease the relay peer percentage in peer list than the relayPeerPropotionInReply
        bool	obscureSeeders					= default(false);	
        double	relayPoolFraction				= default(1);
        
}