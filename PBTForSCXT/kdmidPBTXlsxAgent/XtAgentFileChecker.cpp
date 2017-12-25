#include "XtAgentFileChecker.h"
#include "XtAgentFileOpt.h"
#include "XtAgentCommon.h"
#include "utils/TimeTool.h"

namespace agent
{
    XtAgentFileChecker::XtAgentFileChecker(boost::asio::io_service& ioservice)
        : m_nScanInterval(300)
        , m_nUpdateWarnTime(300)
    {
        // 这里的ioservice不能用rpc引擎的，因为disparchio根本就没有启动
        m_nScanTimer = boost::shared_ptr<boost::asio::deadline_timer>(new boost::asio::deadline_timer(ioservice));

    }

    XtAgentFileChecker::~XtAgentFileChecker()
    {

    }


    void XtAgentFileChecker::start()
    {
        if (NULL != m_nScanTimer)
        {
            m_nScanTimer->expires_from_now(boost::posix_time::seconds(m_nScanInterval));
            m_nScanTimer->async_wait(boost::bind(&XtAgentFileChecker::on_scanFiles, shared_from_this(), _1));
        }
    }

    void XtAgentFileChecker::init(boost::shared_ptr<utils::Configuration>& config)
    {
        m_nScanInterval = config->readInt("filescan", "sacn_interval", 300);
        LOG_INFO(boost::format("==: [filescan] sacn_interval: %d") %m_nScanInterval);

        m_nUpdateWarnTime = config->readInt("filescan", "update_warn_time", 300);
        LOG_INFO(boost::format("==: [filescan] update_warn_time: %d") %m_nUpdateWarnTime);

        userName = config->read("mail", "sender_name");
        LOG_INFO(boost::format("==: [mail] sender_name: %d") %userName);

        password = config->read("mail", "sender_password");
        account = config->read("mail", "receiver_name");
        LOG_INFO(boost::format("==: [mail] receiver_name: %d") %account);
        server = config->read("mail", "mail_server");
        LOG_INFO(boost::format("==: [mail] mail_server: %d") %server);

        m_bUseMailWarn = config->readInt("mail", "use_mail_warn", 0) == 0 ? false : true;
        LOG_INFO(boost::format("==: [mail] use_mail_warn: %s") %(m_bUseMailWarn ?"on" : "off"));

        string exportMainPath = config->read("common", "out_file_path");
        boost::algorithm::replace_all(exportMainPath, "\\", "/");
        exportMainPath = exportMainPath + "/";
        boost::algorithm::replace_all(exportMainPath, "//", "/");

        m_vScanPaths.push_back(exportMainPath + "Folder1\\");
        m_vScanPaths.push_back(exportMainPath + "Folder2\\");

        if (m_bUseMailWarn)
        {
            start();
        }
    }

    void XtAgentFileChecker::on_scanFiles(const boost::system::error_code& error)
    {
        if (!error)
        {
            scanFiles();
            if (NULL != m_nScanTimer)
            {
                m_nScanTimer->expires_from_now(boost::posix_time::seconds(m_nScanInterval));
                m_nScanTimer->async_wait(boost::bind(&XtAgentFileChecker::on_scanFiles, shared_from_this(), _1));
            }
        }
    }

    string XtAgentFileChecker::genSendMsg(const map<string , r_int64>& warnMap)
    {
        string ret;
        ret = "\n\n";
        for (map<string, r_int64>::const_iterator iter = warnMap.begin();\
            iter != warnMap.end() ; ++iter)
        {
            ret += "        警告:文件  " + iter->first +\
                " 已经 " + boost::lexical_cast<string>(iter->second)\
                + " 秒 未更新!\n";
        }
        ret + "\n\n";
        return ret;
    }

    void XtAgentFileChecker::scanFiles()
    {
        LOG_INFO( "-------------check file update time----------------");
        r_int64 timeNow = utils::clock();
        map<string , r_int64> warnMap;
        for (vector<string>::iterator iter = m_vScanPaths.begin();\
            iter != m_vScanPaths.end(); ++iter)
        {
            map<string , r_int64> timeMap = XtAgentFileOpt::getFileUpdateTime(".XLSX", *iter);
            for (map<string , r_int64>::iterator timeiter = timeMap.begin();
                timeiter != timeMap.end(); ++timeiter)
            {
                if (timeNow - timeiter->second > m_nScanInterval)
                {
                    warnMap[timeiter->first] = timeNow - timeiter->second;
                }
            }
        }
        if (warnMap.size() > 0 )
        {
            if (!sendMail(genSendMsg(warnMap), timeNow))
            {
                LOG_ERROR( "警告邮件发送失败，请检查网络状态或者邮件配置。");
            }
        }
    }


    bool XtAgentFileChecker::sendMail(const string strMsg,const r_int64 timeNow)
    {
        try
        {
            utils::Configuration config ;

            SMailer::TextPlainContent  content2(strMsg);

            SMailer::MailInfo info;
            info.setSenderName(std::string("文件更新警告:") + userName);
            info.setSenderAddress(account);

            info.setReceiver("rzrk_report", account);

            info.setPriority(SMailer::Priority::normal);
            char szTmp[512];

            string nowTime = utils::d8_secondToDateTimeString(timeNow);
            sprintf(szTmp, "文件更新警告 : %s", nowTime.c_str());

            info.setSubject(szTmp);
            info.addMimeContent(&content2);

            SMailer::MailSender sender(server, userName, password);
            sender.setMail(&SMailer::MailWrapper(&info));
            sender.sendMail();   
        }
        catch (SMailer::MailException& e)
        {
            return false;
        }
        catch (...)
        {
            return false;
        }

        return true;
    }
}