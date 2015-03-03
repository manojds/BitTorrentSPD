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

#ifndef __INET_BTSPDSECURITYSTATISTICS_H_
#define __INET_BTSPDSECURITYSTATISTICS_H_

#include <omnetpp.h>
#include <map>

class BTSPDSecurityStatistics : public cSimpleModule
{
  public:
    BTSPDSecurityStatistics();
    virtual ~BTSPDSecurityStatistics();

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();

  protected:
    virtual void nodeInfected(const std::string & _sNodeType);
    virtual void nodeVulnerabilityFixed(const std::string & _sNodeType);
    virtual void nodeInfectionCleaned(const std::string & _sNodeType);
    virtual void printOverallInfectedNodeCounts();
    virtual void printFinalInfectedNodeCounts();
    virtual void printVulnerabilityFixedNodeCounts();
    virtual void printVulnerabilityFixedNodeCounts();

    void increaseOverallInfectedNodeCount(const std::string & _sNodeType);
    void increaseCurrentInfectedNodeCount(const std::string & _sNodeType);
    void decreaseCurrentInfectedNodeCount(const std::string & _sNodeType);



    std::map<std::string,int>   map_InfectedNodes;
    std::map<std::string,int>   map_FinalInfectedNodes;
    std::map<std::string,int>   map_FixedNodes;
};

#endif
