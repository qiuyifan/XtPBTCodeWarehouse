#ifndef __CSV_AGENT_CLIENT_H__
#define __CSV_AGENT_CLIENT_H__

#include "Stock/StockClient.h"

namespace broker 
{
    namespace stock
    {
        class CsvAgentClient : public StockClient
        {
        public:
            CsvAgentClient(const string& name);
            virtual ~CsvAgentClient();

        protected:
            virtual IRecordPtr createRecrod(const platform_func_ptr& func, const bson::BSONElement& elem);
            
        private:
            int m_nPosition;
        };
        typedef boost::shared_ptr<CsvAgentClient> CsvAgentClientPtr;
    }
}

#endif