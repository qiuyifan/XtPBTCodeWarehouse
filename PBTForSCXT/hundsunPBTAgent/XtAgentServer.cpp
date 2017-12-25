#include "common/Stdafx.h"
#include "utils/strings.h"
#include "net/RPCServer.h"
#include "XtAgentCenter.h"
#include "XtAgentServer.h"

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
        ftable.insert(make_pair("request", boost::bind(&XtAgentServer::request, shared_from_this(), _1, _2, _3)));

        string ip("");
        unsigned short port(0);
        utils::getIpPort(cfg.address, ip, port);
        server_ = boost::shared_ptr<net::RPCServer>(new net::RPCServer(io_service, ip, port, ftable));
        server_->setConfig(cfg);
        server_->start();
    }

    bson::bo XtAgentServer::request(const bson::bo& param, const r_int64 seq, const NetConnectionPtr& conn)
    {
        return xtagent_center_->request(param, seq, conn);
    }
}