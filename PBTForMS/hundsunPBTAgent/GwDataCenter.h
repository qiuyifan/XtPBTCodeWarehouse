#ifndef __GW_DATA_CENTER__
#define __GW_DATA_CENTER__

#include "common/Stdafx.h"
#include "utils/CSingletonT.h"
#include "utils/Config.h"
#include "boost/asio/deadline_timer.hpp"
#include "utils/Threading.h"
#include "XtAgentFileChecker.h"
#include "XtAgentCSV.h"

namespace agent
{
    class GwDataCenter : public boost::enable_shared_from_this<GwDataCenter>
    {
    public:

        GwDataCenter( boost::asio::io_service& ioService);

        virtual ~GwDataCenter();

        void init(const utils::ConfigurationPtr& config);

        void start();

        void onWorkLoop(const boost::system::error_code& error = boost::system::error_code());

        string getQueryFolder();

        void doWorkLoop();

        bson::bo getData(const string& fundAccount, const int& funcNo);

    private:

        // 这里的io_service使用center的io_service 确保io正常运行
        boost::shared_ptr<boost::asio::deadline_timer>          m_nReloadDataTimer;    // 数据重载定时器

        boost::shared_ptr<XtAgentFileChecker>                   m_ptrFileChecker;

        int                                                     m_nReloadDataInterval; // 数据缓存时间间隔(秒)

        boost::shared_ptr<XtAgentCSVApi>                        m_ptrCsvImp;

        map< string, AccountStructPtr >                         m_mapAccountData;

        utils::RWMutex                                          m_mutex;

        string                                                  m_strExportPath;       // 导出文件目录

        bool                                                    m_bUseMailWarn;

    };
    typedef boost::shared_ptr<GwDataCenter>                     GwDataCenterPtr;
}

#endif