#ifndef __XTAGENT_CENTER_H__
#define __XTAGENT_CENTER_H__

#include <boost/asio/io_service.hpp>
#include "XtAgentFileChecker.h"
#include "XtAgentDataCacher.h"

namespace bson 
{
    class BSONObj;
    typedef bson::BSONObj bo;
}

namespace net
{
    class NetConnection;
    typedef boost::shared_ptr<NetConnection> NetConnectionPtr;
}

namespace utils
{
    class Configuration;
}

namespace agent
{
    class XtAgentServer;
    class XtAgentCSVApi;

    typedef boost::shared_ptr<boost::asio::io_service> io_service_ptr;
    typedef boost::shared_ptr<boost::asio::io_service::work> work_ptr;

    class XtAgentCenter : public boost::enable_shared_from_this<XtAgentCenter>,  public boost::noncopyable
    {
    public:
        XtAgentCenter();
        ~XtAgentCenter();

        void init(boost::shared_ptr<utils::Configuration> config);
        void run();
        bson::bo request(const bson::bo &param, const r_int64& seq, const net::NetConnectionPtr& conn);
        void getQueryFiles(vector<string>& dataFilesPath, string& suffix);

    private:
        void do_request(const bson::bo& param, const r_int64 seq, const net::NetConnectionPtr& conn);
        string getQueryFolder();

    private:
        boost::shared_ptr<utils::Configuration>     config_;
        boost::asio::io_service                     io_service_;
        boost::asio::io_service::work               work_;
        boost::shared_ptr<XtAgentServer>            server_;
        boost::thread_group                         thread_group_;  // 线程池
        boost::shared_ptr<XtAgentFileChecker>       file_checker_;
        boost::shared_ptr<XtDataCenter>             dataCenter_;

        bool is_log_detail_;
        io_service_ptr check_ios_;

        std::string     m_csv_file_path;
        std::string     m_strGenFileName;
    };
}

#endif // __XTAGENT_CENTER_H__
