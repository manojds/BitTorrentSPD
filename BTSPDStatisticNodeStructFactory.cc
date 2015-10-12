/*
 * BTSPDStatisticNodeStructFactory.cpp
 *
 *  Created on: Oct 9, 2015
 *      Author: manojd
 */

#include "BTSPDStatisticNodeStructFactory.h"

BTSPDStatisticNodeStructFactory::BTSPDStatisticNodeStructFactory() :
BTSimpleObjFactory<NodeStruct>(UNIT_SIZE)
{

}

BTSPDStatisticNodeStructFactory::~BTSPDStatisticNodeStructFactory()
{

}

NodeStruct * BTSPDStatisticNodeStructFactory::getObject()
{
    NodeStruct *  pRet = BTSimpleObjFactory<NodeStruct>::getObject();
    pRet->reset();

    return pRet;

}



