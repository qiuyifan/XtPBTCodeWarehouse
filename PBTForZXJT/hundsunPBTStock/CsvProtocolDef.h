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

        // 登录 1

        static const CsvField REQ_FIELDS_1[] = 
        {
            REQ_FIELDS_COMMON()
        };

        static const CsvField RESP_FIELDS_1[] = 
        {
            { "accountID", "资金账号", "S", 'N' },
            { "accountName", "账号名称", "S", 'N' },
        };

        // 查询资金精确查询 3
        static const CsvField REQ_FIELDS_3[] = 
        {
            REQ_FIELDS_COMMON()
        };

        static const CsvField RESP_FIELDS_3[] = 
        {
            { "accountID", "资金账号", "S", 'N' },
            { "enableBalance", "可用金额", "B", 'N' },
            { "fetchBalance", "可取金额", "B", 'N' },
            { "marketValue", "总市值", "B", 'N' },
            { "assetBalance", "总资产", "B", 'N' },
        };

        // 查询持仓 4
        static const CsvField REQ_FIELDS_4[] =
        {
            REQ_FIELDS_COMMON()
        };

        static const CsvField RESP_FIELDS_4[] =
        {
            { "accountID", "资金账号", "S", 'N' },
            { "exchangeName", "市场名称", "S", 'N' },
            { "stockCode", "证券代码", "S", 'N' },
            { "stockName", "证券名称", "S", 'N' },
            { "stockAccount", "股东账号", "S", 'N' },
            { "totalAmt", "当前拥股", "N", 'N' },
            { "enableAmount", "可用余额", "N", 'N' },
            { "lastPrice", "最新价", "B", 'N' },
            { "marketValue", "市值", "B", 'N' },
            { "costBalance", "当前成本", "B", 'N' },
            { "costPrice", "成本价", "B", 'N' },
            { "income", "盈亏", "B", 'N' },
        };

        // 查询委托 5
        static const CsvField REQ_FIELDS_5[] = 
        {
            REQ_FIELDS_COMMON()
        };

        static const CsvField RESP_FIELDS_5[] = 
        {
            { "accountID", "资金账号", "S", 'N' },
            { "entrustNo", "合同编号", "S", 'N' },
            { "exchangeName", "交易市场", "S", 'N' },
            { "stockCode", "证券代码", "S", 'N' },
            { "stockName", "证券名称", "S", 'N' },
            { "entrustDate", "委托日期", "S", 'N' },
            { "entrustTime", "委托时间", "S", 'N' },
            { "bsflage", "买卖标记", "S", 'N' },
            { "cancelInfo", "废单原因", "S", 'N' },
            { "entrustPrice", "委托价格", "B", 'N' },
            { "entrustAmount", "委托量", "N", 'N' },
            { "bizAmount", "成交数量", "N", 'N' },
            { "cancelAmount", "已撤数量", "N", 'N' },
            { "bizPrice", "成交均价", "B", 'N' },
            { "entrustStatusName", "委托状态", "S", 'N' },
            { "entrustTypeName", "委托类别", "S", 'N' },
            { "cancelInfo", "废单原因", "S", 'N' },
        };

        // 成交查询 6

        static const CsvField REQ_FIELDS_6[] = 
        {
            REQ_FIELDS_COMMON()
        };

        static const CsvField RESP_FIELDS_6[] = 
        {
            { "accountID", "资金账号", "S", 'N' },
            { "bizDate", "成交日期", "S", 'N' },
            { "bizTime", "成交时间", "S", 'N' },
            { "entrustNo", "合同编号", "S", 'N' },
            { "exchangeName", "交易市场", "S", 'N' },
            { "stockCode", "证券代码", "S", 'N' },
            { "stockName", "证券名称", "S", 'N' },
            { "bizNo", "成交编号", "S", 'N' },
            { "bsflage", "买卖标记", "S", 'N' },
            { "bizAmount", "成交数量", "N", 'N' },
            { "bizBalance", "成交金额", "B", 'N' },
            { "bizPrice", "成交价格", "B", 'N' },
        };

        // 质押明细查询 7

        static const CsvField REQ_FIELDS_7[] = 
        {
            REQ_FIELDS_COMMON()
        };

        static const CsvField RESP_FIELDS_7[] = 
        {
            { "accountID", "资金账号", "S", 'N' },
            { "exchangeType", "交易类别", "S", 'N' },
            { "stockAccount", "股东号", "S", 'N' },
            { "stockCode", "债券代码", "S", 'N' },
            { "standardCode", "标准券代码", "S", 'N' },
            { "pledgeNum", "质押数量", "N", 'N' },
        };

        // 查询信用资金 8
        static const CsvField REQ_FIELDS_8[] = 
        {
            REQ_FIELDS_COMMON()
        };

        static const CsvField RESP_FIELDS_8[] = 
        {
            { "accountID", "资金账号", "S", 'N' },
            { "perAssurescaleValue", "个人维持担保比例", "B", 'N' },
            { "enableBailBalance", "可用保证金", "B", 'N' },
            { "finMaxQuota", "融资授信额度", "B", 'N' },
            { "sloMaxQuota", "融券授信额度", "B", 'N' },
            { "underlyMarketValue", "标的证券市值", "B", 'N' },
            { "fetchBalance", "可取金额", "B", 'N' },
            { "marketValue", "总市值", "B", 'N' },
            { "assetBalance", "总资产", "B", 'N' },
            { "debt", "总负债", "B", 'N' },
        };

        // 查询信用合约持仓 9
        static const CsvField REQ_FIELDS_9[] = 
        {
            REQ_FIELDS_COMMON()
        };

        static const CsvField RESP_FIELDS_9[] = 
        {
            { "accountID", "资金账号", "S", 'N' },
            { "exchangeName", "交易所名称", "S", 'N' },
            { "stockCode", "证券代码", "S", 'N' },
            { "stockName", "股票名称", "S", 'N' },
            { "compactId", "合约编号", "S", 'N' },
            { "entrustNo", "委托编号", "S", 'N' },
            { "openDate", "合约开仓日期", "N", 'N' },
            { "crdtRatio", "融资融券保证金比例", "B", 'N' },
            { "entrustPrice", "委托价格", "B", 'N' },
            { "entrustAmount", "委托数量", "B", 'N' },
            { "businessAmount", "合约开仓数量", "B", 'N' },
            { "businessBalance", "合约开仓金额", "B", 'N' },
            { "businessFare", "合约开仓费用", "B", 'N' },
            { "compactTypeTmp", "合约类型", "S", 'N' },
            { "compactStatusTmp", "合约状态", "S", 'N' },
            { "realCompactBalance", "未还合约金额", "B", 'N' },
            { "realCompactAmount", "未还合约数量", "B", 'N' },
            { "realCompactFare", "未还合约费用", "B", 'N' },
            { "realCompactInterest", "未还合约利息", "B", 'N' },
            { "repaidInterest", "已还利息", "B", 'N' },
            { "repaidAmount", "已还数量", "B", 'N' },
            { "repaidBalance", "已还金额", "B", 'N' },
            { "compactInterest", "合约总利息", "B", 'N' },
            { "usedBailBalance", "占用保证金", "B", 'N' },
            { "yearRate", "合约年利率", "B", 'N' },
            { "retEndDate", "归还截止日", "N", 'N' },
            { "dateClear", "了结日期", "N", 'N' },
        };

        // 查询信用标的证券 10
        static const CsvField REQ_FIELDS_10[] = 
        {
            REQ_FIELDS_COMMON()
        };

        static const CsvField RESP_FIELDS_10[] = 
        {
            { "accountID", "资金账号", "S", 'N' },
            { "exchangeType", "交易所", "S", 'N' },
            { "stockCode", "证券代码", "S", 'N' },
            { "stockName", "股票名称", "S", 'N' },
            { "finStatusTmp", "融资状态", "S", 'N' },
            { "sloStatusTmp", "融券状态", "S", 'N' },
            { "sloRatio", "融券保证金比例", "B", 'N' },
            { "enableAmount", "融券可融数量", "B", 'N' },
            { "finRatio", "融资保证金比例", "B", 'N' },
            { "assureRatio", "担保品折算比例", "B", 'N' },
        };

        // 查询信用股票费率 11
        static const CsvField REQ_FIELDS_11[] = 
        {
            REQ_FIELDS_COMMON()
        };

        static const CsvField RESP_FIELDS_11[] = 
        {
            { "accountID", "资金账号", "S", 'N' },
            { "crdtrateKind", "融资融券利率费率类型", "B", 'N' },
            { "stockCode", "证券代码", "S", 'N' },
            { "yearRate", "年利率", "B", 'N' },
            { "rateDays", "利率天数", "N", 'N' },
        }; 

        // ---------------------------------------------------------------------

        static const CsvFunc ALL_FUNCS[] =
        {
            // 客户登录
            { 1, REQ_FIELDS_1, ARRAYLEN(REQ_FIELDS_1), RESP_FIELDS_1, ARRAYLEN(RESP_FIELDS_1), false, false },
            // 资金查询
            { 3, REQ_FIELDS_3, ARRAYLEN(REQ_FIELDS_3), RESP_FIELDS_3, ARRAYLEN(RESP_FIELDS_3), false, false },
            // 持仓查询
            { 4, REQ_FIELDS_4, ARRAYLEN(REQ_FIELDS_4), RESP_FIELDS_4, ARRAYLEN(RESP_FIELDS_4), true, true },
            // 委托查询
            { 5, REQ_FIELDS_5, ARRAYLEN(REQ_FIELDS_5), RESP_FIELDS_5, ARRAYLEN(RESP_FIELDS_5), true, true },
            // 成交查询
            { 6, REQ_FIELDS_6, ARRAYLEN(REQ_FIELDS_6), RESP_FIELDS_6, ARRAYLEN(RESP_FIELDS_6), true, true },
            // 质押明细查询
            { 7, REQ_FIELDS_7, ARRAYLEN(REQ_FIELDS_7), RESP_FIELDS_7, ARRAYLEN(RESP_FIELDS_7), true, true },
            // 查询信用资金
            { 8, REQ_FIELDS_8, ARRAYLEN(REQ_FIELDS_8), RESP_FIELDS_8, ARRAYLEN(RESP_FIELDS_8), false, false },
            // 查询信用合约持仓
            { 9, REQ_FIELDS_9, ARRAYLEN(REQ_FIELDS_9), RESP_FIELDS_9, ARRAYLEN(RESP_FIELDS_9), true, true },
            // 查询信用标的证券
            { 10, REQ_FIELDS_10, ARRAYLEN(REQ_FIELDS_10), RESP_FIELDS_10, ARRAYLEN(RESP_FIELDS_10), true, true },
            // 查询信用股票费率
            { 11, REQ_FIELDS_11, ARRAYLEN(REQ_FIELDS_11), RESP_FIELDS_11, ARRAYLEN(RESP_FIELDS_11), true, true },
        };
    }
}

#endif