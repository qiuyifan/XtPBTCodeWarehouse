﻿#include "utils/CSingletonT.hpp"
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
        string accountMatch = config->read("kdmid", "account_match");
        LOG_INFO(boost::format("==: [kdmid] account_match: %s") %accountMatch);

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
                if (tmpVec.size() == 2)
                {
                    m_accountMatch[tmpVec.at(0)] =  tmpVec.at(1);
                }
            }
        }
    }

    string XtAgentConfig::getAccountID(const string& productName)
    {
        map<string, string>::iterator iter = m_accountMatch.find(productName);
        if (iter != m_accountMatch.end())
        {
            return iter->second;
        }
        return "";
    }

}