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

simple BTSPDConnTracker 
{
    parameters:
        string 	OutPutFile;   
        bool 	enableConnMapDumping = default(false);
        bool 	printActiveConn = default(false);		
        int		dumpingInterval = default(1000);  
        int		terminalTypeCount= default(0);
        string 	overlayTerminal0;
        string 	overlayTerminal1;
        string 	overlayTerminal2;
        string 	overlayTerminal3;  
        string 	overlayTerminal4;
    gates:
        input direct_in;    
}
