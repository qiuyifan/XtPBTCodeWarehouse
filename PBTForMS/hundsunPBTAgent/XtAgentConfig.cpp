#include "utils/CSingletonT.hpp"
#include "XtAgentConfig.h"
#include "common/Stdafx.h"
#include "XtAgentCommon.h"

IMPL_SINGLETON_CLASS(agent::XtAgentConfig);

namespace agent
{
    XtAgentConfig::XtAgentConfig()
    {

    }

    XtAgentConfig::~XtAgentConfig()
    {

    }

    void XtAgentConfig::init(boost::shared_ptr<utils::Configuration>& config)
    {
        string accountMatch = config->read("hundsun", "account_match");
        LOG_INFO(boost::format("==: [hundsun] account_match: %s") %accountMatch);

        parseAccountMatch(accountMatch);
    }

    void XtAgentConfig::parseAccountMatch(string& accountMatch)
    {
        vector<string> vec;
        boost::split(vec, accountMatch, boost::is_any_of(";"));
        if (vec.size() > 0)
        {
            vector<string> defVec;
            for (int i = 0; i < vec.size(); ++i)
            {
                vector<string> tmpVec;
                boost::split(tmpVec, vec.at(i), boost::is_any_of(":"));
                if (tmpVec.size() == 3)
                {
                    m_accountMatch[tmpVec.at(0)+ "__" +tmpVec.at(1)] =  tmpVec.at(2);
                }
            }
        }
    }

    string XtAgentConfig::getAccountID(const string& productName, const string& unitName)
    {
        map<string, string>::iterator iter = m_accountMatch.find(productName + "__" + unitName);
        if (iter != m_accountMatch.end())
        {
            return iter->second;
        }
        return "";
    }

    vector<string> XtAgentConfig::getAllAccountID()
    {
        vector<string> ret;
        for(map<string, string>::iterator iter = m_accountMatch.begin(); iter != m_accountMatch.end(); ++iter)
        {
            ret.push_back(iter->second);
        }
        return ret;
    }

}