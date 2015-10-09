/*
 * BTSPDStatisticNodeStructFactory.h
 *
 *  Created on: Oct 9, 2015
 *      Author: manojd
 */

#ifndef BTSPDSTATISTICNODESTRUCTFACTORY_H_
#define BTSPDSTATISTICNODESTRUCTFACTORY_H_
#include <string>
#include <list>
#include "BTSPDCommon.h"

using std::string;
using std::list;

#define UNIT_SIZE   100

class NodeStruct
{
public:
    NodeStruct():
        b_ActiveInSwarm(false),
        b_NodeAlive(true),
        b_DownloadCompleted(false),
        e_NodeType(NORMAL_PEER),
        s_NodeName("NOT_SET")
    {}

    void reset()
    {
        b_ActiveInSwarm = false;
        b_NodeAlive = true;
        b_DownloadCompleted = false;
        e_NodeType = NORMAL_PEER;
        s_NodeName = "NOT_SET";
    }

    bool        b_ActiveInSwarm;
    bool        b_NodeAlive;
    bool        b_DownloadCompleted;
    NODE_TYPE   e_NodeType;     // 0 for true peer, 1 for relay
    string      s_NodeName;
};

/*!
 * This class handles the creation of NodeStruct objects.
 * But destroying of those NodeStruct are not handled  currently
 * because handling destroying those object involves lot of house keeping
 */
class BTSPDStatisticNodeStructFactory
{
public:
    BTSPDStatisticNodeStructFactory();
    virtual ~BTSPDStatisticNodeStructFactory();


    NodeStruct *    getNodeStruct();
    void            releaseNodeStruct(NodeStruct* _pNode);

protected:
    void                checkForRenewal();
    void                renewTheChunk();
    int                 i_NextAvailableSlot;
    NodeStruct *        p_ActiveChunk;
    list<NodeStruct*>   lst_FreeList;



};

#endif /* BTSPDSTATISTICNODESTRUCTFACTORY_H_ */
