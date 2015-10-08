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


import inet.applications.BitTorrent.BTPeerWireBase;
import inet.applications.tcpapp.TCPApp;

simple BTPeerWireSPD extends BTPeerWireBase like TCPApp
{
    parameters:
		@class(BTPeerWireSPD);
		 
        bool enableConnMapDumping = default(false);	
        
        bool publishtoTrackerWhenDownloadComplete = default(false);
        
        //whether this peer information will be published by the tracker in the peer list
        bool publishMeByTracker = default(true);	
        
        //whether to disconnect connections with peers which so not provide much
        //download rate when maximum connection count reached.
        bool disconnectBadConnections = default(false);	
        
        //parameter which indicates whether not to actively participate and initiate connection 
        //once download is completed.
        bool doNotActivelyParticipateOnDownloadCompletion = default(false);
        
        //maximum allowed passive Connection count as a fraction of maximum allowed all connection count
        double	maxPassiveConnCountFraction = default(0.9);
        // 0 - normal method, 1- fill only seeders, 2- hide downloders
        int		fillMethod= default (0);

        string connTrackerModulePath = default("");		
		
	gates:
	    output 	threatHandlerOut;	

}
