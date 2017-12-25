#ifndef __CSV_PROTOCOL_CONVERTER_H__
#define __CSV_PROTOCOL_CONVERTER_H__

#include "Stock/StockProtocolConverter.h"
#include "BasePacket.h"
#include "CsvToolFunc.h"

namespace broker
{
    class IReqContent;
    typedef boost::shared_ptr<IReqContent> IReqContentPtr;

    namespace stock
    {
        class CsvProtocolConverter : public StockProtocolConverter
        {
        public:
            CsvProtocolConverter();
            virtual ~CsvProtocolConverter();

        protected:
            virtual utils::SwapMapPtr newSwapMap();
            virtual FuncMatcherPtr newFuncMatcher();
            virtual platform_protocol_ptr newPlatformProtocol();

            // 获取平台特定字段值（需要特殊处理的字段）
            virtual void get_spec_platform_field_val(string& valstr, const string& field_name, const bson::bo& param, const BaseReqPtr& req);
            // 平台特定响应字段值获取
            //virtual void get_spec_unity_field_val_platform(boost::any& val, const uni_func& u_func, const platform_func_ptr& p_func, const uni_field& u_field, const IRecordPtr& record, const unity_record_ptr& dst_record);

            virtual void get_spec_unity_field_val_platform(boost::any& val, const uni_func& u_func, 
                const platform_func_ptr& p_func, const uni_field& u_field, const IRecordPtr& record, 
                const unity_record_ptr& dst_record, const PacketPtr& packet);
        public:
            CsvToolFuncPtr m_toolFunc;
        };
        typedef boost::shared_ptr<CsvProtocolConverter> CsvProtocolConverterPtr;
    }
}


#endif
