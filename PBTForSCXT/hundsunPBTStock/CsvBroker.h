#ifndef __CSV_BROKER_H__
#define __CSV_BROKER_H__

#include "Stock/StockBroker.h"

namespace broker
{
    namespace stock
    {
        class CsvBroker : public StockBroker
        {
        public:
            CsvBroker();
            virtual ~CsvBroker();

        protected:
            virtual ProtocolConverterPtr newProtocolConverter();
            virtual SessionPtr newSession();
            virtual BaseReqPtr newRequest(const r_int64& seq, const net::NetConnectionPtr& conn, const SessionPtr& session, const string& funcname);
            virtual BaseClientPtr newClient(const string& tag);
        };
    }
}

#endif 