#include "common/Stdafx.h"
#include "log4cxx/logger.h"
#include "utils/Config.h"
#include "utils/strings.h"
#include "utils/TimeTool.h"
#include <utils/commonFunc.h>
#include "XtAgentCommon.h"
#include "XtAgentCenter.h"
#include "boost/filesystem/operations.hpp"
#include <Python.h>

void proc(const char* cfg_file)
{
    using namespace log4cxx;
    using namespace boost;
    using namespace utils;
    using namespace agent;

    // 兼容python c++读取xlsx有问题，用python实现数据转换
    Py_Initialize();

    string fileName = "config.ini";
    boost::filesystem::path filePath = boost::filesystem::absolute(fileName, boost::filesystem::current_path());
    string configFile = filePath.generic_string();
    boost::shared_ptr<Configuration> config = boost::shared_ptr<Configuration>(new Configuration(configFile.c_str()));
    config->load();

    const string logger_properties_file_path = config->read("common", "log4cxx_property_file");
    PropertyConfigurator::configure(logger_properties_file_path.c_str());

    LOG_INFO("");
    LOG_INFO("***************************************");
    LOG_INFO("***** hundsunO32Agent AGENT started ******");
    LOG_INFO("***************************************");
    LOG_INFO("");

    boost::shared_ptr<XtAgentCenter> xtagent_center = boost::shared_ptr<XtAgentCenter>(new XtAgentCenter());
    xtagent_center->init(config);
    xtagent_center->run();
}

int main(int argc, char* argv[])
{
    ::SetErrorMode(SEM_NOGPFAULTERRORBOX);

    if (argc < 2 || strncmp((const char*)argv[1], "--help", 6) == 0 || strncmp((const char*)argv[1], "-h", 2) == 0)
    {
        printf("Usage: hundsunO32Agent <config file>\n");
    }
    else
    {
        proc(argv[1]);
    }

    return 0;
}