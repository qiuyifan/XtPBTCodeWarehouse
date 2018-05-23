#include "XtAgentFileChecker.h"
#include "XtAgentFileOpt.h"
#include "XtAgentCommon.h"
#include "utils/TimeTool.h"

namespace agent
{

    XtAgentFileChecker::XtAgentFileChecker()
    {


    }

    XtAgentFileChecker::~XtAgentFileChecker()
    {

    }



    void XtAgentFileChecker::init(const utils::ConfigurationPtr& config)
    {

        m_nUpdateWarnTime = config->readInt("filescan", "update_warn_time", 300);
        LOG_INFO(boost::format("==: [filescan] update_warn_time: %d") %m_nUpdateWarnTime);

        userName = config->read("mail", "sender_name");
        LOG_INFO(boost::format("==: [mail] sender_name: %d") %userName);

        password = config->read("mail", "sender_password");
        account = config->read("mail", "receiver_name");
        LOG_INFO(boost::format("==: [mail] receiver_name: %d") %account);
        server = config->read("mail", "mail_server");
        LOG_INFO(boost::format("==: [mail] mail_server: %d") %server);

        string exportMainPath = config->read("common", "csv_file_path");
        m_vScanPaths.push_back(exportMainPath + "Folder1\\");
        m_vScanPaths.push_back(exportMainPath + "Folder2\\");
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
            map<string , r_int64> timeMap = XtAgentFileOpt::getFileUpdateTime(".CSV", *iter);
            for (map<string , r_int64>::iterator timeiter = timeMap.begin();
                timeiter != timeMap.end(); ++timeiter)
            {
                if (timeNow - timeiter->second > m_nUpdateWarnTime)
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