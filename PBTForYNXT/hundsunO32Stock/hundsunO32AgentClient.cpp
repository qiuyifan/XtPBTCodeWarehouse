#include "common/Stdafx.h"
#include "hundsunO32Packet.h"
#include "hundsunO32AgentClient.h"
#include "common/BrokerCommon.h"


namespace broker
{
    namespace stock
    {
        CsvAgentClient::CsvAgentClient(const string& name) : StockClient(name)
        {

        }

        CsvAgentClient::~CsvAgentClient()   
        {

        }

        IRecordPtr CsvAgentClient::createRecrod(const platform_func_ptr& func, const bson::BSONElement& elem)
        {
            return CsvRecordPtr(new CsvRecord(elem.Obj().copy()));
        }
    }
}