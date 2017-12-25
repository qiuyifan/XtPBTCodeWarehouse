#ifndef __XT_AGENT_CONFIG__
#define __XT_AGENT_CONFIG__

#include "utils/CSingletonT.h"
#include "utils/Config.h"

namespace agent
{
    class XtAgentConfig : public utils::CSingletonT<XtAgentConfig>
    {
    public:
        XtAgentConfig();
        ~XtAgentConfig();

        void init(boost::shared_ptr<utils::Configuration>& config);

        void parseAccountMatch(string& accountMatch);

        // 这里需要传产品名称 针对民生信托版本干掉资产单元名称
        string getAccountID(const string& productName);

    private:
        /*
        * 产品账号用户id匹配关系
        * < 产品_单元 ,账号  >
        * 暂时不需要加锁，目前只有启动的时候回去写这个数据
        */
        map< string, string >            m_accountMatch; 

    };
}

#endif