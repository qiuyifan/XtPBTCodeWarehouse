#ifndef __CSV_PACKET_H__
#define __CSV_PACKET_H__

#include "BasePacket.h"

namespace broker 
{
    namespace stock 
    {
        class CsvReqContent : public CommonReqContent
        {
        };
        typedef boost::shared_ptr<CsvReqContent> CsvReqContentPtr;

        struct CsvReq : public BaseReq
        {
            CsvReq(const r_int64& seq, const net::NetConnectionPtr& conn, SessionPtr session, const string& funcname);
            virtual void encode_header(bson::bob& bob);
        };
        typedef boost::shared_ptr<CsvReq> CsvReqPtr;


        class CsvRecord : public BsonRecord
        {
        public:
            CsvRecord(const bson::bo& src_record);
            virtual ~CsvRecord();
            boost::any get_field_val(const platform_field_ptr& field);
        };
        typedef boost::shared_ptr<CsvRecord> CsvRecordPtr;
    }
}

#endif