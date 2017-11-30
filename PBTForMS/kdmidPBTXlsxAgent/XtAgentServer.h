#ifndef __XTAGENT_SERVER_H__
#define __XTAGENT_SERVER_H__

namespace bson 
{
    class BSONObj;
    typedef bson::BSONObj bo;
}

namespace net
{
    class RPCServer;
    struct RPCServerConfig;
}

namespace agent
{
    class XtAgentCenter;

    class XtAgentServer : public boost::enable_shared_from_this<XtAgentServer>, public boost::noncopyable
    {
    public:
        XtAgentServer();
        ~XtAgentServer();

        void init(boost::asio::io_service& io_service, const net::RPCServerConfig& cfg, boost::shared_ptr<XtAgentCenter> xtagent_center);

        bson::bo request(const bson::bo& param, const r_int64 seq, const net::NetConnectionPtr& conn);
        bson::bo on_connected(const bson::bo& request, const r_int64 seq, const net::NetConnectionPtr conn);
        bson::bo on_conn_error(const bson::bo& error, const r_int64 seq,const net::NetConnectionPtr conn);

    private:
        boost::shared_ptr<net::RPCServer>           server_;
        boost::shared_ptr<XtAgentCenter>            xtagent_center_;

    };
}

#endif //__XTAGENT_SERVER_H__
