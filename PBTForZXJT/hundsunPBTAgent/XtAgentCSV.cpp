#include "XtAgentCSV.h"
#include "common/log.h"
#include "bson/src/bson.h"
#include "utils/FileHelper.h"
#include "openssl/md5.h"
#include "Stock/StockDataDict.h"
#include "Stock/StockUtils.h"
#include "XtAgentEnum.h"
#include "XtAgentCommon.h"
#include "XtAgentConfig.h"
#include <string>

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

    XtAgentCSVApi::XtAgentCSVApi()
    {
    }

    XtAgentCSVApi::~XtAgentCSVApi()
    {
    }

    bool XtAgentCSVApi::getFuncMatchUnit(FuncMatchUnit& coverFuncUnit, int funcNo)
    {
        for (int i = 0; i < ARRAYLEN(ALL_FUNC_MATCH_UNITS); ++i)
        {
            if (ALL_FUNC_MATCH_UNITS[i].funcNo == funcNo)
            {
                coverFuncUnit = ALL_FUNC_MATCH_UNITS[i];
                return true;
            }
        }
        return false;
    }

    void XtAgentCSVApi::loadNamePos(string line , std::map<string , int>& name2pos)
    {
        name2pos.clear();
        vector<string> lineParm;
        split(lineParm, line, "\",\"");
        int no = 0;

        for (vector<string>::iterator iter = lineParm.begin(); iter != lineParm.end(); ++iter)
        {
            string linestr = (*iter);
            if (linestr.compare("沪深T+0交易可用") == 0)
            {
                linestr = "T+0可用";
            }
            name2pos[linestr] = no;
            no++;
        }
    }

    double XtAgentCSVApi::getPerAmount(string str)
    {
        double amount(0.0);
        try
        {
            // str格式 2842.61%
            if (!str.empty())
            {
                str = str.substr(0 ,str.length() - 1);
                amount = boost::lexical_cast<double> (str) /100;
            }
        }
        catch (const boost::bad_lexical_cast& e)
        {
            LOG_INFO(boost::format("getPerAmount %s lexical_cast error: %s") %str %e.what());
        }
        return amount;
    }

    double XtAgentCSVApi::getAmount(string str)
    {
        double amount(0.0);
        try
        {
            // 处理空窜数据
            if (!str.empty())
            {
                boost::algorithm::erase_all(str, ",");
                boost::algorithm::erase_all(str, "-");
                amount = boost::lexical_cast<double>(str);
            }
        }
        catch (const boost::bad_lexical_cast& e)
        {
            LOG_INFO(boost::format("getAmount %s lexical_cast error: %s") %str %e.what());
        }
        return amount;
    }

    string XtAgentCSVApi::getTime(string str)
    {
        if (!str.empty())
        {
            boost::algorithm::erase_all(str, "-");
            boost::algorithm::erase_all(str, ":");
        }
        return str;
    }


    void XtAgentCSVApi::genErrMsgData(const string& errMsg, bson::bo& errMsgBson)
    {
        bson::bob builder;
        builder.append("error_no", GW_ERR_PARAM);
        builder.append("error_info", errMsg);
        errMsgBson = builder.obj();
    }

    // 获取数据
    bson::bo XtAgentCSVApi::genData(vector<string>& dataFilesPath, int funcNo, string& strAccountID)
    {
        bson::bo data;
        bson::bob builder;
        int nCnt = 0;
        bson::BSONArrayBuilder arrayBuilder(builder.subarrayStart("records"));

        for (vector<string>::iterator iterFile = dataFilesPath.begin(); iterFile != dataFilesPath.end(); ++iterFile)
        {
            vector<string> dataTemp;
            if (!utils::FileHelper::open(*iterFile, dataTemp))
            {
                continue;
            }
            if (!dataTemp.empty())
            {
                // 是否放弃当前文件
                bool giveUpFile = false; 
                std::map<string , int> name2pos;
                vector< vector<string> > records; 

                for (vector<string>::iterator iter = dataTemp.begin(); iter != dataTemp.end(); ++iter)
                {
                    if (giveUpFile)
                    {
                        break;
                    }
                    string line = *iter;
                    // 是否放弃当前行
                    bool giveUp = false;
                    // 恒生数据有莫名其秒的换行。这里兼容处理下
                    while (line.at(line.size() - 1) != '"')
                    {
                        ++iter;
                        if (iter == dataTemp.end() || (*iter).at(0) == '"')
                        {
                            giveUp = true;
                            break;
                        }
                        line = line + (*iter);
                    }

                    if (giveUp)
                    {
                        LOG_ERROR(boost::format("give up data %s ") %line);
                        continue;
                    }

                    line = line.substr(1, line.size() -2);
                    if (iter == dataTemp.begin())
                    {//文件第一行是字段说明，读取当标签用,第一行默认不存在换行的情况
                        loadNamePos(line , name2pos);

                        // 校验文件是否是正常的文件，按键精灵导出可能存在内容串行的问题。]

                        switch(funcNo)
                        {
                        case XT_DATA_TYPE_LOGIN:
                        case XT_DATA_TYPE_FUND:
                            if (name2pos.find("T+0可用") == name2pos.end())
                            {
                                giveUpFile = true;
                            }
                            break;
                        case XT_DATA_TYPE_POSITION:
                            if (name2pos.find("持仓数量") == name2pos.end())
                            {
                                giveUpFile = true;
                            }
                            break;
                        case XT_DATA_TYPE_ORDER:
                            if (name2pos.find("委托状态") == name2pos.end())
                            {
                                giveUpFile = true;
                            }
                            break;
                        case XT_DATA_TYPE_BUSINESS:
                            if (name2pos.find("成交序号") == name2pos.end())
                            {
                                giveUpFile = true;
                            }
                            break;
                        }
                        continue;
                    }
                    vector<string> lineParm;
                    split(lineParm, line, "\",\"");
                    if (lineParm.size() < name2pos.size())
                    {
                        LOG_ERROR(boost::format("give up data %s ") %line);
                        continue;
                    }
                    string account = XtAgentConfig::instance()->getAccountID(lineParm[name2pos["产品名称"]], lineParm[name2pos["单元名称"]]);
                    if (strAccountID.compare(account) != 0)
                    {
                        continue;
                    }
                    ++nCnt;
                    records.push_back(lineParm);
                }

                for (vector< vector<string> >::iterator iter = records.begin(); iter != records.end(); ++iter)
                {
                    coverField(*iter, arrayBuilder, funcNo, name2pos);
                }
            }
        }

        arrayBuilder.done();

        // 登录找不到资金数据需要报错的
        if (nCnt == 0 && (funcNo == XT_DATA_TYPE_LOGIN || funcNo == XT_DATA_TYPE_FUND ))
        {
            LOG_INFO(boost::format("genData of %s or error! can not find login record!") %funcNo);
            builder.append("error_no", GW_ERR_PARAM);
            builder.append("error_info", (BF("找不到帐号[%1%]数据.") %strAccountID).str());
        }
        else
        {
            builder.append("error_no", GW_SUCCESS);
            builder.append("record_cnt", nCnt);
        }
        data = builder.obj();
        return data;
    }

    void XtAgentCSVApi::coverField(vector<string>& lineParm, bson::BSONArrayBuilder& arrayBuilder, int funcNo, std::map<string , int>& name2pos)
    {
        FuncMatchUnit coverFuncUnit;
        bool isfind = getFuncMatchUnit(coverFuncUnit, funcNo);
        bson::bob subBuilder;

        if (isfind)
        {
            const FieldMatchUnit* coverFeildUnit = coverFuncUnit.coverFields;
            int cnt = coverFuncUnit.coverCnt;

            for (int i = 0; i < cnt; ++i)
            {
                const FieldMatchUnit& fieldMatchUnit = coverFeildUnit[i];

                // 帐号id需要特殊的拼接方式
                if(fieldMatchUnit.dst.compare("accountID") == 0)
                {
                    subBuilder.append(fieldMatchUnit.dst,XtAgentConfig::instance()->getAccountID(lineParm[name2pos["产品名称"]], lineParm[name2pos["单元名称"]]));
                    continue;
                }

                else if (fieldMatchUnit.src.empty())
                {
                    switch(fieldMatchUnit.method)
                    {
                    case SWAP_STR:
                        subBuilder.append(fieldMatchUnit.dst, "");
                        break;
                    case SWAP_INT:
                        subBuilder.append(fieldMatchUnit.dst, int(0));
                        break;
                    case SWAP_DOUBLE:
                        subBuilder.append(fieldMatchUnit.dst, double(0));
                        break;
                    case SWAP_DOUBLE_PRE:
                        subBuilder.append(fieldMatchUnit.dst, double(0));
                        break;
                    default:
                        break;
                    }
                    continue;
                }

                switch(fieldMatchUnit.method)
                {
                case SWAP_STR:
                    subBuilder.append(fieldMatchUnit.dst, lineParm[name2pos[fieldMatchUnit.src]]);
                    break;
                case SWAP_INT:
                    subBuilder.append(fieldMatchUnit.dst, int(getAmount(lineParm[name2pos[fieldMatchUnit.src]])));
                    break;
                case SWAP_DOUBLE:
                    subBuilder.append(fieldMatchUnit.dst, getAmount(lineParm[name2pos[fieldMatchUnit.src]]));
                    break;
                case SWAP_DOUBLE_PRE:
                    subBuilder.append(fieldMatchUnit.dst, getPerAmount(lineParm[name2pos[fieldMatchUnit.src]]));
                    break;
                case SWAP_TIME:
                    subBuilder.append(fieldMatchUnit.dst, getTime(lineParm[name2pos[fieldMatchUnit.src]]));
                    break;
                default:
                    break;
                }
            }
            arrayBuilder.append(subBuilder.obj());
        }
    }

}