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
#include <fstream>
#include <iomanip>
#include <iostream>

#include "BTSPDSecurityStatistics.h"
#include "BTSPDCommonMsgTypes.h"
#include "BTSPDSecurityStatisticsMsgs_m.h"
#include "../BTLogImpl.h"

Define_Module(BTSPDSecurityStatistics);


using namespace std;

#define PRINT_SECURITY_STATS_MSG_TYPE   1


BTSPDSecurityStatistics::BTSPDSecurityStatistics():
        i_StatPrintInterval(1000),
        p_PrintStatTimer(NULL),
        b_PrintStatsToFile(false),
        s_StatFileName("NO_NAME"),
        i_TotalInfectedNodeCount(0),
        i_InfectionCleanedNOdeCount(0),
        i_FixedNodeCount(0)
{}

BTSPDSecurityStatistics::~BTSPDSecurityStatistics()
{}

void BTSPDSecurityStatistics::initialize()
{
    b_PrintStatsToFile = par("printStatsToFile");
    if (b_PrintStatsToFile)
    {
        s_StatFileName = par("statFileName").stdstringValue();

        time_t timer;
        time(&timer);

        char pFullFileName[256];

#ifndef WINNT
    snprintf(pFullFileName, 256,"%s_%ld.txt", s_StatFileName.c_str(), (long)timer);
#else
    _snprintf(pFullFileName, 256,"%s_%ld.txt", s_StatFileName.c_str(), (long)timer);
#endif /* WINNT */

    s_StatFileName = pFullFileName;

    }

    i_StatPrintInterval = par("statPrintInterval");

    BT_LOG_INFO(btLogSinker,"BTSPDSecurityStatistics","initialize - printStatsToFilet ["<<b_PrintStatsToFile<<
            "] statFileName ["<<s_StatFileName<<"] statPrintInterval ["<<i_StatPrintInterval<<"]");

    //just the touch the file to truncate it
    if (b_PrintStatsToFile)
    {
        ofstream myfile (s_StatFileName.c_str());
        if (myfile.is_open() == false)
        {
          throw cRuntimeError("Failed to open file [%s] for connection map dump", s_StatFileName.c_str());
          return;
        }

        myfile<<"";

        myfile.close();
    }

    p_PrintStatTimer = new cMessage("PRINT_SECURITY_STATS_MSG_TYPE",PRINT_SECURITY_STATS_MSG_TYPE);
    scheduleAt(simTime(),p_PrintStatTimer);
}

void BTSPDSecurityStatistics::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage() )
    {
        handleSelfMsg(msg);
    }
    else
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
}

void BTSPDSecurityStatistics::handleSelfMsg(cMessage *msg)
{
    switch (msg->getKind())
    {
        case PRINT_SECURITY_STATS_MSG_TYPE:
            statPrintTimerExpired(msg);
            break;

        default:
            throw cRuntimeError("BTSPDSecurityStatistics::handleSelfMsg - unknown message received. kind [%d], name[%s]",
                    msg->getKind(), msg->getName());
            break;
    }
}

void BTSPDSecurityStatistics::statPrintTimerExpired(cMessage *msg)
{
    printStats();
    scheduleAt(simTime() + i_StatPrintInterval, msg);

}

void BTSPDSecurityStatistics::printStats()
{
    stringstream strm;
    strm<<"Time ,"<<setfill(' ')<<setw(10)<<simTime()<<
            ", Vulnerability Fixed Node Count, "<<setfill(' ')<<setw(5)<<i_FixedNodeCount<<
            ", Total Infected Node Count, "<<setfill(' ')<<setw(5)<<i_TotalInfectedNodeCount<<
            ", Infection Cleaned Node Count, "<<setfill(' ')<<setw(5)<<i_InfectionCleanedNOdeCount<<
            ", Current infected Node Count, "<<setfill(' ')<<setw(5)<<i_TotalInfectedNodeCount - i_InfectionCleanedNOdeCount<<std::endl;

    BT_LOG_INFO(btLogSinker,"BTSPDSecurityStatistics","printStats - printing security statistics \n"<<strm.str());

    if (b_PrintStatsToFile)
    {
        ofstream myfile (s_StatFileName.c_str(), ios::app);
        if (myfile.is_open() == false)
        {
          throw cRuntimeError("Failed to open file [%s] for connection map dump", s_StatFileName.c_str());
          return;
        }

        myfile<<strm.str();

        myfile.close();
    }
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
    i_TotalInfectedNodeCount++;

    std::map<std::string,int>::iterator itr= map_InfectedNodes.find(_sNodeType);
    if(itr == map_InfectedNodes.end())
    {
        map_InfectedNodes[_sNodeType]=0;
    }

    map_InfectedNodes[_sNodeType]++;
}



void BTSPDSecurityStatistics::increaseInfectionCleanedNodeCount(const std::string & _sNodeType)
{
    i_InfectionCleanedNOdeCount++;

    std::map<std::string,int>::iterator itr=  map_InfectionCleanedNodes.find(_sNodeType);
    if(itr == map_InfectionCleanedNodes.end())
    {
        map_InfectionCleanedNodes[_sNodeType]=0;
    }

    map_InfectionCleanedNodes[_sNodeType]++;

}

void BTSPDSecurityStatistics::nodeVulnerabilityFixed(const std::string & _sNodeType)
{
    i_FixedNodeCount++;

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
