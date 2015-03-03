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

#ifndef BTPEERWIRECLIENTHANDLERSPD_H_
#define BTPEERWIRECLIENTHANDLERSPD_H_

#include "../BitTorrent/BTPeerWireClientHandlerBase.h"

class INET_API BTPeerWireClientHandlerSPD:public BTPeerWireClientHandlerBase
{
public:
    BTPeerWireClientHandlerSPD();
    virtual ~BTPeerWireClientHandlerSPD();


    //Redefined methods from BTPeerWireClientHandlerBase
    virtual void dataArrived(cMessage*, bool);

protected:
    virtual void sendPatchInfo();
};

#endif /* BTPEERWIRECLIENTHANDLERSPD_H_ */
