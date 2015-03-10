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
cplusplus {{

#include "../BitTorrent/BTTrackerMsg_m.h"

}};

packet BTTrackerMsgAnnounce;

packet BTTrackerMsgAnnounceSPD extends BTTrackerMsgAnnounce
{
    @omitGetVerb(true);
    double 	relayPeerRatio;
    bool	seeder;	//falg which indicate the client is seeder or not . it is used for hide leacher from others
    				//the EVT_COMP event cannot be used since it is not sent to the tracker if the client is a seeder from the begining.
}
