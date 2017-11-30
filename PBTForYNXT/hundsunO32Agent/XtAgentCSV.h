#ifndef __XT_AGENT_CSVAPI_H__
#define __XT_AGENT_CSVAPI_H__

#include "XtAgentStruct.h"
#include "utils/BsonHelper.h"

#define FUND     0
#define ORDER    1
#define DEAL     2
#define POSITION 3

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

        map< string, AccountStructPtr > getAccountData(const string& filePath);
        map< string, bson::bo > getDataFromFiles(const int& funcNo, const vector< string >& queryFileList);
        string getReqFileSuffix(const int& funcNo);
        vector< string > getQueryFiles(const string& filePath);
        void getDataFromFile(const string& file, const int& funcNo, map < string, vector< map< string, string > > >& retData);
        void loadNamePos(string line , vector<string>& headName);
        map< string, bson::bo > makeRetData(map < string, vector< map< string, string > > > rawData);
        bson::bo encode(vector<map < string , string > >& data);
    };

}


#endif /*XT_AGENT_DBFAPI_H*/