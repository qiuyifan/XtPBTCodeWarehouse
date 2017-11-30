#ifndef __CSV_DATA_DICT_H__
#define __CSV_DATA_DICT_H__

namespace broker
{
    namespace stock
    {
        static const string CSV_EXCHANGE_TYPE_SH = "SH";  // 上海交易所
        static const string CSV_EXCHANGE_TYPE_SZ = "SZ";  // 深圳交易所

        // 委托状态
        enum
        {
            CSV_ENTRUST_STATUS_WAIT_END = 0,  //委托状态已经在ENTRUST_STATUS_CANCELED或以上，但是成交数额还不够，等成交回报来
            CSV_ENTRUST_STATUS_UNREPORTED = 48,  //未报
            CSV_ENTRUST_STATUS_WAIT_REPORTING, //待报
            CSV_ENTRUST_STATUS_REPORTED, //已报
            CSV_ENTRUST_STATUS_REPORTED_CANCEL, //已报待撤
            CSV_ENTRUST_STATUS_PARTSUCC_CANCEL, //部成待撤
            CSV_ENTRUST_STATUS_PART_CANCEL, //部撤
            CSV_ENTRUST_STATUS_CANCELED, //已撤
            CSV_ENTRUST_STATUS_PART_SUCC, //部成
            CSV_ENTRUST_STATUS_SUCCEEDED, //已成
            CSV_ENTRUST_STATUS_JUNK, //废单
            CSV_ENTRUST_STATUS_DETERMINED = 86,  //已确认
            CSV_ENTRUST_STATUS_UNKNOWN = 255,  //未知
        };

        // 委托买卖类别
        enum
        {
            CSV_ENTRUST_BS_UNKNOWN           = 0, // 未知
            CSV_ENTRUST_BS_BUY               = '1', // 买入
            CSV_ENTRUST_BS_SELL              = '2', // 卖出
        };

        // 负债合约类型
        enum
        {
            CSV_COMPACT_TYPE_UNKNOWN        = 0,        // 未知
            CSV_COMPACT_TYPE_FIN            = '0',      // 融资负债
            CSV_COMPACT_TYPE_SLO            = '1'       // 融券负债
        };

        //合约状态
        enum
        {
            CSV_COMPACT_STATUS_UNKNOWN = 0,  //未知
            CSV_COMPACT_STATUS_UNDONE = '0',  //未归还
            CSV_COMPACT_STATUS_PART_DONE = '1',  //部分归还
            CSV_COMPACT_STATUS_DONE = '2',  //已归还
            CSV_COMPACT_STATUS_DONE_BY_SELF = '3',  //自行了结
            CSV_COMPACT_STATUS_DONE_BY_HAND = '4',  //手工了结
            CSV_COMPACT_STATUS_NOT_DEBT = '5',  //未形成负债
        };

        //标的状态
        enum
        {
            CSV_COMPACT_STATUS_OK = '0',  //正常
            CSV_COMPACT_STATUS_STOP = '1',  //暂停
        };

    }
}

#endif