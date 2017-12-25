#ifndef __XT_AGENT_FILECHECKER__
#define __XT_AGENT_FILECHECKER__

#include "utils/CSingletonT.h"
#include "utils/Config.h"
#include "boost/enable_shared_from_this.hpp"
#include "utils/Threading.h"
#include "net/NetConnection.h"
#include "SMailer.h"

namespace agent
{
    class XtAgentFileChecker : public boost::enable_shared_from_this<XtAgentFileChecker>
    {
    public:
        XtAgentFileChecker(boost::asio::io_service& ioservice);
        ~XtAgentFileChecker();

        void init(boost::shared_ptr<utils::Configuration>& config);
        void on_scanFiles(const boost::system::error_code& error);
        void scanFiles();
        void start();
        bool sendMail(const string strMsg, const r_int64 timeNow);
        string genSendMsg(const map<string , r_int64>& warnMap);
    private:
        int                                                     m_nScanInterval; //扫描文件间隔 秒
        int                                                     m_nUpdateWarnTime;
        boost::shared_ptr<boost::asio::deadline_timer>          m_nScanTimer;
        vector<string>                                          m_vScanPaths;
        std::string                                             userName ;
        std::string                                             account ;
        std::string                                             password ;
        std::string                                             server ;
        bool                                                    m_bUseMailWarn;
    };
}

#endif