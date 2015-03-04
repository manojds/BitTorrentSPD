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

#ifndef BTPEERWIRESPD_H_
#define BTPEERWIRESPD_H_
#include "../BitTorrent/BTPeerWireBase.h"

class BTThreatHandler;

class INET_API BTPeerWireSPD :public BTPeerWireBase
{
public:
    BTPeerWireSPD();
    virtual ~BTPeerWireSPD();

    const std::string & getPatchInfo(){return s_PatchInfo;}
    const std::string & getPlatFormType(){ return s_PlatFormType; }

protected:

    virtual void initialize();

    virtual void handleSelfMessage(cMessage* msg);
    virtual cMessage * createTrackerCommMsg();

    virtual void newConnectionFromPeerEstablished(PEER peer, TCPServerThreadBase* thread);
    virtual void newConnectionToPeerEstablished(PEER peer, TCPServerThreadBase* thread);

    virtual void notifyNewAddrToThreatHndlr(const PEER & peer);

    virtual void downloadCompleted();



    BTThreatHandler*    p_ThreatHndlr;
    std::string         s_PlatFormType;
    std::string         s_PatchInfo;

};

#endif /* BTPEERWIRESPD_H_ */
