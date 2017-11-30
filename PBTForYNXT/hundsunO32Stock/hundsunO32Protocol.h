#ifndef __HUNDSUNO32_PROTOCOL_H__
#define __HUNDSUNO32_PROTOCOL_H__

#include "platform_protocol.h"
#include "hundsunO32DataDict.h"

namespace broker 
{
    namespace stock 
    {
        struct CsvField
        {
            string name;
            string desc;
            string type;
            BYTE required;
            boost::any defval;
        };

        struct CsvFunc
        {
            int func_code;                      // 功能标识 可为功能号或为功能名
            const CsvField* req_fields;     // 请求字段
            int req_field_cnt;                  // 请求字段数目
            const CsvField* resp_fields;    // 响应字段
            int resp_field_cnt;                 // 响应字段数目

            bool is_multi;                      // 是否多记录
            bool is_query;                      // 是否查询功能
        };

        struct CsvsField : public platform_field
        {
            bool is_encrypt;

            CsvsField(const CsvField& field)
            {
                name = field.name;
                desc = field.desc;
                type = field.type;
                is_required = (field.required == 'Y') ? true : false;
                defval = field.defval;
            }
            
            virtual bool is_type_double()
            {
                return type.find(".") != string::npos;
            }
        };
        typedef boost::shared_ptr<CsvsField> CsvsFieldPtr;

        struct CsvsFunc : public platform_func 
        {
            CsvsFunc(const CsvFunc& kdfunc)
            {
                id = kdfunc.func_code;
                is_multi = kdfunc.is_multi;
                is_query = kdfunc.is_query;

                for (int i = 0; i < kdfunc.req_field_cnt; ++i)
                {
                    req_fields.push_back(CsvsFieldPtr(new CsvsField(kdfunc.req_fields[i])));
                }

                for (int i = 0; i < kdfunc.resp_field_cnt; ++i)
                {
                    resp_fields.push_back(CsvsFieldPtr(new CsvsField(kdfunc.resp_fields[i])));
                }
            }
        };
        typedef boost::shared_ptr<CsvsFunc> CsvsFuncPtr;

        class CsvProtocol : public platform_protocol
        {
        public:
            CsvProtocol(const CsvFunc funcs[], int cnt) : platform_protocol()
            {
                for (int i = 0; i < cnt; ++i)
                {
                    CsvsFuncPtr func = CsvsFuncPtr(new CsvsFunc(funcs[i]));
                    funcs_[func->id] = func;
                }
            }
        protected:
            virtual void init()
            {
            }

        };
        typedef boost::shared_ptr<CsvProtocol> CsvProtocolPtr;

    }
};
#endif // __BROKER_PLATFORM_PROTOCOL_H__