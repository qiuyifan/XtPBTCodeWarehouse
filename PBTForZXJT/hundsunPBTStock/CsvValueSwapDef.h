#ifndef __CSV__VALUE_SWAP_DEF_H__
#define __CSV__VALUE_SWAP_DEF_H__

#include "common/Stdafx.h"
#include "utils/mathex.h"
#include "ext_utils/swap_map.h"
#include "common/Trader.h"
#include "BaseCommon.h"
#include "Stock/StockDataDict.h"
#include "CsvDataDict.h"

namespace broker
{
    using namespace utils;

    namespace stock
    {

        static const val_pair VP_EXCH_TYPE_U2P[] = 
        {
            { CSV_EXCHANGE_TYPE_SH, char(EXCHANGE_TYPE_SHANGHAI) },
            { CSV_EXCHANGE_TYPE_SZ, char(EXCHANGE_TYPE_SHENZHEN) },
        };

        static const utils::val_map SWAP_TABLES[] = 
        {
            { "exchangeType", "exchangeType", VP_EXCH_TYPE_U2P, ARRAYLEN(VP_EXCH_TYPE_U2P) },
        };
    }
}

#endif