#ifndef XT_AGENT_MATCH_DEF_H
#define XT_AGENT_MATCH_DEF_H
#include "XtAgentEnum.h"

#define ARRAYLEN(x) ((sizeof((x)) / (sizeof(((x)[0])))))
namespace agent
{
    struct FieldMatchUnit
    {
        string dst;     // 目标字段
        string src;     // 源字段
        char method;    // 值转换方式
    };

    struct FuncMatchUnit
    {
        int funcNo;                         // 功能号
        const FieldMatchUnit* coverFields;  // 转换表
        int coverCnt;                       // 转换表长度
        string fieldSuffix;                 // 文件后缀
    };

    // ---------------------------------------------------------------------

    static const FieldMatchUnit FIELD_PAIR_LOGIN[] = 
    {
        { "accountID", "", SWAP_STR},
        { "accountName", "单元名称", SWAP_STR},
    };

    static const FieldMatchUnit FIELD_PAIR_FUND[] = 
    {
        { "accountID", "", SWAP_STR},
        { "enableBalance", "T+0可用", SWAP_DOUBLE},
        { "fetchBalance", "当前现金余额", SWAP_DOUBLE},
        { "marketValue", "股票资产", SWAP_DOUBLE},
        { "assetBalance", "单元净值", SWAP_DOUBLE},
    };

    static const FieldMatchUnit FIELD_PAIR_ORDER[] = 
    {
        { "accountID", "", SWAP_STR},
        { "entrustNo", "委托序号", SWAP_STR},
        { "exchangeName", "交易市场", SWAP_STR},
        { "stockCode", "证券代码", SWAP_STR},
        { "stockName", "证券名称", SWAP_STR},
        { "entrustDate", "业务日期", SWAP_TIME},
        { "entrustTime", "委托时间", SWAP_TIME},
        { "bsflage", "委托方向", SWAP_STR},
        { "entrustStatusName", "委托状态", SWAP_STR},
        { "entrustPrice", "委托价格", SWAP_DOUBLE},
        { "entrustAmount", "委托数量", SWAP_INT},
        { "bizAmount", "成交数量", SWAP_INT},
        { "cancelAmount", "撤单数量", SWAP_INT},
        { "bizPrice", "成交均价", SWAP_DOUBLE},
        { "cancelInfo", "废单原因", SWAP_STR},
    };

    static const FieldMatchUnit FIELD_PAIR_BIZ[] = 
    {
        { "accountID", "", SWAP_STR},
        { "bizDate", "业务日期", SWAP_TIME},
        { "bizTime", "成交时间", SWAP_TIME},
        { "entrustNo", "委托序号", SWAP_STR},
        { "exchangeName", "", SWAP_STR},
        { "stockCode", "证券代码", SWAP_STR},
        { "stockName", "证券名称", SWAP_STR},
        { "bizNo", "成交序号", SWAP_STR},
        { "bsflage", "委托方向", SWAP_STR},
        { "bizAmount", "成交数量", SWAP_INT},
        { "bizBalance", "成交金额", SWAP_DOUBLE},
        { "bizPrice", "成交均价", SWAP_DOUBLE},
    };

    static const FieldMatchUnit FIELD_PAIR_POSITION[] = 
    {
        { "accountID", "", SWAP_STR},
        { "exchangeName", "交易市场", SWAP_STR},
        { "stockCode", "证券代码", SWAP_STR},
        { "stockName", "证券名称", SWAP_STR},
        { "stockAccount", "股东", SWAP_STR},
        { "totalAmt", "持仓数量", SWAP_INT},
        { "enableAmount", "可用数量", SWAP_INT},
        { "lastPrice", "最新价", SWAP_DOUBLE},
        { "marketValue", "持仓市值(全价)", SWAP_DOUBLE},
        { "costBalance", "当前成本", SWAP_DOUBLE},
        { "costPrice", "成本价", SWAP_DOUBLE},
        { "income", "浮动盈亏", SWAP_DOUBLE},
    };

    static const FieldMatchUnit FIELD_PAIR_PLEDGE[] = 
    {
        { "accountID", "资金账号", SWAP_STR},
        { "exchangeType", "交易类别", SWAP_STR},
        { "stockAccount", "股东号", SWAP_STR},
        { "stockCode", "债券代码", SWAP_STR},
        { "standardCode", "标准券代码", SWAP_STR},
        { "pledgeNum", "质押数量", SWAP_INT},
    };

    static const FieldMatchUnit FIELD_PAIR_SMT_FUND[] = 
    {
        { "accountID", "资金账号", SWAP_STR},
        { "perAssurescaleValue", "个人维持担保比例", SWAP_DOUBLE_PRE},
        { "enableBailBalance", "可用保证金", SWAP_DOUBLE},
        { "finMaxQuota", "融资授信额度", SWAP_DOUBLE},
        { "enableBalance", "可用金额", SWAP_DOUBLE},
        { "sloMaxQuota", "融券授信额度", SWAP_DOUBLE},
        { "underlyMarketValue", "标的证券市值", SWAP_DOUBLE},
        { "fetchBalance", "可取金额", SWAP_DOUBLE},
        { "marketValue", "总市值", SWAP_DOUBLE},
        { "assetBalance", "总资产", SWAP_DOUBLE},
        { "debt", "总负债", SWAP_DOUBLE},
    };

    static const FieldMatchUnit FIELD_PAIR_STK_CMP[] = 
    {
        { "accountID", "资金账号", SWAP_STR },
        { "exchangeName", "交易所名称", SWAP_STR },
        { "stockCode", "证券代码", SWAP_STR },
        { "stockName", "股票名称", SWAP_STR },
        { "compactId", "合约编号", SWAP_STR },
        { "entrustNo", "委托编号", SWAP_STR },
        { "openDate", "合约开仓日期", SWAP_INT },
        { "crdtRatio", "融资融券保证金比例", SWAP_DOUBLE },
        { "entrustPrice", "委托价格", SWAP_DOUBLE },
        { "entrustAmount", "委托数量", SWAP_DOUBLE },
        { "businessAmount", "合约开仓数量", SWAP_DOUBLE },
        { "businessBalance", "合约开仓金额", SWAP_DOUBLE },
        { "businessFare", "合约开仓费用", SWAP_DOUBLE },
        { "compactTypeTmp", "合约类型", SWAP_STR },
        { "compactStatusTmp", "合约状态", SWAP_STR },
        { "realCompactBalance", "未还合约金额", SWAP_DOUBLE },
        { "realCompactAmount", "未还合约数量", SWAP_DOUBLE },
        { "realCompactFare", "未还合约费用", SWAP_DOUBLE },
        { "realCompactInterest", "未还合约利息", SWAP_DOUBLE },
        { "repaidInterest", "已还利息", SWAP_DOUBLE },
        { "repaidAmount", "已还数量", SWAP_DOUBLE },
        { "repaidBalance", "已还金额", SWAP_DOUBLE },
        { "compactInterest", "合约总利息", SWAP_DOUBLE },
        { "usedBailBalance", "占用保证金", SWAP_DOUBLE },
        { "yearRate", "合约年利率", SWAP_DOUBLE },
        { "retEndDate", "归还截止日", SWAP_INT },
        { "dateClear", "了结日期", SWAP_INT },
    };

    static const FieldMatchUnit FIELD_PAIR_UNDERLYING[] = 
    {
        { "accountID", "资金账号", SWAP_STR},
        { "exchangeType", "交易所", SWAP_STR},
        { "stockCode", "证券代码", SWAP_STR },
        { "stockName", "股票名称", SWAP_STR },
        { "finStatusTmp", "融资状态", SWAP_STR },
        { "sloStatusTmp", "融券状态", SWAP_STR },
        { "sloRatio", "融券保证金比例", SWAP_DOUBLE },
        { "enableAmount", "融券可融数量", SWAP_DOUBLE },
        { "finRatio", "融资保证金比例", SWAP_DOUBLE },
        { "assureRatio", "担保品折算比例", SWAP_DOUBLE },
    };

    static const FieldMatchUnit FIELD_PAIR_INTRATE[] = 
    {
        // 一条数据对应4条数据，走特殊处理
        { "accountID", "资金账号", SWAP_STR},
    };

    // ---------------------------------------------------------------------

    static const FuncMatchUnit ALL_FUNC_MATCH_UNITS[] = 
    {
        { XT_DATA_TYPE_LOGIN, FIELD_PAIR_LOGIN, ARRAYLEN(FIELD_PAIR_LOGIN), "_fund_hs.csv"},
        { XT_DATA_TYPE_FUND, FIELD_PAIR_FUND, ARRAYLEN(FIELD_PAIR_FUND), "_fund_hs.csv"},
        { XT_DATA_TYPE_POSITION, FIELD_PAIR_POSITION, ARRAYLEN(FIELD_PAIR_POSITION), "_position_hs.csv"},
        { XT_DATA_TYPE_ORDER, FIELD_PAIR_ORDER, ARRAYLEN(FIELD_PAIR_ORDER), "_order_hs.csv"},
        { XT_DATA_TYPE_BUSINESS, FIELD_PAIR_BIZ, ARRAYLEN(FIELD_PAIR_BIZ), "_dealdetail_hs.csv"},
        //{ XT_DATA_TYPE_PLEDGE, FIELD_PAIR_PLEDGE, ARRAYLEN(FIELD_PAIR_PLEDGE), "_pledge_hs.CSV"},
        { XT_DATA_TYPE_SMTFUND, FIELD_PAIR_SMT_FUND, ARRAYLEN(FIELD_PAIR_SMT_FUND), "_fund_hs.csv"},
//         { XT_DATA_TYPE_SMTPOSITIONCOM, FIELD_PAIR_STK_CMP, ARRAYLEN(FIELD_PAIR_STK_CMP), "_smtpositioncompacts_hs.CSV"},
//         { XT_DATA_TYPE_SMTUNDERLYINGSEC, FIELD_PAIR_UNDERLYING, ARRAYLEN(FIELD_PAIR_UNDERLYING), "_smtstksubjects_hs.CSV"},
//         { XT_DATA_TYPE_SMTINTERESTRATE, FIELD_PAIR_INTRATE, ARRAYLEN(FIELD_PAIR_INTRATE), "_smtstksubjects_hs.CSV"},
    };
}

#endif