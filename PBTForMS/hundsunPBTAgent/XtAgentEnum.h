#ifndef Enums_XtClientBroker_H_
#define Enums_XtClientBroker_H_

namespace agent
{
    enum QUERY_DATA_TYPE
    {
        XT_DATA_TYPE_LOGIN = 1,
        XT_DATA_TYPE_FUND = 3,
        XT_DATA_TYPE_POSITION = 4,
        XT_DATA_TYPE_ORDER = 5,
        XT_DATA_TYPE_BUSINESS = 6,
        XT_DATA_TYPE_PLEDGE = 7,
        XT_DATA_TYPE_SMTFUND = 8,
        XT_DATA_TYPE_SMTPOSITIONCOM = 9,
        XT_DATA_TYPE_SMTUNDERLYINGSEC = 10,
        XT_DATA_TYPE_SMTINTERESTRATE = 11,
    };

    enum ACCOUNT_STATUS
    {
        ACCOUNT_LOGIN_SUCCESS,
        ACCOUNT_LOGIN_FAILURE,
    };

    // 融资融券利率费率类型 1-融资利率，2-融券费率，3-融资罚息费率，4-融券罚息费率

    enum
    {
        RZRQ_FEE_RATE_TYPE_RZ       = '1',
        RZRQ_FEE_RATE_TYPE_RQ       = '2',
        RZRQ_FEE_RATE_TYPE_RZFX     = '3',
        RZRQ_FEE_RATE_TYPE_RQFX     = '4',
    };

    //转换方式
    enum
    {
        SWAP_STR = '0',             //str to string
        SWAP_INT = '1',             //str to int
        SWAP_DOUBLE = '2',          //str to double
        SWAP_DOUBLE_PRE = '3',      //str to double(含%的str)
        SWAP_TIME       = '4',      //str to int
    };
}

#endif /* Enums_XtClientBroker_H_ */