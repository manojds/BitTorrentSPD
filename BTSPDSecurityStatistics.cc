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

#include "BTSPDSecurityStatistics.h"
#include "BTSPDCommonMsgTypes.h"
#include "BTSPDSecurityStatisticsMsgs_m.h"
#include "../BTLogImpl.h"

Define_Module(BTSPDSecurityStatistics);

BTSPDSecurityStatistics::BTSPDSecurityStatistics()
{}

BTSPDSecurityStatistics::~BTSPDSecurityStatistics()
{}

void BTSPDSecurityStatistics::initialize()
{

}

void BTSPDSecurityStatistics::handleMessage(cMessage *msg)
{
    BTSPDSecurityStatus * pSecMsg=check_and_cast<BTSPDSecurityStatus *>(msg);

    switch (msg->getKind())
    {
    case BTSPD_INFECTED_MSG_TYPE:
        nodeInfected(pSecMsg->moduleType());
        break;

    case BTSPD_VULNERABILITY_FIXED_MSG_TYPE:
        nodeVulnerabilityFixed(pSecMsg->moduleType());
        break;

    case BTSPD_INFECTION_CLEANED_MSG_TYPE:
        nodeInfectionCleaned(pSecMsg->moduleType());
        break;

    default:
        throw cRuntimeError("BTSPDSecurityStatistics::handleMessage - unknown message received. kind [%d], name[%s]",
                msg->getKind(), msg->getName());
        break;

    }

    delete msg;
}

void BTSPDSecurityStatistics::nodeInfected(const std::string & _sNodeType)
{
    increaseInfectedNodeCount(_sNodeType);

}



void BTSPDSecurityStatistics::nodeInfectionCleaned(const std::string & _sNodeType)
{

    increaseInfectionCleanedNodeCount(_sNodeType);

}

void BTSPDSecurityStatistics::increaseInfectedNodeCount(const std::string & _sNodeType)
{
    std::map<std::string,int>::iterator itr= map_InfectedNodes.find(_sNodeType);
    if(itr == map_InfectedNodes.end())
    {
        map_InfectedNodes[_sNodeType]=0;
    }

    map_InfectedNodes[_sNodeType]++;
}



void BTSPDSecurityStatistics::increaseInfectionCleanedNodeCount(const std::string & _sNodeType)
{
    std::map<std::string,int>::iterator itr=  map_InfectionCleanedNodes.find(_sNodeType);
    if(itr == map_InfectionCleanedNodes.end())
    {
        map_InfectionCleanedNodes[_sNodeType]=0;
    }

    map_InfectionCleanedNodes[_sNodeType]++;

}

void BTSPDSecurityStatistics::nodeVulnerabilityFixed(const std::string & _sNodeType)
{
    std::map<std::string,int>::iterator itr= map_FixedNodes.find(_sNodeType);
    if(itr == map_FixedNodes.end())
    {
        map_FixedNodes[_sNodeType]=0;
    }

    map_FixedNodes[_sNodeType]++;

}

void BTSPDSecurityStatistics::printInfectedNodeCounts()
{
    std::map<std::string,int>::iterator itr= map_InfectedNodes.begin();
    for(; itr != map_InfectedNodes.end() ; itr++)
    {
        BT_LOG_INFO(btLogSinker,"BTSPDSecurityStatistics","Overall infected node count ["<< itr->first<<
                    "]- ["<< itr->second <<"] ");
    }

}

void BTSPDSecurityStatistics::printInfectionCleanedNodeCounts()
{
    std::map<std::string,int>::iterator itr= map_InfectionCleanedNodes.begin();
    for(; itr != map_InfectionCleanedNodes.end() ; itr++)
    {
        BT_LOG_INFO(btLogSinker,"BTSPDSecurityStatistics","Infection Cleaned node count ["<< itr->first<<
                    "]- ["<< itr->second <<"] ");
    }
}

void BTSPDSecurityStatistics::printVulnerabilityFixedNodeCounts()
{
    std::map<std::string,int>::iterator itr= map_FixedNodes.begin();
    for(; itr != map_FixedNodes.end() ; itr++)
    {
        BT_LOG_INFO(btLogSinker,"BTSPDSecurityStatistics","Vulnerability Fixed node count ["<< itr->first<<
                    "]- ["<< itr->second <<"] ");
    }
}

void BTSPDSecurityStatistics::finish()
{
    printInfectedNodeCounts();
    printVulnerabilityFixedNodeCounts();
    printInfectionCleanedNodeCounts();
}
