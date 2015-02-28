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

#include "BTThreatHandler.h"
#include "../BitTorrent/BTLogImpl.h"

Define_Module(BTThreatHandler);

int BTThreatHandler::i_CurrentMaliciousNodeCount(0);

BTThreatHandler::BTThreatHandler()
{}

BTThreatHandler::~BTThreatHandler()
{}

void BTThreatHandler::initialize()
{
    TCPGenericCliAppBase::initialize();

    int iMaxMaliciousNodes= par("maliciousNodeCount");

    if(i_CurrentMaliciousNodeCount < iMaxMaliciousNodes)
    {
        b_Malicious=true;
        i_CurrentMaliciousNodeCount++;
    }

    b_Vulnerable= par("vulnerable");

    BT_LOG_INFO(btLogSinker,"BTThreatHandler::initialize","["<<this->getParentModule()->getFullName()<<
            "] ***** Threat Handler initialized. Vulnerable ["<< b_Vulnerable?"true":"false"<<
                    "] Malicious["<<b_Malicious?"true":"false"<<"] Current malicious node count ["
                    <<i_CurrentMaliciousNodeCount<<"] Max malicious node count ["<<iMaxMaliciousNodes<<"]");
}

void BTThreatHandler::handleMessage(cMessage *msg)
{
    if(msg->arrivedOn("btorrentIn"))
    {
        handleMsgFromBT(msg);
    }
    else
    {
        TCPGenericCliAppBase::handleMessage(msg);

    }
}

void BTThreatHandler::handleTimer(cMessage *msg)
{

}

void BTThreatHandler::socketEstablished(int connId, void *ptr)
{
    TCPGenericCliAppBase::socketEstablished(connId, ptr);

    //TODO ::send the attack message

}

void BTThreatHandler::handleMsgFromBT(cMessage* msg)
{
    BT_LOG_INFO (btLogSinker,"BTThreatHandler::handleMsgFromBT","["<<getParentModule()->getFullName()<<"]  Message of kind ["<<
            msg->getKind()<<"] received from PeerWire module");
    //decode the message
    //if attack message go in to malicious mode
    //if new address learned message attack to that node
}


void BTThreatHandler::newAddrFound(const std::string & _sIP, const std::string & _sPort)
{
    BT_LOG_INFO(btLogSinker,"BTThreatHandler::newAddrFound","["<<getParentModule()->getFullName()<<"]  New address found ["<<
            _sIP<<":"<<_sPort<< "]");
}

bool BTThreatHandler::isMalicious()
{
    return b_Malicious;
}
