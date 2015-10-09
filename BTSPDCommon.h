/*
 * BTSPDCommon.h
 *
 *  Created on: Jun 27, 2015
 *      Author: manojd
 */

#ifndef COMMON_H_
#define COMMON_H_

enum PEER_FILL_METHOD
{
    FILL_ALL =0,
    ONLY_SEEDERS = 1,
    HIDE_DOWNLOADERS = 2
};

enum NODE_TYPE
{
    NORMAL_PEER = 0 ,
    RELAY_PEER = 1
};



#endif /* COMMON_H_ */
