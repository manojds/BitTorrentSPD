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

#ifndef __INET_BTSPDCONNTRACKERFUNC_H_
#define __INET_BTSPDCONNTRACKERFUNC_H_

#include <omnetpp.h>
#include <map>
#include <string>


/**
 * TODO - Generated class
 */
class BTSPDConnTracker : public cSimpleModule
{
public:
    BTSPDConnTracker();
    virtual ~BTSPDConnTracker();

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void handleSelfMessage(cMessage* msg);

  private:

    void dumpConnectionsToFile();
    void storeIPtoNameMapping(cMessage* _pMsg);
    void storeConnMap(cMessage* _pMsg);
    void splitStringByCommas(const char * _pStr, std::vector<std::string>& _vector);
    void writeConnsToFile();



  protected:

    std::string s_FileName;

    std::map<std::string, std::set<std::string> > map_CurrentConnections;
    std::map<std::string, std::set<std::string> > map_AllConnections;
    std::map<std::string, std::string>            map_IPtoName;

    cMessage*   evt_DumpToFile;
    int         i_DumpingInterval;


};

#endif
