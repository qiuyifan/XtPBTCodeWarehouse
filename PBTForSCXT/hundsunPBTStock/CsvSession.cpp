#include "common/Stdafx.h"
#include "utils/SysInfo.h"
#include "CsvPacket.h"
#include "CsvSession.h"
#include "BaseCommon.h"
#include "utils/TimeTool.h"


namespace broker
{
    namespace stock
    {
        CsvSession::CsvSession() : StockSession()
        {
            marketMap.clear();
        }

        CsvSession::~CsvSession()
        {
        }

        void CsvSession::initPassWord(string accountID, string srcpassword)
        {
            // 恒投目前只支持股票，密码暂时不特殊处理
            password = srcpassword;
            /*
            vector<string> loginParm;
            boost::algorithm::split(loginParm, srcpassword, boost::is_any_of(","));
            if(loginParm.size() < 4)
            {
                BROKER_LOG_INFO(boost::format("login password error: %s") %srcpassword);
                throw (boost::format("CsvSession login parm is error!"));
                return;
            }

            platformID = loginParm[0];
            brokerID = loginParm[1];
            password = loginParm[2];
            brokerType = loginParm[3];
            */
        }

        void CsvSession::on_resp( const PacketPtr& packet )
        {
            if (packet->req->funcname_.compare("queryOrder") == 0)
            {
                const size_t cnt = packet->resp->records_.size();
                for (size_t i = 0; i < cnt; ++i)
                {
                    const IRecordPtr& record = packet->resp->records_.at(i);
                    string exchangeName = any_to_str(record->get_field_val(packet->req->func_->get_resp_field("exchangeName")));
                    string stockCode = any_to_str(record->get_field_val(packet->req->func_->get_resp_field("stockCode")));
                    string entrustNo = any_to_str(record->get_field_val(packet->req->func_->get_resp_field("entrustNo")));
                    marketMap[entrustNo + "_" + stockCode] = exchangeName;
                }
            }
        }

        string CsvSession::getExchangeName(const string stockCode, const string entrustNo)
        {
            map<string , string>::iterator iter = marketMap.find(entrustNo + "_" + stockCode);
            if (iter != marketMap.end())
            {
                return iter->second;
            }
            return "";
        }

    }
}