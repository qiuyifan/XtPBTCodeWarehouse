#include "common/Stdafx.h"
#include "utils/strings.h"
#include "utils/bsonFunc.h"
#include "net/RPCServer.h"
#include "XtAgentCenter.h"
#include "XtAgentServer.h"
#include "XtAgentCommon.h"

namespace agent
{
    using namespace boost;
    using namespace net;

    XtAgentServer::XtAgentServer()
    {

    }

    XtAgentServer::~XtAgentServer()
    {

    }

    void XtAgentServer::init(boost::asio::io_service& io_service, const RPCServerConfig& cfg, boost::shared_ptr<XtAgentCenter> xtagent_center)
    {
        xtagent_center_ = xtagent_center;
        net::FuncTable ftable;
        ftable.insert(make_pair("onConnected", boost::bind(&XtAgentServer::on_connected, shared_from_this(), _1, _2, _3)));
        ftable.insert(make_pair("onError", boost::bind(&XtAgentServer::on_conn_error, shared_from_this(), _1, _2, _3)));
        ftable.insert(make_pair("request", boost::bind(&XtAgentServer::request, shared_from_this(), _1, _2, _3)));

        string ip("");
        unsigned short port(0);
        utils::getIpPort(cfg.address, ip, port);
        server_ = boost::shared_ptr<net::RPCServer>(new net::RPCServer(io_service, ip, port, ftable));
        server_->setConfig(cfg);
        server_->start();
    }

    bson::bo XtAgentServer::on_connected(const bson::bo& request, const r_int64 seq,const net::NetConnectionPtr conn)
    {
        // LOG_INFO(boost::format("client connected %1%:%2%") % conn->m_peerIp % conn->m_peerPort);
        LOG_INFO(BF("client connected %1%:%2%") % conn->m_peerIp % conn->m_peerPort);
        return utils::bsonNull();
    }

    bson::bo XtAgentServer::on_conn_error(const bson::bo& err, const r_int64 seq, const NetConnectionPtr conn)
    {
        // LOG_INFO(boost::format("client lost %1%:%2%, error: %3%") % conn->m_peerIp % conn->m_peerPort % err["error"].String());
        LOG_INFO( BF("client lost %1%:%2%, error: %3%") % conn->m_peerIp % conn->m_peerPort % err["error"].String());
        return utils::bsonNull();
    }

    bson::bo XtAgentServer::request(const bson::bo& param, const r_int64 seq, const NetConnectionPtr& conn)
    {
        return xtagent_center_->request(param, seq, conn);
    }
}