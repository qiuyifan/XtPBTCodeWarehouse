#ifndef __CSV_SESSION_H__
#define __CSV_SESSION_H__


#include "SessionManager.h"
#include "Stock/StockSession.h"

namespace broker
{
    namespace stock
    {
        struct CsvSession : public StockSession
        {
        public:
            CsvSession();
            virtual ~CsvSession();

            void initPassWord(string accountID, string srcpassword);

            virtual void on_resp( const PacketPtr& packet );


        public:
            string password;

        };
        typedef boost::shared_ptr<CsvSession> CsvSessionPtr;
    }
}

#endif