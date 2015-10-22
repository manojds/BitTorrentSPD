#ifndef BTSPDTIMEUTILS_H
#define BTSPDTIMEUTILS_H
#include <sys/timeb.h>
#include <string.h>


class BTSPDTimeUtils
{

public:
    static inline void fillFileNameWithTimeStamp(const char * _pFileNameIn, char * _pFileNameOut)
    {
        time_t timer;
        time(&timer);

        struct timeb tbNow;
        char szNow[128];

        ftime(&tbNow);
        strftime(szNow, sizeof (szNow), "%m%d_%H%M%S", localtime(&tbNow.time));

    #ifndef WINNT
    snprintf(_pFileNameOut, 256,"%s_%s.txt", _pFileNameIn, szNow);
    #else
    _snprintf(_pFileNameOut, 256,"%s_%s.txt", _pFileNameIn, szNow);
    #endif /* WINNT */
    }
};

#endif  /* BTSPDTIMEUTILS_H */
