/**
* 数据缓存中心，负责数据读取，所有数据从这个来
*/
#ifndef __XT_AGENT_DATACACHER__
#define __XT_AGENT_DATACACHER__

#include "utils/CSingletonT.h"
#include "utils/Config.h"
#include "boost/enable_shared_from_this.hpp"
#include "utils/Threading.h"
#include "net/NetConnection.h"
#include "SMailer.h"
#include "XtAgentCSV.h"

namespace agent
{

    class XtDataCenter : public boost::enable_shared_from_this<XtDataCenter>
    {
    public:
        XtDataCenter(boost::asio::io_service& ioservice);
        ~XtDataCenter();

        void init(boost::shared_ptr<utils::Configuration>& config);
        void on_scanFiles(const boost::system::error_code& error);
        void scanFiles();
        void start();
        /*
        * C++对于xlsx兼容性太差
        * 调用python把xlsx转换成csv文件，并不需要删除，文件自动会覆盖。
        */
        void genCsvFileFromXls(const string& queryPath);
        void loadDatas(const string& filePath);
        string getQueryFolder();
        bson::bo getData(const string& accountID, const int& funcNo);

    private:
        int                                                     m_nCacheInterval; // 缓存文件时间
        boost::shared_ptr<boost::asio::deadline_timer>          m_nCacheTimer;    // 缓存计时器
        boost::shared_ptr<XtAgentCSVApi>                        csvApi_;
        string                                                  m_strCachePath;
        map<string, AccountStructPtr>                           m_cacheData;       // 缓存数据
        utils::RWMutex                                          m_mutex;


    };
}

#endif