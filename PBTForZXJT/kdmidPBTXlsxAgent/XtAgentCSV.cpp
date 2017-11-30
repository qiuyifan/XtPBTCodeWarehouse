#include "common/Stdafx.h"
#include "XtAgentCSV.h"
#include "XtAgentFileOpt.h"
#include "XtAgentConfig.h"

namespace agent
{

    void split(std::vector<std::string>& result, std::string str,std::string pattern)
    {
        std::string::size_type pos;
        str += pattern;//扩展字符串以方便操作
        int size=str.size();

        for(int i = 0; i < size; ++i)
        {
            pos = str.find(pattern,i);
            if(pos < size)
            {
                std::string s=str.substr(i,pos-i);
                result.push_back(s);
                i = pos+pattern.size() - 1;
            }
        }
    }

    string double2namestr(const string& num )
    {
        return num.substr(0, num.find("."));
    }

    XtAgentCSVApi::XtAgentCSVApi()
    {

    }

    XtAgentCSVApi::~XtAgentCSVApi()
    {

    }

    map< string, AccountStructPtr > XtAgentCSVApi::getAccountData(const string& filePath)
    {
        // 一个一个处理， 先处理fund
        map< string, AccountStructPtr > ret;
        vector< string > queryFileList = getQueryFiles(filePath);
        map< string, bson::bo > fundData = getDataFromFiles(FUND, queryFileList);
        map< string, bson::bo > orderData = getDataFromFiles(ORDER, queryFileList);
        map< string, bson::bo > dealData = getDataFromFiles(DEAL, queryFileList);
        map< string, bson::bo > positionData = getDataFromFiles(POSITION, queryFileList);

        // 创建结构体就按fund来创，这个没有其他的应该也没有。
        // 默认每一个帐号只有一个资金数据
        for(map< string, bson::bo >::iterator iter = fundData.begin(); 
            iter != fundData.end(); ++iter)
        {
            AccountStructPtr accountData = AccountStructPtr(new AccountStruct());
            accountData->accountID = iter->first;
            accountData->fundData = iter->second;
            ret[iter->first] = accountData;
        }

        for (map< string, bson::bo >::iterator iter = orderData.begin();
            iter != orderData.end(); ++iter)
        {
            map< string, AccountStructPtr >::iterator fIter = ret.find(iter->first);
            if (fIter != ret.end())
            {
                fIter->second->orderData = iter->second;
            }
        }
        for (map< string, bson::bo >::iterator iter = dealData.begin();
            iter != dealData.end(); ++iter)
        {
            map< string, AccountStructPtr >::iterator fIter = ret.find(iter->first);
            if (fIter != ret.end())
            {
                fIter->second->dealData = iter->second;
            }
        }
        for (map< string, bson::bo >::iterator iter = positionData.begin();
            iter != positionData.end(); ++iter)
        {
            map< string, AccountStructPtr >::iterator fIter = ret.find(iter->first);
            if (fIter != ret.end())
            {
                fIter->second->positionData = iter->second;
            }
        }
        return ret;
    }

    string XtAgentCSVApi::getReqFileSuffix(const int& funcNo)
    {
        switch (funcNo)
        {
        case FUND:
            {
                return "_fund_kd";
                break;
            }
        case POSITION:
            {
                return "_position_kd";
                break;
            }
        case ORDER:
            {
                return"_order_kd";
                break;
            }
        case DEAL :
            {
                return "_dealdetail_kd";
                break;
            }
        default:
            {
                throw((BF(" 暂不支持功能号: %1% 查询. ") %funcNo ).str());
                break;
            }
        }
        return "unknown";
    }

    vector< string > XtAgentCSVApi::getQueryFiles(const string& filePath)
    {
        vector<string> ret;
        XtAgentFileOpt::getFilePaths(".csv", filePath, ret);
        XtAgentFileOpt::getFilePaths(".CSV", filePath, ret);
        return ret;
    }

    map< string, bson::bo > XtAgentCSVApi::getDataFromFiles( const int& funcNo, const vector< string >& queryFileList)
    {
        map< string, bson::bo > ret;
        string key = getReqFileSuffix(funcNo);
        map < string, vector< map< string, string > > > retData;
        for(vector<string>::const_iterator iter = queryFileList.begin(); 
            iter != queryFileList.end(); ++iter)
        {
            if ((*iter).find(key) != string::npos)
            {
                getDataFromFile(*iter, funcNo, retData);
            }
        }
        ret = makeRetData(retData);
        return ret;
    }

    bson::bo XtAgentCSVApi::encode(vector<map < string , string > >& data)
    {
        bson::bob builder;

        builder.append("error_no", 0);
        builder.append("record_cnt", data.size());
        bson::BSONArrayBuilder arrayBuilder(builder.subarrayStart("records"));
        for (vector<map < string , string > >::iterator iter = data.begin(); iter != data.end() ; ++iter )
        {
            bson::BSONObjBuilder subBuilder;
            for (map<string, string>::iterator mapIter = (*iter).begin(); \
                mapIter != (*iter).end() ; ++mapIter)
            {
                subBuilder.append( (*mapIter).first, (*mapIter).second);
            }
            arrayBuilder.append(subBuilder.obj());
        }
        arrayBuilder.done();
        return builder.obj();
    }

    map< string, bson::bo > XtAgentCSVApi::makeRetData(map < string, vector< map< string, string > > > rawData)
    {
        map< string, bson::bo > ret;
        for (map < string, vector< map< string, string > > >::iterator iter = rawData.begin();
            iter != rawData.end(); ++iter)
        {
            bson::bo record = encode(iter->second);
            ret[iter->first] = record;
        }
        return ret;
    }

    void XtAgentCSVApi::loadNamePos(string line , vector<string>& headName)
    {
        vector<string> lineParm;
        split(lineParm, line, ",");
        string tmp;

        for (int i = 0; i < lineParm.size(); ++i)
        {
            string posName = lineParm[i];
            if ( i >= headName.size())
            {
                if (posName.empty())
                {
                    posName = tmp;
                }
                headName.push_back(posName);
            }
            else
            {
                headName[i] += posName;
            }
            if (!posName.empty())
            {
                tmp = posName;
            }
        }
    }

    void XtAgentCSVApi::getDataFromFile(const string& file, const int& funcNo, map < string, vector< map< string, string > > >& retData)
    {
        vector<string> dataTemp;
        if (!utils::FileHelper::open(file, dataTemp))
        {
            return;
        }
        if (!dataTemp.empty())
        {
            int headLenth(0);
            vector<string> namepos;

            if (FUND == funcNo ||\
                POSITION == funcNo)
            {
                headLenth = 2;
            }
            else
            {
                headLenth = 1;
            }

            for (int pos = 0; pos < headLenth; ++pos )
            {
                loadNamePos(dataTemp[pos] ,namepos);
            }

            for (int pos = headLenth; pos < dataTemp.size(); ++pos)
            {
                map<string, string> record;
                vector<string> lineParm;
                split(lineParm, dataTemp[pos], ",");
                if (lineParm.size() < namepos.size())
                {
                    continue;
                }
                for (int i = 0; i < namepos.size(); ++i)
                {
                    record[namepos[i]] = lineParm[i];
                }

                string AccountID = XtAgentConfig::instance()->getAccountID(record["产品名称"], record["资产单元名称"]);
                if (!AccountID.empty())
                {
                    retData[AccountID].push_back(record);
                }
            }
        }
    }
}