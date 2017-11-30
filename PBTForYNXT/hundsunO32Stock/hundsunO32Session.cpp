#include "common/Stdafx.h"
#include "utils/SysInfo.h"
#include "hundsunO32Packet.h"
#include "hundsunO32Session.h"
#include "BaseCommon.h"
#include "utils/TimeTool.h"


namespace broker
{
    namespace stock
    {
        CsvSession::CsvSession() : StockSession()
        {

        }

        CsvSession::~CsvSession()
        {
        }

        void CsvSession::initPassWord(string accountID, string srcpassword)
        {
            // 恒投目前只支持股票，密码暂时不特殊处理
            password = srcpassword;
        }

        void CsvSession::on_resp( const PacketPtr& packet )
        {
            if (packet->resp->errno_ == int(ERR_SUCC))
            {
                if (packet->req->funcname_.compare("queryOrder") == 0)
                {
                    const size_t cnt = packet->resp->records_.size();
                    for (size_t i = 0; i < cnt; ++i)
                    {
                        const IRecordPtr& record = packet->resp->records_.at(i);
                        string exchangeName = any_to_str(record->get_field_val(packet->req->func_->get_resp_field("交易市场")));
                        string stockCode = any_to_str(record->get_field_val(packet->req->func_->get_resp_field("证券代码")));
                        string entrustNo = any_to_str(record->get_field_val(packet->req->func_->get_resp_field("委托序号")));
                        marketMap[entrustNo + "_" + stockCode] = exchangeName;
                    }
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