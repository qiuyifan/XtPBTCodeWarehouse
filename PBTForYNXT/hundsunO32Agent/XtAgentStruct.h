#ifndef __XT_AGENT_STRUCT__
#define __XT_AGENT_STRUCT__

#include "bson/src/bson.h"

namespace agent
{
    struct AccountStruct
    {
        string     accountID;
        bson::bo   orderData;
        bson::bo   fundData;
        bson::bo   dealData;
        bson::bo   positionData;
    };
    typedef boost::shared_ptr<AccountStruct> AccountStructPtr;
} 

#endif