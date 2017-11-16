#pragma once

#include <vector>
#include <functional>
#include <cstdarg>

namespace Logger
{
  enum class Severity
  {
    eInfo = 0,
    eWarning,
    eError,
    eFatal,
    MAX
  };

  void Trace(Severity _severity, const char* _file, uint32_t _line, const std::string& _msg);
  void BindOutputFunction(std::function<void(Severity, const std::string&)> _fun);
};

#ifdef ENABLE_LOGGING

#define Log_Error(msg) Logger::Trace(Logger::Severity::eError, __FILE__, __LINE__, msg);
#define Log_Warning(msg) Logger::Trace(Logger::Severity::eWarning, __FILE__, __LINE__, msg);
#define Log_Info(msg) Logger::Trace(Logger::Severity::eInfo, __FILE__, __LINE__, msg);
#define Log_Fatal(msg) Logger::Trace(Logger::Severity::eFatal, __FILE__, __LINE__, msg);

#else

#define Log_Error(msg){}
#define Log_Warning(msg){}
#define Log_Info(msg){}
#define Log_Fatal(msg){}

#endif //  

