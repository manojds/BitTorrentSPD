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

#ifndef __INET_BTTHREATHANDLER_H_
#define __INET_BTTHREATHANDLER_H_

#include <omnetpp.h>
#include "../tcpapp/TCPGenericCliAppBase.h"
#include <queue>


class INET_API BTThreatHandler : public TCPGenericCliAppBase
{
public:
    BTThreatHandler();
    virtual ~BTThreatHandler();
  protected:

    virtual void handleMsgFromBT(cMessage*);

    /* inherited methods from TCPGenericCliAppBase */
    virtual void initialize();
    virtual void handleMessage(cMessage*);
    virtual void socketEstablished(int, void*);
    virtual void socketDataArrived(int, void*, cPacket*, bool);
    virtual void socketPeerClosed(int, void*);
    virtual void socketFailure(int, void*, int);
    // end of the overridden methods

    bool isMalicious();

  private:
    bool b_Malicious;
};

#endif
