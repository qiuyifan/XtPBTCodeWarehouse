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

        }

    }
}