#ifndef __CSV_TOOL_FUNC_H__
#define __CSV_TOOL_FUNC_H__
#include "common/Stdafx.h"

namespace broker
{
    namespace stock
    {
        class CsvToolFunc
        {
        public:
            CsvToolFunc();
            ~CsvToolFunc();

            char getExchangeType(string str);
            char getEntrustBS(string str);
            char getEntrusType(string str);
            char getEntrusPorp(string str);
            char getEntrustStatus(string str);
            char getCompactType(string str);
            char getCompactStatus(string str);
            string getSmtStkStatus(string str);
            string getTradeName(string str);
        };
        typedef boost::shared_ptr<CsvToolFunc> CsvToolFuncPtr;
    }
}
#endif