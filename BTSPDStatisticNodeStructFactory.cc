/*
 * BTSPDStatisticNodeStructFactory.cpp
 *
 *  Created on: Oct 9, 2015
 *      Author: manojd
 */

#include "BTSPDStatisticNodeStructFactory.h"

BTSPDStatisticNodeStructFactory::BTSPDStatisticNodeStructFactory() :
i_NextAvailableSlot(0),
p_ActiveChunk(NULL)
{
    renewTheChunk();
}

BTSPDStatisticNodeStructFactory::~BTSPDStatisticNodeStructFactory()
{

}

NodeStruct * BTSPDStatisticNodeStructFactory::getNodeStruct()
{
    NodeStruct *  pRet(NULL);

    if (lst_FreeList.size() > 0 )
    {
        pRet = lst_FreeList.front();
        lst_FreeList.pop_front();

        pRet->reset();
    }
    else
    {
        checkForRenewal();

        pRet = p_ActiveChunk + i_NextAvailableSlot;

        i_NextAvailableSlot++;
    }

    return pRet;

}

void BTSPDStatisticNodeStructFactory::releaseNodeStruct(NodeStruct* _pNode)
{
    lst_FreeList.push_back(_pNode);
}

void BTSPDStatisticNodeStructFactory::checkForRenewal()
{
    if (i_NextAvailableSlot >= UNIT_SIZE )
        renewTheChunk();

}

void BTSPDStatisticNodeStructFactory::renewTheChunk()
{
    p_ActiveChunk = new NodeStruct[UNIT_SIZE];
    i_NextAvailableSlot = 0;
}

