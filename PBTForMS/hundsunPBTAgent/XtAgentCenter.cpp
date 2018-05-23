/**
* Copyright (C) 2012 RZRK. All right reserved.
*
* @brief    特殊broker网关程序--主逻辑控制部分
* @author   rzrk
* @version  1.0
* @date     2016-01-13
*/

#include "common/Stdafx.h"
#include "common/log.h"
#include <boost/timer.hpp>
#include "net/RPCServer.h"
#include "utils/Config.h"
#include "utils/bsonFunc.h"
#include "utils/bson_utils.h"
#include "utils/BsonHelper.h"
#include "utils/TrafficWatch.h"
#include "utils/TimeTool.h"
#include "utils/io_service_pool.hpp"
#include <io.h>  

#include "XtAgentCommon.h"
#include "XtAgentServer.h"
#include "XtAgentCenter.h"
#include "XtAgentEnum.h"
#include "XtAgentCSV.h"
#include "bson/src/bson.h"

namespace agent
{
    using namespace boost;
    using namespace net;

    XtAgentCenter::XtAgentCenter() : work_(io_service_)
    {

    }

    XtAgentCenter::~XtAgentCenter()
    {

    }

    void XtAgentCenter::init(boost::shared_ptr<utils::Configuration> config)
    {
        try 
        {
            LOG_INFO(">>> init gateway...");

            config_ = config;

            is_log_detail_ = config->readInt("common", "log_detail", 1) == 1 ? true : false;
            thread_group_.create_thread(boost::bind(&asio::io_service::run, &io_service_));

            // init server
            RPCServerConfig server_cfg;
            const unsigned int listen_port = config->readInt("server", "port", 59903);
            server_cfg.address = string("0.0.0.0:") + boost::lexical_cast<string>(listen_port);
            LOG_INFO(boost::format("==: listen address: %s") %server_cfg.address);
            server_cfg.timeoutSecond = config->readInt("server", "conn_timeout_interval", 60); // 改为60s 默认600s
            LOG_INFO(boost::format("==: [server] connection timeout interval (seconds): %d") %server_cfg.timeoutSecond);

            server_cfg.isUseSSL = config->readInt("server", "is_use_ssl", 0) == 1;
            LOG_INFO(boost::format("==: [server] use ssl: %s") %(server_cfg.isUseSSL ? "on" : "off"));
            server_cfg.crtPath = config->read("server", "crt_path");
            LOG_INFO(boost::format("==: [server] crt path: %s") %server_cfg.crtPath);
            server_cfg.serverKeyPath = config->read("server", "server_key_path") ;
            LOG_INFO(boost::format("==: [server] server key path: %s") %server_cfg.serverKeyPath);
            server_cfg.tempDhPath = config->read("server", "temp_dh_path");
            LOG_INFO(boost::format("==: [server] temp dh path: %s") %server_cfg.tempDhPath);
            server_cfg.sslPassword = config->read("server", "ssl_password");
            server_ = boost::shared_ptr<XtAgentServer>(new XtAgentServer);
            server_->init(*(utils::thread::io_service_pool::instance().get_io_service_exclusive()), server_cfg, shared_from_this());

            check_ios_ = utils::thread::io_service_pool::instance().get_io_service_exclusive();
            data_center_ = GwDataCenterPtr(new GwDataCenter(io_service_));
            data_center_->init(config);

        }
        catch (const std::exception& e)
        {
            throw std::exception((boost::format("failed to init gateway, %s") %e.what()).str().c_str());
        }
        catch(...)
        {
            LOG_INFO("fail to init gateway!");
        }
    }

    void XtAgentCenter::run()
    {
        LOG_INFO(">>> gateway is running");
        thread_group_.join_all();
    }

    bson::bo XtAgentCenter::request(const bson::bo &param, const r_int64& seq, const NetConnectionPtr& conn)
    {
        io_service_.post(boost::bind(&XtAgentCenter::do_request, this, param.copy(), seq, conn)); // 跨线程，bson对象深拷贝，否则可能会出错
        return utils::bsonNull();
    }

    void XtAgentCenter::do_request(const bson::bo& param, const r_int64 seq, const NetConnectionPtr& conn)
    {
        try 
        {
            // 解析bson请求参数
            std::map<string, string> reqFields;
            int funcNo;
            string strAccountID, strPassword, funcName, accountFilePath;

            utils::safeParseBson(param, "func", funcName);
            utils::safeParseBson(param, "func_no", funcNo);
            LOG_INFO((boost::format(">>> [req] [%s|%ld] seq: %ld") %funcName %funcNo %seq).str() + (is_log_detail_ ?  utils::bsonFullToString(param) : ""));

            vector<bson::BSONElement> elem_ary;
            if (utils::safeParseBsonArray(elem_ary, param, "param"))
            {
                const int cnt = elem_ary.size();
                for (int i = 0; i < cnt ; ++i)
                {
                    bson::bo field_obj = elem_ary.at(i).Obj();
                    reqFields[utils::get_be_val<string>(field_obj, "name")] = utils::get_be_val<string>(field_obj, "value");
                }
            }
            strAccountID = reqFields["accountID"];
            strPassword = reqFields["passWord"];

            bson::bo errMsgBson;
            bson::bo data = data_center_->getData(strAccountID, funcNo);
            LOG_INFO((boost::format(">>> [resp] [%s|%ld] seq: %ld") %funcName %funcNo %seq).str() + (is_log_detail_ ? utils::bsonFullToString(data) : ""));
            RPCServer::sendData(data, seq, conn, STATUS_OK);
        }
        catch (...)
        {
            LOG_ERROR((boost::format(">>> [error] seq: %ld")  %seq).str() + utils::bsonFullToString(param));
            RPCServer::sendData(bson::bob().append("success", false).obj(), seq, conn, STATUS_OK);
        }
    }

}