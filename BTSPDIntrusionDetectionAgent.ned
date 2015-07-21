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

simple BTSPDIntrusionDetectionAgent like TCPApp
{
    parameters:
        
        volatile string address= default("");				// local address 

        volatile int port= default(-1);						//local port        

        volatile string connectAddress= default("not_specified");		// remote address - tracker's address

        volatile int connectPort= default(-1);				// remote port number
        
    gates:
        input tcpIn;        
        output tcpOut;            
}
