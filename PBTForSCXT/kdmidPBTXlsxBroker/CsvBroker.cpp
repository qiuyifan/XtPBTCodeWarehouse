#include "common/Stdafx.h"
#include "CsvProtocolConverter.h"
#include "CsvPacket.h"
#include "CsvAgentClient.h"
#include "CsvSession.h"
#include "CsvBroker.h"

DECLARE_IMPLATE_BROKER_MODULE_INSTANCE_FUNC(stock::CsvBroker)

namespace broker
{
    namespace stock
    {
        CsvBroker::CsvBroker()
        {

        }

        CsvBroker::~CsvBroker()
        {

        }

        ProtocolConverterPtr CsvBroker::newProtocolConverter()
        {
            return CsvProtocolConverterPtr(new CsvProtocolConverter());
        }

        SessionPtr CsvBroker::newSession()
        {
            return CsvSessionPtr(new CsvSession());
        }

        BaseReqPtr CsvBroker::newRequest(const r_int64& seq, const net::NetConnectionPtr& conn, const SessionPtr& session, const string& funcname)
        {
            return CsvReqPtr(new CsvReq(seq, conn, session, funcname));
        }

        BaseClientPtr CsvBroker::newClient(const string& tag)
        {
            return CsvAgentClientPtr(new CsvAgentClient(tag));
        }
    }
}
