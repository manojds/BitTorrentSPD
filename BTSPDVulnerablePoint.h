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

#ifndef __INET_BTSPDVULNERABLEPOINT_H_
#define __INET_BTSPDVULNERABLEPOINT_H_

#include <omnetpp.h>
#include "../tcpapp/TCPSrvHostApp.h"

class INET_API BTSPDVulnerablePoint  : public TCPSrvHostApp
{
public:
    BTSPDVulnerablePoint();
    virtual ~BTSPDVulnerablePoint();

    bool isVulnerable();

    void vulnerabilityFixed();

    virtual bool tryToExploit();

    virtual bool exploit();

  protected:
    virtual void initialize();



    bool                b_Vulnerable;
    cSimpleModule*      p_SecStatistics;
};


class INET_API BTSPDVulnerablePClientHndlr : public TCPServerThreadBase
{
public:
    BTSPDVulnerablePClientHndlr();
    virtual ~BTSPDVulnerablePClientHndlr();

    virtual void tryToExploit();

protected:
    /* Redefined methods from TCPServerThreadBase */
    virtual void established();
    virtual void dataArrived(cMessage*, bool);
    virtual void timerExpired(cMessage*);
    virtual void peerClosed();
    //end of the redefined methods




};

#endif
