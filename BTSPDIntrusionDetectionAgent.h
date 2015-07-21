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

#ifndef __INET_BTSPDINTRUSIONDETECTIONAGENT_H_
#define __INET_BTSPDINTRUSIONDETECTIONAGENT_H_

#include <omnetpp.h>
#include "../tcpapp/TCPGenericCliAppBase.h"

#include <set>
#include <string>

using std::string;
using std::set;

class BTSPDIntrusionDetectionAgent : public TCPGenericCliAppBase
{
public:
    BTSPDIntrusionDetectionAgent();
    virtual ~BTSPDIntrusionDetectionAgent();


    virtual void attackDetected(const std::string _sSourceIP);


  protected:

    virtual void scheduleConnectWithTracker();
    virtual void connectToTracker();
    virtual void sendAttackerInfoToTracker();

    /* inherited methods from TCPGenericCliAppBase */
    virtual void initialize();
    virtual void handleMessage(cMessage*);
    virtual void handleTimer(cMessage *msg){};
    virtual void socketEstablished(int, void*);
    virtual void socketFailure(int, void*, int);
    // end of the overridden methods

    cMessage*   p_NOtifyTrackerMsg;
    set<string> set_Attackers;


};

#endif
