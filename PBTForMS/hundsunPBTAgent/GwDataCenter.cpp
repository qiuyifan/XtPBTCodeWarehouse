#include "utils/CSingletonT.hpp"
#include "GwDataCenter.h"
#include "agent/AgentCommon.h"
#include "utils/convFunc.h"

namespace agent
{
    GwDataCenter::GwDataCenter( boost::asio::io_service& ioService)
        : m_nReloadDataInterval(60)
    {
        m_nReloadDataTimer = boost::shared_ptr<boost::asio::deadline_timer>(new boost::asio::deadline_timer(ioService));
    }

    GwDataCenter::~GwDataCenter()
    {

    }

    void GwDataCenter::init(const utils::ConfigurationPtr& config)
    {
        m_nReloadDataInterval = config->readInt("filescan", "sacn_interval", 60);
        LOG_INFO(boost::format("==: [filescan] scan_interval: [%1%]") %m_nReloadDataInterval);

        m_strExportPath = config->read("common", "csv_file_path");
        utils::safeUtf82Gbk(m_strExportPath);
        boost::algorithm::replace_all(m_strExportPath, "\\", "/");
        m_strExportPath = m_strExportPath + "/";
        boost::algorithm::replace_all(m_strExportPath, "//", "/");
        LOG_INFO(boost::format("==: [scan] csv_file_path: [%s]") %m_strExportPath);

        m_bUseMailWarn = config->readInt("mail", "use_mail_warn", 0) == 0 ? false : true;
        LOG_INFO(boost::format("==: [mail] use_mail_warn: %s") %(m_bUseMailWarn ?"on" : "off"));


        //m_ptrCsvImp = csv::CsvImpPtr(new csv::CsvImp);
        //m_ptrCsvImp->init(config);

        m_ptrCsvImp = boost::shared_ptr<XtAgentCSVApi>(new XtAgentCSVApi());


        m_ptrFileChecker = boost::shared_ptr<XtAgentFileChecker>(new XtAgentFileChecker());
        m_ptrFileChecker->init(config);

        start();

    }

    void GwDataCenter::start()
    {
        onWorkLoop();
    }

    void GwDataCenter::onWorkLoop(const boost::system::error_code& error)
    {
        try
        {
            if (!error)
            {
                doWorkLoop();
                if (NULL != m_nReloadDataTimer && m_nReloadDataInterval > 0)
                {
                    m_nReloadDataTimer->expires_from_now(boost::posix_time::seconds(m_nReloadDataInterval));
                    m_nReloadDataTimer->async_wait(boost::bind(&GwDataCenter::onWorkLoop, shared_from_this(), _1));
                }
            }
            else
            {
                LOG_DEBUG(boost::format("cancel or error in scan file, %s") %error.message());
            }
        }
        catch (const std::exception e)
        {
            LOG_ERROR(boost::format("failed to scan file, %s") %e.what());
        }
        catch (const string e)
        {
            LOG_ERROR(boost::format("failed to scan file, %s") %e);
        }
        catch (...)
        {
            LOG_ERROR("failed to scan file, unknow error.");
        }

    }

    string GwDataCenter::getQueryFolder()
    {

        boost::shared_ptr<utils::Configuration> config = boost::shared_ptr<utils::Configuration>(new utils::Configuration((m_strExportPath + "exportGuid.ini").c_str()));
        config->load();

        string ret = config->read("common", "enablepath");
        if (ret.empty() || ret == "")
        {
            throw (string("get exportGuid config error"));
        }
        return (ret + "/");
    }

    void GwDataCenter::doWorkLoop()
    {
        try
        {
            string folder = getQueryFolder();
            string workFolder = m_strExportPath + folder;

            // 检查文件更新时间
            if (m_bUseMailWarn)
            {
                if (m_ptrFileChecker)
                {
                    m_ptrFileChecker->scanFiles();
                }
                else 
                {
                    cout << "文件更新检查实例" << endl;
                    LOG_ERROR("文件更新检查实例.");
                }
            }

            // 读取csv文件数据
            if (m_ptrCsvImp)
            {
                LOG_DEBUG( "-------------load start----------------");

                map< string, AccountStructPtr > accountData = m_ptrCsvImp->loadData(workFolder);
                {
                    utils::WriteLock  lock(m_mutex);
                    m_mapAccountData = accountData;
                }
                LOG_DEBUG( "-------------load end----------------");

            }
            else
            {
                cout << "找不到csv插件实例" << endl;
                LOG_ERROR("找不到csv插件实例.");
            }
        }
        catch (const std::exception e)
        {
            LOG_ERROR(boost::format("failed to scan file, %s") %e.what());
        }
        catch (const string e)
        {
            LOG_ERROR(boost::format("failed to scan file, %s") %e);
        }
        catch (...)
        {
            LOG_ERROR("failed to scan file, unknow error.");
        }
    }

    bson::bo GwDataCenter::getData(const string& fundAccount, const int& funcNo)
    {
        bson::bo ret;
        utils::ReadLock lock(m_mutex);
        map<string, AccountStructPtr>::iterator iter = m_mapAccountData.find(fundAccount);
        if (iter != m_mapAccountData.end())
        {
            switch (funcNo)
            {
            case XT_DATA_TYPE_LOGIN:
            case XT_DATA_TYPE_FUND:
                return iter->second->fundData;
            case XT_DATA_TYPE_ORDER:
                return iter->second->orderData;
            case XT_DATA_TYPE_BUSINESS:
                return iter->second->dealData;
            case XT_DATA_TYPE_POSITION:
                return iter->second->positionData;
            }
        }

        bson::bob builder;
        builder.append("error_no", GW_ERR_RECV_EMPTY_DATA);
        builder.append("error_info", (BF("未找到帐号[%1%]数据") %fundAccount).str());
        return builder.obj();
 
    }
}