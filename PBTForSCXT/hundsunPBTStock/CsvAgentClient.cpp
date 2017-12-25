#include "common/Stdafx.h"
#include "CsvPacket.h"
#include "CsvAgentClient.h"
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