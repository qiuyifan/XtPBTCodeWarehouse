#ifndef XT_AGENT_CSVAPI_H
#define XT_AGENT_CSVAPI_H

#include "common/Stdafx.h"
#include <boost/filesystem.hpp>
#include "utils/BsonHelper.h"

#include "XtAgentMatchDef.h"
#include "XtAgentError.h"

namespace bson 
{
    class BSONObj;
    typedef bson::BSONObj bo;

    class BSONObjBuilder;
    typedef bson::BSONObjBuilder bob;
}

namespace agent
{
    class XtAgentCSVApi
    {
    public:
        XtAgentCSVApi();
        ~XtAgentCSVApi();

        bool getFuncMatchUnit(FuncMatchUnit& coverFuncUnit, int funcNo);
        void loadNamePos(string line , std::map<string , int>& name2pos);
        double getPerAmount(string str);
        double getAmount(string str);
        void genErrMsgData(const string& errMsg, bson::bo& errMsgBson);
        bson::bo genData(vector<string>& dataFilesPath, int funcNo, string& strAccountID);
        void coverField(vector<string>& lineParm, bson::BSONArrayBuilder& arrayBuilder, int funcNo, std::map<string , int>& name2pos);
        string getTime(string str);
    };

}


#endif /*XT_AGENT_DBFAPI_H*/