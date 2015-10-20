/*
 * BTSPDCommon.h
 *
 *  Created on: Jun 27, 2015
 *      Author: manojd
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <string>

enum PEER_FILL_METHOD
{
    FILL_ALL =0,
    ONLY_SEEDERS = 1,
    HIDE_DOWNLOADERS = 2
};

inline std::string fillMethodToString(PEER_FILL_METHOD fillMethod)
{

    switch(fillMethod)
    {
    case FILL_ALL:
        return "FILL_ALL";
        break;

    case ONLY_SEEDERS:
        return "ONLY_SEEDERS";
        break;

    case HIDE_DOWNLOADERS:
        return "HIDE_DOWNLOADERS";
        break;

    default:
        return "UNKNOWN";
        break;
    }
}

enum NODE_TYPE
{
    NORMAL_PEER = 0 ,
    RELAY_PEER = 1
};



#endif /* COMMON_H_ */
