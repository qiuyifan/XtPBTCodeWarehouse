#ifndef __CSV_PROTOCOL_DEF_H__
#define __CSV_PROTOCOL_DEF_H__

#include <boost/any.hpp>
#include "CsvProtocol.h"

namespace broker
{
    namespace stock
    {
#define ARRAYLEN(x) ((sizeof((x)) / (sizeof(((x)[0])))))

#define REQ_FIELDS_COMMON()\
        { "accountID", "账号", "S", 'Y' },\
        { "passWord", "密码", "S", 'Y' },

        // 查询资金精确查询 3
        static const CsvField REQ_FIELDS_3[] = 
        {
            REQ_FIELDS_COMMON()
        };

        static const CsvField RESP_FIELDS_3[] = 
        {
            { "资产单元名称", "资产单元名称", "S", 'N' },
            { "T+0交易可用金额", "可用金额", "B", 'N' },
            { "T+1交易可用金额", "可取金额", "B", 'N' },
            { "股票股票市值", "总市值", "B", 'N' },
            { "单元总资产", "总资产", "B", 'N' },
        };

        // 查询持仓 4
        static const CsvField REQ_FIELDS_4[] =
        {
            REQ_FIELDS_COMMON()
        };

        static const CsvField RESP_FIELDS_4[] =
        {
            //{ "产品名称", "产品名称", "S", 'N' },
            { "交易市场", "市场名称", "S", 'N' },
            { "证券代码", "证券代码", "S", 'N' },
            { "证券名称", "证券名称", "S", 'N' },
            { "股东账户", "股东账号", "S", 'N' },
            { "持仓数量", "当前拥股", "B", 'N' },
            { "T0交易可用", "可用余额", "B", 'N' },
            { "价格最新价", "最新价", "B", 'N' },
            { "市值", "市值", "B", 'N' },
            { "买入成本", "当前成本", "B", 'N' },
            { "买入成本价", "成本价", "B", 'N' },
            { "浮动盈亏", "盈亏", "B", 'N' },
        };

        // 查询委托 5
        static const CsvField REQ_FIELDS_5[] = 
        {
            REQ_FIELDS_COMMON()
        };

        static const CsvField RESP_FIELDS_5[] = 
        {
            //{ "accountID", "资金账号", "S", 'N' },
            { "委托序号", "合同编号", "N", 'N' },
            { "市场", "交易市场", "S", 'N' },
            { "证券代码", "证券代码", "S", 'N' },
            { "证券名称", "证券名称", "S", 'N' },
            { "委托日期", "委托日期", "N", 'N' },
            { "委托时间", "委托时间", "N", 'N' },
            { "买卖类别", "买卖标记", "S", 'N' },
            //{ "cancelInfo", "废单原因", "S", 'N' },
            { "委托价格", "委托价格", "B", 'N' },
            { "委托数量", "委托量", "B", 'N' },
            { "成交数量", "成交数量", "B", 'N' },
            { "撤单数量", "已撤数量", "B", 'N' },
            { "成交金额", "成交金额", "B", 'N' },
            { "委托状态", "委托状态", "S", 'N' },
            { "报价类型", "委托类别", "S", 'N' },
        };

        // 成交查询 6

        static const CsvField REQ_FIELDS_6[] = 
        {
            REQ_FIELDS_COMMON()
        };

        static const CsvField RESP_FIELDS_6[] = 
        {
            //{ "accountID", "资金账号", "S", 'N' },
            { "交易日期", "成交日期", "N", 'N' },
            { "成交时间", "成交时间", "N", 'N' },
            { "委托序号", "合同编号", "N", 'N' },
            { "市场", "交易市场", "S", 'N' },
            { "证券代码", "证券代码", "S", 'N' },
            { "证券名称", "证券名称", "S", 'N' },
            { "成交序号", "成交编号", "N", 'N' },
            { "委托方向", "买卖标记", "S", 'N' },
            { "成交数量", "成交数量", "N", 'N' },
            { "成交金额", "成交金额", "N", 'N' },
            { "成交价格", "成交价格", "N", 'N' },
        };

        // ---------------------------------------------------------------------

        static const CsvFunc ALL_FUNCS[] =
        {
            // 资金查询
            { 0, REQ_FIELDS_3, ARRAYLEN(REQ_FIELDS_3), RESP_FIELDS_3, ARRAYLEN(RESP_FIELDS_3), false, false },
            // 持仓查询
            { 3, REQ_FIELDS_4, ARRAYLEN(REQ_FIELDS_4), RESP_FIELDS_4, ARRAYLEN(RESP_FIELDS_4), true, true },
            // 委托查询
            { 1, REQ_FIELDS_5, ARRAYLEN(REQ_FIELDS_5), RESP_FIELDS_5, ARRAYLEN(RESP_FIELDS_5), true, true },
            // 成交查询
            { 2, REQ_FIELDS_6, ARRAYLEN(REQ_FIELDS_6), RESP_FIELDS_6, ARRAYLEN(RESP_FIELDS_6), true, true },
        };
    }
}

#endif