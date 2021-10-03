#pragma once 

#ifdef MTR_ENABLED
#include "minitrace/minitrace.h"
#define FE_SCOPE_TRACE(process, name) MTR_SCOPE(process, name);
#define FE_BEGIN_TRACING(path) mtr_init(path);
#define FE_TRACING_FLUSH mtr_flush();
#define FE_END_TRACING mtr_shutdown();
#define FE_THREAD_NAME(name) MTR_META_THREAD_NAME(name);
#else
#define FE_SCOPE_TRACE(process, name)
#define FE_BEGIN_TRACING(path)
#define FE_TRACING_FLUSH
#define FE_END_TRACING
#define FE_THREAD_NAME(name)
#endif

#define FE_LOG_VERBOSE(message) std::cout << message << std::endl;
#define FE_LOG_WARNING(condition, message) if(condition){std::cout << "Warning at " << __FILE__ ", on line: " << __LINE__ << ". " << message << std::endl;}
#define FE_LOG_ERROR(condition, message)   if(condition){std::cout << "Error at "   << __FILE__ ", on line: " << __LINE__ << ". " << message << std::endl;}