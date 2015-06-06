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

#ifndef BTTRACKERSTRUCTBASESPD_H_
#define BTTRACKERSTRUCTBASESPD_H_

#include "../BTTrackerBase.h"

class BTTrackerStructBaseSPD : public BTTrackerStructBase
{
public:
    BTTrackerStructBaseSPD(const IPvXAddress& , const string& , size_t, const string& , simtime_t, bool);
    virtual ~BTTrackerStructBaseSPD();
    bool isPublishInPeerList() const;
    void setPublishInPeerList(bool publishInPeerList);

protected:
    bool b_PublishInPeerList;
};

#endif /* BTTRACKERSTRUCTBASESPD_H_ */
