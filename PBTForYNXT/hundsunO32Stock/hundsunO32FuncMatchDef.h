﻿#ifndef __HUNDSUNO32_FUNC_MATCH_DEF_H__
#define __HUNDSUNO32_FUNC_MATCH_DEF_H__

#include "func_matcher.h"

namespace broker
{
    namespace stock
    {

#define REQ_FIELDS_COMMON()\
        { "accountID", "fundAccount"},\
        { "passWord", "" },\
        { "platformID", "" },\
        { "brokerID", ""},\
        { "brokerType", ""},\

        // ---------------------------------------------------------------------
        // login

        static const FieldMatchUnit FIELD_PAIR_LOGIN_REQ[] = 
        {
            { "accountID", "userName"},
            { "passWord", "" },
            { "platformID", "" },
            { "brokerID", ""},
            { "brokerType", ""},
        };

        static const FieldMatchUnit FIELD_PAIR_LOGIN_RESP[] = 
        {
            { "branchNo", "" },
            { "clientId", "" },
            { "clientName", "基金名称" },
            { "fundAccount", "" },
        };

        // queryFund
        static const FieldMatchUnit FIELD_PAIR_QRY_FUND_REQ[] = 
        {
            REQ_FIELDS_COMMON()
        };

        static const FieldMatchUnit FIELD_PAIR_QRY_FUND_RESP[] = 
        {
            { "moneyType", "" },
            { "currentBalance", "" },
            { "enableBalance", "T+0交易可用" },
            { "fetchBalance", "T+1交易可用" },
            { "interest", "" },
            { "assetBalance", "证券总市值(扣期货)" },
            { "marketValue", "总资产" },
            { "debt", ""},// 正回购质押产生负债 其他负债请不要匹配
        };

        // queryPosition

        static const FieldMatchUnit FIELD_PAIR_QRY_POS_REQ[] = 
        {
            REQ_FIELDS_COMMON()
        };

        static const FieldMatchUnit FIELD_PAIR_QRY_POS_RESP[] = 
        {
            { "exchangeType", "" },
            { "stockCode", "证券代码" },
            { "stockName", "证券名称" },
            { "totalAmt", "持仓" }, // 暂且double
            { "enableAmount", "可用数量" }, // 暂且double
            { "lastPrice", "最新价" },
            { "marketValue", "市值" },
            { "costBalance", "当前成本" },
            { "costPrice", "成本价" },
            { "income", "累计盈亏" },
            { "incomeRate", "" },
            { "handFlag", "" },
            { "stockAccount", "股东代码" },
            { "bsOnTheWayVol", "" },
            { "prEnableVol", "" },
        };

        // queryOrder

        static const FieldMatchUnit FIELD_PAIR_QRY_ORDER_REQ[] = 
        {
            REQ_FIELDS_COMMON()
        };

        static const FieldMatchUnit FIELD_PAIR_QRY_ORDER_RESP[] = 
        {
            { "entrustNo", "委托序号" },
            { "exchangeType", "" },
            { "exchangeName", "交易市场" },
            { "stockAccount", "" },
            { "stockCode", "证券代码" },
            { "stockName", "证券名称" },
            { "entrustBS", "" },
            { "entrustBSName", "" },
            { "entrustPrice", "委托价格" },
            { "entrustAmount", "委托数量" },
            { "bizAmount", "累计成交数量" }, // 累积成交量
            { "cancelAmount", "撤单数量" },
            { "bizPrice", "" },
            { "bizBalance", "成交金额" }, // add @ 20140731
            { "entrustDate", "" }, // 格式为 YYYYMMDD
            { "entrustTime", "" }, // 格式为 HHMMSS
            { "entrustType", "" },
            { "entrustProp", "" }, // 某些平台查询委托无委托属性返回，使用默认值
            { "entrustPropName", "" },
            { "entrustStatus", "" },
            { "entrustStatusName", "" },
            { "cancelFlag", "" },   // 标识委托是正常买卖委托还是撤单
            { "cancelInfo", "" },
            { "positionStr", "" },
            { "orderRef", "" },
            { "tradeName","" },// 信用字段
        };

        // queryBusiness

        static const FieldMatchUnit FIELD_PAIR_QRY_BUSINESS_REQ[] = 
        {
            REQ_FIELDS_COMMON()
        };

        static const FieldMatchUnit FIELD_PAIR_QRY_BUSINESS_RESP[] = 
        {
            { "bizDate", "日期" },
            { "bizTime", "" },
            { "entrustNo", "委托序号" },
            { "exchangeType", "" },
            { "stockCode", "证券代码" },
            { "stockName", "证券名称" },
            { "entrustBS", "" },
            { "entrustBSName", "" },
            { "bizAmount", "成交数量" }, // 暂且为double，单笔成交的量
            { "bizBalance", "成交金额" }, // 暂且为double
            { "bizPrice", "成交价格" },
            { "stockAccount", "" },
            { "bizNo", "成交编号" },
            { "cancelFlag", "" },   // 标识委托是正常买卖委托还是撤单
            { "positionStr", "" },
            { "orderRef", "" },
            { "tradeName","" },// 信用字段
        };



        // ---------------------------------------------------------------------
        
        static const FuncMatchUnit ALL_FUNC_MATCH_UNITS[] = 
        {
            { "login", 0, FIELD_PAIR_LOGIN_REQ, ARRAYLEN(FIELD_PAIR_LOGIN_REQ), FIELD_PAIR_LOGIN_RESP, ARRAYLEN(FIELD_PAIR_LOGIN_RESP) },
            { "queryFund", 0, FIELD_PAIR_QRY_FUND_REQ, ARRAYLEN(FIELD_PAIR_QRY_FUND_REQ), FIELD_PAIR_QRY_FUND_RESP, ARRAYLEN(FIELD_PAIR_QRY_FUND_RESP) },
            { "queryPosition", 3, FIELD_PAIR_QRY_POS_REQ, ARRAYLEN(FIELD_PAIR_QRY_POS_REQ), FIELD_PAIR_QRY_POS_RESP, ARRAYLEN(FIELD_PAIR_QRY_POS_RESP) },
            { "queryOrder", 1, FIELD_PAIR_QRY_ORDER_REQ, ARRAYLEN(FIELD_PAIR_QRY_ORDER_REQ), FIELD_PAIR_QRY_ORDER_RESP, ARRAYLEN(FIELD_PAIR_QRY_ORDER_RESP) },
            { "queryBusiness", 2, FIELD_PAIR_QRY_BUSINESS_REQ, ARRAYLEN(FIELD_PAIR_QRY_BUSINESS_REQ), FIELD_PAIR_QRY_BUSINESS_RESP, ARRAYLEN(FIELD_PAIR_QRY_BUSINESS_RESP) },
            { "queryBusinessInc", 2, FIELD_PAIR_QRY_BUSINESS_REQ, ARRAYLEN(FIELD_PAIR_QRY_BUSINESS_REQ), FIELD_PAIR_QRY_BUSINESS_RESP, ARRAYLEN(FIELD_PAIR_QRY_BUSINESS_RESP) },
        };
    }
}

#endif