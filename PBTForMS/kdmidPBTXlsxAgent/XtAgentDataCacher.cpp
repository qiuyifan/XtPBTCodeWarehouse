#include "XtAgentDataCacher.h"
#include "XtAgentCommon.h"
#include "utils/TimeTool.h"
#include <Python.h>
#include "XtAgentError.h"

namespace agent
{
    XtDataCenter::XtDataCenter(boost::asio::io_service& ioservice)
        : m_nCacheInterval(5)
    {
        // 这里的ioservice不能用rpc引擎的，因为disparchio根本就没有启动
        m_nCacheTimer = boost::shared_ptr<boost::asio::deadline_timer>(new boost::asio::deadline_timer(ioservice));

    }

    XtDataCenter::~XtDataCenter()
    {

    }


    void XtDataCenter::start()
    {
        on_scanFiles(boost::system::error_code());
    }

    void XtDataCenter::init(boost::shared_ptr<utils::Configuration>& config)
    {
        m_nCacheInterval = config->readInt("datacache", "cache_interval", 5);
        LOG_INFO(boost::format("==: [datacache] cache_interval: %d") %m_nCacheInterval);

        m_strCachePath = config->read("common", "out_file_path");
        boost::algorithm::replace_all(m_strCachePath, "\\", "/");
        m_strCachePath = m_strCachePath + "/";
        boost::algorithm::replace_all(m_strCachePath, "//", "/");
        LOG_INFO(boost::format("==: [common] out file path : %d") %m_strCachePath);

        csvApi_ = boost::shared_ptr<XtAgentCSVApi>(new XtAgentCSVApi);
        start();
    }

    void XtDataCenter::on_scanFiles(const boost::system::error_code& error)
    {
        try
        {
            if (!error)
            {
                scanFiles();
                if (NULL != m_nCacheTimer)
                {
                    m_nCacheTimer->expires_from_now(boost::posix_time::seconds(m_nCacheInterval));
                    m_nCacheTimer->async_wait(boost::bind(&XtDataCenter::on_scanFiles, shared_from_this(), _1));
                }
            }
        }
        catch (const std::exception e)
        {
            LOG_ERROR((boost::format("failed to scan file, %s") %e.what()).str());
        }
        catch (const string e)
        {
            LOG_ERROR((boost::format("failed to scan file, %s") %e).str());
        }
        catch (...)
        {
            LOG_ERROR("failed to scan file, unknow error.");
        }

    }

    string XtDataCenter::getQueryFolder()
    {
        boost::shared_ptr<utils::Configuration> config = boost::shared_ptr<utils::Configuration>(new utils::Configuration((m_strCachePath + "exportGuid.ini").c_str()));
        config->load();

        string ret = config->read("common", "enablepath");
        if (ret.empty() || ret == "")
        {
            throw (string("get exportGuid config error"));
        }
        return ret + "/";
    }

    void XtDataCenter::genCsvFileFromXls(const string& queryPath)
    {
        string pyString = "\
#coding:utf-8\n\
#!/usr/bin/python\n\
\n\
import xlrd\n\
import csv\n\
import os\n\
import datetime\n\
\n\
DataList = []\n\
TimeList = []\n\
\n\
files = os.listdir('"+ queryPath +"')\n\
for tmpFile in files:\n\
    if tmpFile.endswith('_kd.csv') or tmpFile.endswith('_kd.CSV'):\n\
        os.remove('"+ queryPath +"' + tmpFile)\n\
for tmpFile in files:\n\
    if tmpFile.endswith('_kd.xlsx') or tmpFile.endswith('_kd.XLSX') or tmpFile.endswith('_kd.xls') or tmpFile.endswith('_kd.XLS'):\n\
        bk = xlrd.open_workbook('"+ queryPath +"' + tmpFile)\n\
        sh = bk.sheets()[0]\n\
        csv_file = file( '"+ queryPath + "{xlsx}.csv'.format(xlsx=os.path.splitext(tmpFile.replace(' ', '_'))[0]), 'wb')\n\
        csv_file_writer = csv.writer(csv_file)\n\
        nrows = sh.nrows\n\
        dataNo = -1\n\
        timeNo = -1\n\
        for i in range(0, nrows):\n\
            row_container = []\n\
            rowValues = sh.row_values(i)\n\
            for j in range(0, len(rowValues)):\n\
                cell = rowValues[j]\n\
                if type(cell) == unicode:\n\
                    valueGBK = cell.encode('gbk')\n\
                    if i == 0 :\n\
                        for tmpName in TimeList:\n\
                            if tmpName == valueGBK:\n\
                                timeNo = j\n\
                                break\n\
                        for tmpName in DataList:\n\
                            if tmpName == valueGBK:\n\
                                dataNo = j\n\
                                break\n\
                    row_container.append(cell.encode('gbk'))\n\
                elif type(cell) == float:\n\
                    if j == dataNo:\n\
                        row_container.append(datetime.datetime.strftime( xlrd.xldate.xldate_as_datetime(cell, 0), '%Y%m%d'))\n\
                    elif j == timeNo:\n\
                        tmpTime = xlrd.xldate.xldate_as_tuple(cell, 0)\n\
                        hour = str(tmpTime[3])\n\
                        min = str(tmpTime[4])\n\
                        sec = str(tmpTime[5])\n\
                        if len(hour) == 1 :\n\
                            hour = '0' + hour\n\
                        if len(min) == 1 :\n\
                            min = '0' + min\n\
                        if len(sec) == 1 :\n\
                            sec = '0' + sec\n\
                        row_container.append(hour + min + sec)\n\
                    else:\n\
                        row_container.append(float(cell))\n\
                else:\n\
                    row_container.append(str(cell))\n\
                \n\
            csv_file_writer.writerow(row_container)\n\
        csv_file.close()";
        PyRun_SimpleString(pyString.c_str());
    }

    void XtDataCenter::loadDatas(const string& filePath)
    {
        utils::WriteLock lock(m_mutex);
        m_cacheData = csvApi_->getAccountData(filePath);
    }

    bson::bo XtDataCenter::getData(const string& accountID, const int& funcNo)
    {
        utils::ReadLock lock(m_mutex);
        bson::bo ret;
        map<string, AccountStructPtr>::iterator iter = m_cacheData.find(accountID);
        if (iter != m_cacheData.end())
        {
            switch (funcNo)
            {
            case ORDER:
                ret = iter->second->orderData;
                break;
            case FUND:
                ret = iter->second->fundData;
                break;
            case DEAL:
                ret = iter->second->dealData;
                break;
            case POSITION:
                ret = iter->second->positionData;
                break;
            }
        }
        else
        {
            bson::bob builder;
            builder.append("error_no", GW_ERR_RECV_EMPTY_DATA);
            builder.append("error_info", (BF("未找到帐号[%1%]数据")%accountID).str());
            ret = builder.obj();
        }
        if (ret.isEmpty())
        {
            bson::bob builder;
            builder.append("error_no", 0);
            builder.append("record_cnt", 0);
            bson::BSONArrayBuilder arrayBuilder(builder.subarrayStart("records"));
            arrayBuilder.done();
            ret = builder.obj();
        }
        return ret;
    }

    void XtDataCenter::scanFiles()
    {
        if(m_strCachePath.empty())
        {
            LOG_ERROR( "[common] out file path is empty, please check config file!");
            return;
        }
        string queryPath = m_strCachePath + getQueryFolder();
        LOG_INFO( "-------------reload account data----------------");
        genCsvFileFromXls(queryPath);
        loadDatas(queryPath);
    }
}