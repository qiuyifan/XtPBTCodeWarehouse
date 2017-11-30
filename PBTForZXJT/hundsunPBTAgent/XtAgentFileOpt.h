#ifndef __XT_AGNET_FILE_OPT_HPP__
#define __XT_AGNET_FILE_OPT_HPP__

#include "common/Stdafx.h"
#include "utils/FileHelper.h"
#include "utils/TimeTool.h"
#include <io.h>


namespace agent
{
    class XtAgentFileOpt
    {
    public:
        static string getFormatData()
        {
            time_t nNow = time(NULL);
            r_int32 dt = utils::d8_secondToDate(nNow);
            string strDate = (boost::format("%08d") % dt).str();
            return strDate;
        }

        // 判断文件或文件夹是否存在（其实是访问权限判断）
        static bool dirExists(const std::string& dirName_in)  
        {
            int ftyp = _access(dirName_in.c_str(), 0);  

            if (0 == ftyp)  
                return true;
            else   
                return false; 
        } 

        /**
        * getFilePaths
        * @brief    获取目录下所有带文件后缀的文件列表
        * @param    suffix 文件后缀 ， 是否添加日期后缀
        * @return   vector<string> 文件列表
        */
        static vector<string> getFilePaths(const string& suffix, const string& filePath, bool addDate = false)
        {
            string fileSuffix("");
            if (addDate)
            {
                fileSuffix += "_" + getFormatData() ;
            }
            fileSuffix += suffix;

            // 判断是否有访问文件夹权限
            if(!dirExists(filePath))
            {
                throw(string("无法访问文件夹: ") + filePath);
            }

            // 获取路径下所有含有后缀的文件
            vector<string> ret;
            //文件句柄  
            long hFile   =   0;
            //文件信息  
            struct _finddata_t fileinfo;
            string pathName;
            if ((hFile = _findfirst(pathName.assign(filePath).append("\\*").c_str(), &fileinfo)) == -1) 
            {//没有找到文件，返回
                return ret;
            }
            do {
                // 是文件且文件名包含后缀str，添加到dataFilesPath
                string filestr = fileinfo.name;
                if(filestr.find(fileSuffix) != string::npos)
                {
                    ret.push_back(filePath + filestr);
                }
            } while (_findnext(hFile, &fileinfo) == 0);
            _findclose(hFile);
            if (ret.empty())
            {
                throw((BF("找不到文件: %1% *%2%") %filePath %fileSuffix).str());
            }
            return ret;
        }


         /**
        * getFileUpdateTime
        * @brief    获取目录下所有带文件后缀的更新时间
        * @param    suffix 文件后缀 ， 是否添加日期后缀
        * @return   map<string, r_int64> 文件列表以及更新时间
        */
        static map<string, r_int64> getFileUpdateTime(const string& suffix, const string& filePath)
        {
            string fileSuffix("");
            fileSuffix += suffix;

            // 判断是否有访问文件夹权限
            if(!dirExists(filePath))
            {
                throw(string("无法访问文件夹: ") + filePath);
            }

            // 获取路径下所有含有后缀的文件
            map<string, r_int64> ret;
            //文件句柄  
            long hFile   =   0;
            //文件信息  
            struct _finddata_t fileinfo;
            string pathName;
            if ((hFile = _findfirst(pathName.assign(filePath).append("\\*").c_str(), &fileinfo)) == -1) 
            {//没有找到文件，返回
                return ret;
            }
            do {
                // 是文件且文件名包含后缀str，添加到dataFilesPath
                string filestr = fileinfo.name;
                if(filestr.find(fileSuffix) != string::npos)
                {
                    ret[filePath + "\\" + filestr] = fileinfo.time_write > 0 ? fileinfo.time_write : fileinfo.time_create;
                }
            } while (_findnext(hFile, &fileinfo) == 0);
            _findclose(hFile);

            return ret;
        }
    };

}

#endif