#include "Stock/StockDataDict.h"
#include "hundsunO32ToolFunc.h"
#include "hundsunO32DataDict.h"

namespace broker
{
    namespace stock
    {
        CsvToolFunc::CsvToolFunc()
        {
        }

        CsvToolFunc::~CsvToolFunc()
        {
        }

        char CsvToolFunc::getExchangeType(string str)
        {
            if (str.compare("上交所A") == 0)
            {
                return EXCHANGE_TYPE_SHANGHAI;
            }
            else if (str.compare("深交所A") == 0)
            {
                return EXCHANGE_TYPE_SHENZHEN;
            }
            else if (str.compare("港股通") == 0)
            {
                return 'G';
            }
            return EXCHANGE_TYPE_UNKNOWN;
        }

        char CsvToolFunc::getEntrustBS(string str)
        {
            if (str.find("买") != string::npos || str.find("申购") != string::npos) 
            {
                return CSV_ENTRUST_BS_BUY;
            }
            else if (str.find("卖") != string::npos || str.find("直接还款") != string::npos || str.find("直接还券") != string::npos || str.find("赎回") != string::npos)
            {
                return CSV_ENTRUST_BS_SELL;
            }
            else if (str.find("融资回购") != string::npos)
            {
                return CSV_ENTRUST_BS_BUY;
            }
            else if (str.find("融券回购") != string::npos)
            {
                return CSV_ENTRUST_BS_SELL;
            }
            return CSV_ENTRUST_BS_UNKNOWN;
        }

        char CsvToolFunc::getEntrusType(string str)
        {
            if (str.find("融券") != string::npos)
            {
                return ENTRUST_TYPE_RQWT;
            }
            else if (str.find("融资") != string::npos)
            {
                return ENTRUST_TYPE_RZWT;
            }
            else if (str.find("信用") != string::npos)
            {
                return ENTRUST_CREDIT_NORMAL;
            }
            return ENTRUST_TYPE_BS;
        }

        char CsvToolFunc::getEntrusPorp(string str)
        {
            if (str.find("限价") != string::npos)
            {
                return ENTRUST_PROP_LIMIT_PRICE;
            }
            else if (str.find("回购") != string::npos)
            {
                return ENTRUST_PROP_BUYBACK;
            }
            else if (str.find("直接还款") != string::npos)
            {
                return ENTRUST_PROP_XJHK;
            }
            else if (str.find("直接还券") != string::npos)
            {
                return ENTRUST_PROP_XQHQ;
            }
            return ENTRUST_PROP_LIMIT_PRICE;
        }

        char CsvToolFunc::getEntrustStatus(string str)
        {
            if (str.compare("等待撤单") == 0)
            {
                return CSV_ENTRUST_STATUS_WAIT_END;
            }
            else if (str.compare("未报") == 0)
            {
                return CSV_ENTRUST_STATUS_UNREPORTED;
            }
            else if (str.compare("待报") == 0)
            {
                return CSV_ENTRUST_STATUS_WAIT_REPORTING;
            }
            else if (str.compare("已报") == 0)
            {
                return CSV_ENTRUST_STATUS_REPORTED;
            }
            else if (str.compare("已报待撤") == 0)
            {
                return CSV_ENTRUST_STATUS_REPORTED_CANCEL;
            }
            else if (str.compare("部成待撤") == 0)
            {
                return CSV_ENTRUST_STATUS_PARTSUCC_CANCEL;
            }
            else if (str.compare("部撤") == 0)
            {
                return CSV_ENTRUST_STATUS_PART_CANCEL;
            }
            else if (str.compare("已撤") == 0)
            {
                return ENTRUST_STATUS_CANCELED;
            }
            else if (str.compare("部成") == 0)
            {
                return CSV_ENTRUST_STATUS_PART_SUCC;
            }
            else if (str.compare("已成") == 0)
            {
                return CSV_ENTRUST_STATUS_SUCCEEDED;
            }
            else if (str.compare("废单") == 0)
            {
                return CSV_ENTRUST_STATUS_JUNK;
            }
            else if (str.compare("未知") == 0)
            {
                return CSV_ENTRUST_STATUS_UNKNOWN;
            }
            return CSV_ENTRUST_STATUS_UNKNOWN;
        }

        char CsvToolFunc::getCompactType(string str)
        {
            if (str.find("融资") != string::npos)
            {
                return CSV_COMPACT_TYPE_FIN;
            }
            else if (str.find("融券") != string::npos)
            {
                return CSV_COMPACT_TYPE_SLO;
            }
            return 0;
        }

        char CsvToolFunc::getCompactStatus(string str)
        {
            if (str.find("未归还") != string::npos)
            {
                return CSV_COMPACT_STATUS_UNDONE;
            }
            else if (str.find("部分归还") != string::npos)
            {
                return CSV_COMPACT_STATUS_PART_DONE;
            }
            else if (str.find("已归还") != string::npos)
            {
                return CSV_COMPACT_STATUS_DONE;
            }
            else if (str.find("自行了结") != string::npos)
            {
                return CSV_COMPACT_STATUS_DONE_BY_SELF;
            }
            else if (str.find("手工了结") != string::npos)
            {
                return CSV_COMPACT_STATUS_DONE_BY_HAND;
            }
            else if (str.find("未形成负债") != string::npos)
            {
                return CSV_COMPACT_STATUS_NOT_DEBT;
            }
            return CSV_COMPACT_STATUS_UNKNOWN;
        }

        string CsvToolFunc::getSmtStkStatus(string str)
        {
            if (str.find("正常") != string::npos)
            {
                return string(1,char(CSV_COMPACT_STATUS_OK));
            }
            else if (str.find("暂停") != string::npos)
            {
                return string(1,char(CSV_COMPACT_STATUS_STOP));
            }
            return string(1,char(CSV_COMPACT_STATUS_STOP));
        }

        string CsvToolFunc::getTradeName(string str)
        {
            if (str.find("券") != string::npos || str.find("资") != string::npos || str.find("担保品") != string::npos)
            {
                return str;
            }
            return "";
        }
    }
}