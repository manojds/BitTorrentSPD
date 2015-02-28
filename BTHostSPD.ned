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

import inet.applications.BitTorrent.BTHost;
import inet.applications.tcpapp.TCPApp;

module BTHostSPD extends BTHost
{
    parameters:
        string threatHandlerAppType;
        string plaformType;
        @display("bgb=337,472");
    gates:    
    
    submodules:
        //sub modlue which handles the tracker communication for the relay torrent hash
        threatHandler: <threatHandlerAppType> like TCPApp {
            parameters:
                @display("p=290,80;i=block/app");
        }
        
    connections allowunconnected:
        peerWire.threatHandlerOut --> {  } --> threatHandler.btorrentIn;
        
        threatHandler.tcpOut --> {  } --> tcp.appIn++;
        threatHandler.tcpIn <-- {  } <-- tcp.appOut++;        
               
}
