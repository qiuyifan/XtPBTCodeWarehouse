#ifndef XT_AGENT_MATCH_DEF_H
#define XT_AGENT_MATCH_DEF_H
#include "XtAgentEnum.h"

#define ARRAYLEN(x) ((sizeof((x)) / (sizeof(((x)[0])))))
namespace agent
{
    struct FieldMatchUnit
    {
        string dst;     // Ŀ���ֶ�
        string src;     // Դ�ֶ�
        char method;    // ֵת����ʽ
    };

    struct FuncMatchUnit
    {
        int funcNo;                         // ���ܺ�
        const FieldMatchUnit* coverFields;  // ת����
        int coverCnt;                       // ת������
        string fieldSuffix;                 // �ļ���׺
    };

    // ---------------------------------------------------------------------

    static const FieldMatchUnit FIELD_PAIR_LOGIN[] = 
    {
        { "accountID", "", SWAP_STR},
        { "accountName", "��Ԫ����", SWAP_STR},
    };

    static const FieldMatchUnit FIELD_PAIR_FUND[] = 
    {
        { "accountID", "", SWAP_STR},
        { "enableBalance", "T+0����", SWAP_DOUBLE},
        { "fetchBalance", "��ǰ�ֽ����", SWAP_DOUBLE},
        { "marketValue", "��Ʊ�ʲ�", SWAP_DOUBLE},
        { "assetBalance", "��Ԫ��ֵ", SWAP_DOUBLE},
    };

    static const FieldMatchUnit FIELD_PAIR_ORDER[] = 
    {
        { "accountID", "", SWAP_STR},
        { "entrustNo", "ί�����", SWAP_STR},
        { "exchangeName", "�����г�", SWAP_STR},
        { "stockCode", "֤ȯ����", SWAP_STR},
        { "stockName", "֤ȯ����", SWAP_STR},
        { "entrustDate", "ҵ������", SWAP_TIME},
        { "entrustTime", "ί��ʱ��", SWAP_TIME},
        { "bsflage", "ί�з���", SWAP_STR},
        { "entrustStatusName", "ί��״̬", SWAP_STR},
        { "entrustPrice", "ί�м۸�", SWAP_DOUBLE},
        { "entrustAmount", "ί������", SWAP_INT},
        { "bizAmount", "�ɽ�����", SWAP_INT},
        { "cancelAmount", "��������", SWAP_INT},
        { "bizPrice", "�ɽ�����", SWAP_DOUBLE},
        { "cancelInfo", "�ϵ�ԭ��", SWAP_STR},
    };

    static const FieldMatchUnit FIELD_PAIR_BIZ[] = 
    {
        { "accountID", "", SWAP_STR},
        { "bizDate", "ҵ������", SWAP_TIME},
        { "bizTime", "�ɽ�ʱ��", SWAP_TIME},
        { "entrustNo", "ί�����", SWAP_STR},
        { "exchangeName", "", SWAP_STR},
        { "stockCode", "֤ȯ����", SWAP_STR},
        { "stockName", "֤ȯ����", SWAP_STR},
        { "bizNo", "�ɽ����", SWAP_STR},
        { "bsflage", "ί�з���", SWAP_STR},
        { "bizAmount", "�ɽ�����", SWAP_INT},
        { "bizBalance", "�ɽ����", SWAP_DOUBLE},
        { "bizPrice", "�ɽ�����", SWAP_DOUBLE},
    };

    static const FieldMatchUnit FIELD_PAIR_POSITION[] = 
    {
        { "accountID", "", SWAP_STR},
        { "exchangeName", "�����г�", SWAP_STR},
        { "stockCode", "֤ȯ����", SWAP_STR},
        { "stockName", "֤ȯ����", SWAP_STR},
        { "stockAccount", "�ɶ�", SWAP_STR},
        { "totalAmt", "�ֲ�����", SWAP_INT},
        { "enableAmount", "��������", SWAP_INT},
        { "lastPrice", "���¼�", SWAP_DOUBLE},
        { "marketValue", "�ֲ���ֵ(ȫ��)", SWAP_DOUBLE},
        { "costBalance", "��ǰ�ɱ�", SWAP_DOUBLE},
        { "costPrice", "�ɱ���", SWAP_DOUBLE},
        { "income", "����ӯ��", SWAP_DOUBLE},
    };

    static const FieldMatchUnit FIELD_PAIR_PLEDGE[] = 
    {
        { "accountID", "�ʽ��˺�", SWAP_STR},
        { "exchangeType", "�������", SWAP_STR},
        { "stockAccount", "�ɶ���", SWAP_STR},
        { "stockCode", "ծȯ����", SWAP_STR},
        { "standardCode", "��׼ȯ����", SWAP_STR},
        { "pledgeNum", "��Ѻ����", SWAP_INT},
    };

    static const FieldMatchUnit FIELD_PAIR_SMT_FUND[] = 
    {
        { "accountID", "�ʽ��˺�", SWAP_STR},
        { "perAssurescaleValue", "����ά�ֵ�������", SWAP_DOUBLE_PRE},
        { "enableBailBalance", "���ñ�֤��", SWAP_DOUBLE},
        { "finMaxQuota", "�������Ŷ��", SWAP_DOUBLE},
        { "enableBalance", "���ý��", SWAP_DOUBLE},
        { "sloMaxQuota", "��ȯ���Ŷ��", SWAP_DOUBLE},
        { "underlyMarketValue", "���֤ȯ��ֵ", SWAP_DOUBLE},
        { "fetchBalance", "��ȡ���", SWAP_DOUBLE},
        { "marketValue", "����ֵ", SWAP_DOUBLE},
        { "assetBalance", "���ʲ�", SWAP_DOUBLE},
        { "debt", "�ܸ�ծ", SWAP_DOUBLE},
    };

    static const FieldMatchUnit FIELD_PAIR_STK_CMP[] = 
    {
        { "accountID", "�ʽ��˺�", SWAP_STR },
        { "exchangeName", "����������", SWAP_STR },
        { "stockCode", "֤ȯ����", SWAP_STR },
        { "stockName", "��Ʊ����", SWAP_STR },
        { "compactId", "��Լ���", SWAP_STR },
        { "entrustNo", "ί�б��", SWAP_STR },
        { "openDate", "��Լ��������", SWAP_INT },
        { "crdtRatio", "������ȯ��֤�����", SWAP_DOUBLE },
        { "entrustPrice", "ί�м۸�", SWAP_DOUBLE },
        { "entrustAmount", "ί������", SWAP_DOUBLE },
        { "businessAmount", "��Լ��������", SWAP_DOUBLE },
        { "businessBalance", "��Լ���ֽ��", SWAP_DOUBLE },
        { "businessFare", "��Լ���ַ���", SWAP_DOUBLE },
        { "compactTypeTmp", "��Լ����", SWAP_STR },
        { "compactStatusTmp", "��Լ״̬", SWAP_STR },
        { "realCompactBalance", "δ����Լ���", SWAP_DOUBLE },
        { "realCompactAmount", "δ����Լ����", SWAP_DOUBLE },
        { "realCompactFare", "δ����Լ����", SWAP_DOUBLE },
        { "realCompactInterest", "δ����Լ��Ϣ", SWAP_DOUBLE },
        { "repaidInterest", "�ѻ���Ϣ", SWAP_DOUBLE },
        { "repaidAmount", "�ѻ�����", SWAP_DOUBLE },
        { "repaidBalance", "�ѻ����", SWAP_DOUBLE },
        { "compactInterest", "��Լ����Ϣ", SWAP_DOUBLE },
        { "usedBailBalance", "ռ�ñ�֤��", SWAP_DOUBLE },
        { "yearRate", "��Լ������", SWAP_DOUBLE },
        { "retEndDate", "�黹��ֹ��", SWAP_INT },
        { "dateClear", "�˽�����", SWAP_INT },
    };

    static const FieldMatchUnit FIELD_PAIR_UNDERLYING[] = 
    {
        { "accountID", "�ʽ��˺�", SWAP_STR},
        { "exchangeType", "������", SWAP_STR},
        { "stockCode", "֤ȯ����", SWAP_STR },
        { "stockName", "��Ʊ����", SWAP_STR },
        { "finStatusTmp", "����״̬", SWAP_STR },
        { "sloStatusTmp", "��ȯ״̬", SWAP_STR },
        { "sloRatio", "��ȯ��֤�����", SWAP_DOUBLE },
        { "enableAmount", "��ȯ��������", SWAP_DOUBLE },
        { "finRatio", "���ʱ�֤�����", SWAP_DOUBLE },
        { "assureRatio", "����Ʒ�������", SWAP_DOUBLE },
    };

    static const FieldMatchUnit FIELD_PAIR_INTRATE[] = 
    {
        // һ�����ݶ�Ӧ4�����ݣ������⴦��
        { "accountID", "�ʽ��˺�", SWAP_STR},
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