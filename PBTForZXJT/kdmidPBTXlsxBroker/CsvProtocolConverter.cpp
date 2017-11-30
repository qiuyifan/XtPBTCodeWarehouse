#include "common/Stdafx.h"
#include "utils/TimeTool.h"
#include "utils/SysInfo.h"
#include "CsvProtocolDef.h"
#include "CsvPacket.h"
#include "CsvProtocol.h"
#include "CsvFuncMatchDef.h"
#include "CsvValueSwapDef.h"
#include "CsvProtocolConverter.h"
#include "CsvSession.h"

namespace broker
{
    namespace stock
    {
        CsvProtocolConverter::CsvProtocolConverter() : StockProtocolConverter()
        {
            m_toolFunc = CsvToolFuncPtr(new CsvToolFunc());
        }

        CsvProtocolConverter::~CsvProtocolConverter()
        {

        }

        utils::SwapMapPtr CsvProtocolConverter::newSwapMap()
        {
            return utils::SwapMapPtr(new utils::SwapMap(SWAP_TABLES, ARRAYLEN(SWAP_TABLES)));
        }

        FuncMatcherPtr CsvProtocolConverter::newFuncMatcher()
        {
            return FuncMatcherPtr(new FuncMatcher(ALL_FUNC_MATCH_UNITS, ARRAYLEN(ALL_FUNC_MATCH_UNITS)));
        }

        platform_protocol_ptr CsvProtocolConverter::newPlatformProtocol()
        {
            return CsvProtocolPtr(new CsvProtocol(ALL_FUNCS, ARRAYLEN(ALL_FUNCS)));
        }

        void CsvProtocolConverter::get_spec_platform_field_val(string& valstr, const string& field_name, const bson::bo& param, const BaseReqPtr& req)
        {
            if (req->funcname_.find("login") != string::npos && field_name.compare("passWord") == 0)
            {
                string accountid = boost::any_cast<string>(req->u_req_->get_value("userName"));
                string password = any_to_str(req->u_req_->get_value("password", accountid));//加入账号解密，为空会解错
                boost::dynamic_pointer_cast<CsvSession>(req->session_)->initPassWord(accountid, password);
                valstr = password;
            }
            if (field_name.compare("passWord") == 0)
            {
                valstr = boost::dynamic_pointer_cast<CsvSession>(req->session_)->password;
            }
        }

        //void CsvProtocolConverter::get_spec_unity_field_val_platform(boost::any& val, const uni_func& u_func, const platform_func_ptr& p_func, const uni_field& u_field, const IRecordPtr& record, const unity_record_ptr& dst_record)
        void CsvProtocolConverter::get_spec_unity_field_val_platform(boost::any& val, const uni_func& u_func, 
            const platform_func_ptr& p_func, const uni_field& u_field, const IRecordPtr& record, 
            const unity_record_ptr& dst_record, const PacketPtr& packet)
        {
            if (u_field.name.compare("exchangeType") == 0)
            {
                if (u_func.name.compare("queryPosition") == 0)
                {
                    string temp = any_to_str(record->get_field_val(p_func->get_resp_field("交易市场")));
                    val = to_any(u_field.type, m_toolFunc->getExchangeType(temp));
                }
                else if (u_func.name.compare("queryOrder") == 0 ||\
                    u_func.name.compare("queryBusiness") == 0 || \
                    u_func.name.compare("queryBusinessInc") == 0)
                {
                    string temp = any_to_str(record->get_field_val(p_func->get_resp_field("市场")));
                    val = to_any(u_field.type, m_toolFunc->getExchangeType(temp));
                }
            }
            else if(u_field.name.compare("entrustBS") == 0)
            {
                if (u_func.name.compare("queryOrder") == 0)
                {
                    string temp = any_to_str(record->get_field_val(p_func->get_resp_field("买卖类别")));
                    val = to_any(u_field.type, m_toolFunc->getEntrustBS(temp));
                }
                else
                {
                    string temp = any_to_str(record->get_field_val(p_func->get_resp_field("委托方向")));
                    val = to_any(u_field.type, m_toolFunc->getEntrustBS(temp));
                }
            }
            else if(u_field.name.compare("entrustType") == 0)
            {
                string temp = any_to_str(record->get_field_val(p_func->get_resp_field("买卖类别")));
                val = to_any(u_field.type, m_toolFunc->getEntrusType(temp));
            }
            else if(u_field.name.compare("entrustProp") == 0)
            {
                string temp = any_to_str(record->get_field_val(p_func->get_resp_field("报价类型")));
                val = to_any(u_field.type, m_toolFunc->getEntrusPorp(temp));
            }
            else if(u_field.name.compare("entrustStatus") == 0)
            {
                string temp = any_to_str(record->get_field_val(p_func->get_resp_field("委托状态")));
                val = to_any(u_field.type, m_toolFunc->getEntrustStatus(temp));
            }
            else if(u_field.name.compare("cancelFlag") == 0)
            {
                val = to_any(u_field.type, char(CANCEL_FLAG_ENTRUST));
            }
            else if (u_field.name.compare("handFlag") == 0)
            {
                val = to_any(u_field.type, char('1'));
            }
            
        }
    }
}