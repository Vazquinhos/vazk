#include "Logger.hpp"

#include "EnumStringConversor.hpp"

#include <cstdarg>

namespace Logger
{
  namespace
  {
    std::function<void(Severity, const std::string&)> sTraceFunction;

    Begin_Enum_String(Logger::Severity)
    {
      Register_Enum_String(Logger::Severity::eFatal, "Fatal");
      Register_Enum_String(Logger::Severity::eError, "Error");
      Register_Enum_String(Logger::Severity::eWarning, "Warning");
      Register_Enum_String(Logger::Severity::eInfo, "Info");
    }
    End_Enum_String;
  }

  void Trace(Severity _severity, const char* _file, uint32_t _line, const std::string& _msg)
  {
    std::string lFullMsg = std::string("[") + EnumString<Logger::Severity>::asString(_severity) + std::string("]");
    lFullMsg += EnumString<Logger::Severity>::asString(_severity) + std::string("]");
    sTraceFunction(_severity, lFullMsg);
  }

  void BindOutputFunction(std::function<void(Severity, const std::string&)> _fun)
  {
    sTraceFunction = _fun;
  }
}