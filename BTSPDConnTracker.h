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
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
    virtual void handleSelfMessage(cMessage* msg);

  private:

    virtual void dumpConnectionsToFile();
    virtual void handleNewNodeCreationMsg(cMessage* _pMsg);
    virtual void handleNodeReadyToLeaveMsg(cMessage* _pMsg);
    virtual void handleNodeLeaveMsg(cMessage* _pMsg);
    virtual void handleNewConnectionMsg(cMessage* _pMsg);
    virtual void handleConnectionLostMsg(cMessage* _pMsg);
    virtual void handleDwlCompleteMsg(cMessage* _pMsg);

    void constructTerminalNameMapping();
    std::string getNodeNameWithTErminalType(const std::string & _sNodeName);
    void dumpConnMapToFile(std::map<std::string, std::set<std::string> > & _mapConnMap,
            const std::string & _sFileName);

    void splitStringByCommas(const char * _pStr, std::vector<std::string>& _vector);
    void writeConnsToFile();



  protected:

    bool        b_enableConnMapDumping;
    bool        b_PrintActiveConn;
    int         i_DumpingInterval;
    int         i_LastConnDumpFileIndex;
    cMessage*   evt_DumpToFile;

    std::string s_FileName;

    //this map contains active connections of all nodes
    std::map<std::string, std::set<std::string> > map_CurrentConnections;
    //this map contains all established connections of all nodes
    std::map<std::string, std::set<std::string> > map_AllConnections;
    //this map holds node name to IP mapping
    std::map<std::string, std::string>            map_IPtoName;
    std::map<std::string, std::string>            map_TerminalNames;



};

#endif
