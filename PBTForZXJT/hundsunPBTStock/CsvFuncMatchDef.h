#ifndef __CSV_FUNC_MATCH_DEF_H__
#define __CSV_FUNC_MATCH_DEF_H__

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
            { "clientName", "accountName" },
            { "fundAccount", "accountID" },
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
            { "enableBalance", "enableBalance" },
            { "fetchBalance", "fetchBalance" },
            { "interest", "" },
            { "assetBalance", "assetBalance" },
            { "marketValue", "marketValue" },
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
            { "stockCode", "stockCode" },
            { "stockName", "stockName" },
            { "totalAmt", "totalAmt" }, // 暂且double
            { "enableAmount", "enableAmount" }, // 暂且double
            { "lastPrice", "lastPrice" },
            { "marketValue", "marketValue" },
            { "costBalance", "costBalance" },
            { "costPrice", "costPrice" },
            { "income", "income" },
            { "incomeRate", "" },
            { "handFlag", "" },
            { "stockAccount", "stockAccount" },
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
            { "entrustNo", "entrustNo" },
            { "exchangeType", "" },
            { "exchangeName", "exchangeName" },
            { "stockAccount", "" },
            { "stockCode", "stockCode" },
            { "stockName", "stockName" },
            { "entrustBS", "" },
            { "entrustBSName", "" },
            { "entrustPrice", "entrustPrice" },
            { "entrustAmount", "entrustAmount" },
            { "bizAmount", "bizAmount" }, // 累积成交量
            { "cancelAmount", "cancelAmount" },
            { "bizPrice", "bizPrice" },
            { "bizBalance", "" }, // add @ 20140731
            { "entrustDate", "entrustDate" }, // 格式为 YYYYMMDD
            { "entrustTime", "" }, // 格式为 HHMMSS
            { "entrustType", "" },
            { "entrustProp", "" }, // 某些平台查询委托无委托属性返回，使用默认值
            { "entrustPropName", "" },
            { "entrustStatus", "" },
            { "entrustStatusName", "" },
            { "cancelFlag", "" },   // 标识委托是正常买卖委托还是撤单
            { "cancelInfo", "cancelInfo" },
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
            { "bizDate", "bizDate" },
            { "bizTime", "" },
            { "entrustNo", "entrustNo" },
            { "exchangeType", "" },
            { "stockCode", "stockCode" },
            { "stockName", "stockName" },
            { "entrustBS", "" },
            { "entrustBSName", "" },
            { "bizAmount", "bizAmount" }, // 暂且为double，单笔成交的量
            { "bizBalance", "bizBalance" }, // 暂且为double
            { "bizPrice", "bizPrice" },
            { "stockAccount", "" },
            { "bizNo", "bizNo" },
            { "cancelFlag", "" },   // 标识委托是正常买卖委托还是撤单
            { "positionStr", "" },
            { "orderRef", "" },
            { "tradeName","" },// 信用字段
        };

        // queryPledgeInfo

        static const FieldMatchUnit FIELD_PAIR_QRY_PLEDGE_REQ[] = 
        {
            REQ_FIELDS_COMMON()
        };

        static const FieldMatchUnit FIELD_PAIR_QRY_PLEDGE_RESP[] = 
        {
            { "exchangeType", "exchangeType", BY_SWAP },
            { "stockAccount", "stockAccount" },
            { "stockCode", "stockCode" },
            { "standard", "standardCode" },
            { "pledgeNum", "pledgeNum" },
        };

        // smtQueryFund

        static const FieldMatchUnit FIELD_PAIR_SMT_QUERYFUND_REQ[] = 
        {
            REQ_FIELDS_COMMON()
        };

        static const FieldMatchUnit FIELD_PAIR_SMT_QUERYFUND_RESP[] = 
        {
            { "fundAsset", "assetBalance" },
            { "marketValue", "marketValue"},
            { "assureAsset", "" },
            { "totalDebit", "debt" },
            { "fetchBalance", "fetchBalance" },
            { "perAssurescaleValue", "perAssurescaleValue" },
            { "enableBailBalance", "enableBailBalance" },
            { "usedBailBalance", "" },
            { "assureEnbuyBalance", "" },
            { "finEnbuyBalance", "" },
            { "sloEnrepaidBalance", "" },
            { "finEnrepaidBalance", "" },
            { "finMaxQuota", "finMaxQuota" },
            { "finEnableQuota", "" },
            { "finUsedQuota", "" },
            { "finUsedBail", "" },
            { "finCompactBalance", "" },
            { "finCompactFare", "" },
            { "finCompactInterest", "" },
            { "finMarketValue", "" },
            { "finIncome", "" },
            { "sloMaxQuota", "sloMaxQuota" },
            { "sloEnableQuota", "" },
            { "sloUsedQuota", "" },
            { "sloUsedBail", "" },
            { "sloCompactBalance", "" },
            { "sloCompactFare", "" },
            { "sloCompactInterest", "" },
            { "sloMarketValue", "" },
            { "sloIncome", "" },
            { "otherFare", "" },
            { "underlyMarketValue", "underlyMarketValue" },
        };

        // smtQueryPosition

        static const FieldMatchUnit FIELD_PAIR_SMT_QRY_POS_REQ[] = 
        {
            REQ_FIELDS_COMMON()
        };

        static const FieldMatchUnit FIELD_PAIR_SMT_QRY_POS_RESP[] = 
        {
            { "fundAccount", "accountID" },
            { "exchangeType", "" },
            { "stockAccount", "stockAccount" },
            { "stockCode", "stockCode" },
            { "stockName", "stockName" },
            { "currentAmount", "totalAmt" },
            { "holdAmount", "totalAmt", },
            { "enableAmount", "enableAmount"},
            { "lastPrice", "lastPrice" },
            { "costPrice", "costPrice" },
            { "incomeBalance", "income" },
            { "handFlag", "" },
            { "marketValue", "marketValue" },
            { "avBuyPrice", ""},
            { "avIncomeBalance", ""},
            { "costBalance", "costBalance" },
            { "uncomeBuyAmount", "" },
            { "uncomeSellAmount", "" },
            { "entrustSellAmount", "" },
            { "realBuyAmount", "" },
            { "realSellAmount", "" },
            { "positionStr", "" },
        };

        // smtQueryPositionCompacts

        static const FieldMatchUnit FIELD_PAIR_SMT_QURY_COMPACTS_REQ[] = 
        {
            REQ_FIELDS_COMMON()
        };

        static const FieldMatchUnit FIELD_PAIR_SMT_QURY_COMPACTS_RESP[] = 
        {
            { "openDate", "openDate" },
            { "compactId", "compactId" },
            { "fundAccount", "accountID" },
            { "moneyType", "" },
            { "exchangeType", "" },
            { "stockAccount", "" },
            { "stockCode", "stockCode" },
            { "crdtRatio", "crdtRatio" },
            { "entrustNo", "entrustNo" },
            { "entrustPrice", "entrustPrice" },
            { "entrustAmount", "entrustAmount" },
            { "businessAmount", "businessAmount" },
            { "businessBalance", "businessBalance" },
            { "businessFare", "businessFare" },
            { "compactType", "" },
            { "compactStatus", "" },
            { "realCompactBalance", "realCompactBalance" },
            { "realCompactAmount", "realCompactAmount" },
            { "realCompactFare", "realCompactFare" },
            { "realCompactInterest", "realCompactInterest" },
            { "repaidInterest", "repaidInterest" },
            { "repaidAmount", "repaidAmount" },
            { "repaidBalance", "repaidBalance" },
            { "compactInterest", "compactInterest" },
            { "usedBailBalance", "usedBailBalance" },
            { "yearRate", "yearRate" },
            { "retEndDate", "retEndDate" },
            { "dateClear", "dateClear" },
            { "positionStr", "" },
        };

        // smtQueryUnderlyingSecurities

        static const FieldMatchUnit FIELD_PAIR_SMT_QURY_UNDERLYINGS_REQ[] = 
        {
            REQ_FIELDS_COMMON()
        };

        static const FieldMatchUnit FIELD_PAIR_SMT_QURY_UNDERLYINGS_RESP[] = 
        {
            { "exchangeType", "exchangeType", BY_SWAP },
            { "stockCode", "stockCode" },
            { "stockName", "stockName" },
            { "assureRatio", "assureRatio" },
            { "finRatio", "finRatio" },
            { "finStatus", "" },
            { "sloRatio", "sloRatio" },
            { "sloStatus", "" },
            { "positionStr", "" },
        };

        // smtQuerySellSecutites

        static const FieldMatchUnit FIELD_PAIR_SMT_QURY_SELLSEU_REQ[] = 
        {
            REQ_FIELDS_COMMON()
        };

        static const FieldMatchUnit FIELD_PAIR_SMT_QURY_SELLSEU_RESP[] = 
        {
            { "exchangeType", "exchangeType", BY_SWAP },
            { "stockCode", "stockCode" },
            { "stockName", "stockName" },
            { "sloRatio", "sloRatio" },
            { "sloStatus", "" },
            { "enableAmount", "enableAmount" },
            { "positionStr", "" },
        };

        // smtQueryInterestRate

        static const FieldMatchUnit FIELD_PAIR_SMT_QURY_INTRATE_REQ[] = 
        {
            REQ_FIELDS_COMMON()
        };

        static const FieldMatchUnit FIELD_PAIR_SMT_QURY_INTRATE_RESP[] = 
        {
            { "crdtrateKind", "crdtrateKind" },
            { "stockCode", "stockCode" },
            { "rateDays", "rateDays" },
            { "yearRate", "yearRate" },
        };

        // ---------------------------------------------------------------------
        
        static const FuncMatchUnit ALL_FUNC_MATCH_UNITS[] = 
        {
            { "login", 1, FIELD_PAIR_LOGIN_REQ, ARRAYLEN(FIELD_PAIR_LOGIN_REQ), FIELD_PAIR_LOGIN_RESP, ARRAYLEN(FIELD_PAIR_LOGIN_RESP) },
            { "queryFund", 3, FIELD_PAIR_QRY_FUND_REQ, ARRAYLEN(FIELD_PAIR_QRY_FUND_REQ), FIELD_PAIR_QRY_FUND_RESP, ARRAYLEN(FIELD_PAIR_QRY_FUND_RESP) },
            { "queryPosition", 4, FIELD_PAIR_QRY_POS_REQ, ARRAYLEN(FIELD_PAIR_QRY_POS_REQ), FIELD_PAIR_QRY_POS_RESP, ARRAYLEN(FIELD_PAIR_QRY_POS_RESP) },
            { "queryOrder", 5, FIELD_PAIR_QRY_ORDER_REQ, ARRAYLEN(FIELD_PAIR_QRY_ORDER_REQ), FIELD_PAIR_QRY_ORDER_RESP, ARRAYLEN(FIELD_PAIR_QRY_ORDER_RESP) },
            { "queryBusiness", 6, FIELD_PAIR_QRY_BUSINESS_REQ, ARRAYLEN(FIELD_PAIR_QRY_BUSINESS_REQ), FIELD_PAIR_QRY_BUSINESS_RESP, ARRAYLEN(FIELD_PAIR_QRY_BUSINESS_RESP) },
            { "queryBusinessInc", 6, FIELD_PAIR_QRY_BUSINESS_REQ, ARRAYLEN(FIELD_PAIR_QRY_BUSINESS_REQ), FIELD_PAIR_QRY_BUSINESS_RESP, ARRAYLEN(FIELD_PAIR_QRY_BUSINESS_RESP) },
            { "queryPledge", 7, FIELD_PAIR_QRY_PLEDGE_REQ, ARRAYLEN(FIELD_PAIR_QRY_PLEDGE_REQ), FIELD_PAIR_QRY_PLEDGE_RESP, ARRAYLEN(FIELD_PAIR_QRY_PLEDGE_RESP) },

            // 信用接口
            { "smtLogin", 1, FIELD_PAIR_LOGIN_REQ, ARRAYLEN(FIELD_PAIR_LOGIN_REQ), FIELD_PAIR_LOGIN_RESP, ARRAYLEN(FIELD_PAIR_LOGIN_RESP) },
            { "smtQueryFund", 8, FIELD_PAIR_SMT_QUERYFUND_REQ, ARRAYLEN(FIELD_PAIR_SMT_QUERYFUND_REQ), FIELD_PAIR_SMT_QUERYFUND_RESP, ARRAYLEN(FIELD_PAIR_SMT_QUERYFUND_RESP) },
            { "smtQueryPosition", 4, FIELD_PAIR_SMT_QRY_POS_REQ, ARRAYLEN(FIELD_PAIR_SMT_QRY_POS_REQ), FIELD_PAIR_SMT_QRY_POS_RESP, ARRAYLEN(FIELD_PAIR_SMT_QRY_POS_RESP) },
            { "smtQueryOrder", 5, FIELD_PAIR_QRY_ORDER_REQ, ARRAYLEN(FIELD_PAIR_QRY_ORDER_REQ), FIELD_PAIR_QRY_ORDER_RESP, ARRAYLEN(FIELD_PAIR_QRY_ORDER_RESP) },
            { "smtQueryBusiness", 6, FIELD_PAIR_QRY_BUSINESS_REQ, ARRAYLEN(FIELD_PAIR_QRY_BUSINESS_REQ), FIELD_PAIR_QRY_BUSINESS_RESP, ARRAYLEN(FIELD_PAIR_QRY_BUSINESS_RESP) },
            { "smtQueryPositionCompacts", 9, FIELD_PAIR_SMT_QURY_COMPACTS_REQ, ARRAYLEN(FIELD_PAIR_SMT_QURY_COMPACTS_REQ), FIELD_PAIR_SMT_QURY_COMPACTS_RESP, ARRAYLEN(FIELD_PAIR_SMT_QURY_COMPACTS_RESP) },
            { "smtQueryUnderlyingSecurities", 10, FIELD_PAIR_SMT_QURY_UNDERLYINGS_REQ, ARRAYLEN(FIELD_PAIR_SMT_QURY_UNDERLYINGS_REQ), FIELD_PAIR_SMT_QURY_UNDERLYINGS_RESP, ARRAYLEN(FIELD_PAIR_SMT_QURY_UNDERLYINGS_RESP) },
            { "smtQuerySellSecutites", 10, FIELD_PAIR_SMT_QURY_SELLSEU_REQ, ARRAYLEN(FIELD_PAIR_SMT_QURY_SELLSEU_REQ), FIELD_PAIR_SMT_QURY_SELLSEU_RESP, ARRAYLEN(FIELD_PAIR_SMT_QURY_SELLSEU_RESP) },
            { "smtQueryInterestRate", 11, FIELD_PAIR_SMT_QURY_INTRATE_REQ, ARRAYLEN(FIELD_PAIR_SMT_QURY_INTRATE_REQ), FIELD_PAIR_SMT_QURY_INTRATE_RESP, ARRAYLEN(FIELD_PAIR_SMT_QURY_INTRATE_RESP) },
        };
    }
}

#endif