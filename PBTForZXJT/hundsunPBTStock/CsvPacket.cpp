#include "common/Stdafx.h"
#include "common/BrokerCommon.h"
#include "utils/mathex.h"
#include "CsvSession.h"
#include "CsvPacket.h"


namespace broker
{
    namespace stock
    {
        // ---------------------------------------------------------------------

        CsvReq::CsvReq(const r_int64& seq, const net::NetConnectionPtr& conn, SessionPtr session, const string& funcname)
            : BaseReq(CsvReqContentPtr(new CsvReqContent), seq, conn, session, funcname) 
        {
        }

        void CsvReq::encode_header(bson::bob& bob)
        {
            BaseReq::encode_header(bob);
        }
        // ---------------------------------------------------------------------

        CsvRecord::CsvRecord(const bson::bo& src_record) : BsonRecord(src_record) 
        {

        }
        
        CsvRecord::~CsvRecord() 
        {

        }

        boost::any CsvRecord::get_field_val(const platform_field_ptr& field)
        {
            try 
            {
                if (field->type.compare("C") == 0)
                {
                    const string tmpstr = utils::get_be_val<string>(src_record_, field->name);
                    if (!tmpstr.empty())
                    {
                        return char(tmpstr.at(0));
                    }
                    else
                    {
                        throw (boost::format("value of [C:%s] is null") %field->name).str();
                    }
                }
                else if (field->type.find("S") != string::npos)
                {
                    string val = utils::get_be_val<string>(src_record_, field->name);
                    return val;
                }
                else if (field->type.find("N") != string::npos)
                {
                    int val = utils::get_be_val<int>(src_record_, field->name);
                    return val;
                }
                else if (field->type.find("B") != string::npos)
                {
                    double val = utils::get_be_val<double>(src_record_, field->name);
                    return val;
                }
                else
                {
                    throw std::invalid_argument((boost::format("undefined type [%s] of platform field [%s]") %field->type %field->name).str());
                }
            }
            catch (const boost::bad_lexical_cast& e)
            {
                throw (boost::format("[%s] get value failed, %s") %field->name %e.what()).str();
            }
        }
    }
}