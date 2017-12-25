#ifndef __GATEWAY_COMMON_H__
#define __GATEWAY_COMMON_H__

#define LOG_DEBUG(log)   LOG4CXX_DEBUG( log4cxx::Logger::getRootLogger(), log )
#define LOG_TRACE(log)   LOG4CXX_TRACE( log4cxx::Logger::getRootLogger(), log )
#define LOG_INFO(log)    LOG4CXX_INFO( log4cxx::Logger::getRootLogger(), log )
#define LOG_WARN(log)    LOG4CXX_WARN( log4cxx::Logger::getRootLogger(), log )

#ifdef LOG_DAILY_SIZE_ROLL
#define LOG_ERROR(log)   LOG4CXX_ERROR( log4cxx::Logger::getLogger("errorLogger"), log )
#else
#define LOG_ERROR(log)   LOG4CXX_ERROR( log4cxx::Logger::getRootLogger(), log )
#endif

#define LOG_FATAL(log)   LOG4CXX_FATAL( log4cxx::Logger::getRootLogger(), log )

#endif