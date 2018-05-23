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

        // 这里需要传产品和单元的名称 恒投客户端资金只有这个名字没有id
        string getAccountID(const string& productName, const string& unitName);

        vector<string> getAllAccountID();

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