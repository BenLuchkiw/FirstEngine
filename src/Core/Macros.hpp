#pragma once 

#ifdef MTR_ENABLED
#include "minitrace/minitrace.h"
#define FE_SCOPE_TRACE(process, name) MTR_SCOPE(process, name)
#define FE_BEGIN_TRACING(path) mtr_init(path)
#define FE_TRACING_FLUSH mtr_flush()
#define FE_END_TRACING mtr_shutdown()
#define FE_THREAD_NAME(name) MTR_META_THREAD_NAME(name)
#else
#define FE_SCOPE_TRACE(process, name)
#define FE_BEGIN_TRACING(path)
#define FE_TRACING_FLUSH
#define FE_END_TRACING
#define FE_THREAD_NAME(name)
#endif

#include "Logging/Logging.hpp"
#define FE_LOG_WARNING(condition, message)  if(condition){Logging::logCode(message, LOG_LEVEL_WARNING, __FILE__, __LINE__);}
#define FE_LOG_ERROR(condition, message)    if(condition){Logging::logCode(message, LOG_LEVEL_ERROR, __FILE__, __LINE__);}
#define FE_LOG_FATAL(condition, message)	if(condition){Logging::logCode(message, LOG_LEVEL_FATAL, __FILE__, __LINE__);}

#ifdef DEBUG
#define FE_LOG_GENERIC(condition, message)	if(condition){Logging::logCode(message, LOG_LEVEL_GENERIC);}
#define FE_LOG_INFO(condition, message)		if(condition){Logging::logCode(message, LOG_LEVEL_INFO);}
#else
#define FE_LOG_GENERIC(condition, message)
#define FE_LOG_INFO(condition, message)
#endif