//
// Copyright 2009 Konstantinos V. Katsaros
//                              ntinos@aueb.gr
//                              http://mm.aueb.gr/~katsaros
//

// This file is part of BitTorrent Implementation for OMNeT++.

//    BitTorrent Implementation for OMNeT++ is free software: you can redistribute
//	  it and/or modify it under the terms of the GNU General Public License as
//    published by the Free Software Foundation, either version 2 of the License,
//	  or (at your option) any later version.

//    BitTorrent Implementation for OMNeT++ is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with BitTorrent Implementation for OMNeT++.
//    If not, see <http://www.gnu.org/licenses/>.

package inet.applications.BitTorrentSPD;

import inet.applications.BitTorrent.BTPeerWireBase;
import inet.applications.tcpapp.TCPApp;

simple BTPeerWireSPDRelay extends BTPeerWireSPD like TCPApp
{
    parameters:
		@class(BTPeerWireSPDRelay); 
		
		bool	leaveNetworkRandomly 	= default (false);
		int		leaveTimeAverage		= default (100);
		int		leveTimeVariation		= default (50);
		
		
		

	gates:
	    input 	relayTrackerIn;
        output 	relayTrackerOut;
}
