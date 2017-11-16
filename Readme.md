VazK
-------------
This is a base library to be used across multiple projects.

### Singleton

Allows easily creating singletons extending from the class Singleton

```
#include <Singleton.hpp>
class A : public Singleton< A >
{
public:
  A() = default;
  virtual ~A() = default;
  int i;
};

int main()
{
  // Singleton
  A& a = A::getInstance();
  a.i = 0;
  a.i++;
  return 0;
}
```
### Object factory

Allows creating objects by an id as string

```
#include <ObjectFactory.hpp>
class RenderTask : public std::enable_shared_from_this<RenderTask>
{
public:
  RenderTask() = default;
  virtual ~RenderTask() = default;

  virtual void Execute() = 0;
};

class BeginRenderTask : public RenderTask
{
public:
  BeginRenderTask() = default;
  virtual ~BeginRenderTask() = default;

  virtual void Execute()
  {
    std::cout << "Begin Render" << std::endl;
  }
};

class ClearRenderTargetTask : public RenderTask
{
public:
  struct SClearRTParams
  {
    float color[3];
    bool  clearDepht;
    float depth;
    bool  clearStencil;
    float stencil;
  };
public:
  ClearRenderTargetTask() = default;
  virtual ~ClearRenderTargetTask() = default;

  void Init(const SClearRTParams&)
  {
    // Init...
  }

  virtual void Execute()
  {
    // Apply the config of the rendering params
  }
};

class EndRenderTask : public RenderTask
{
public:
  EndRenderTask() = default;
  virtual ~EndRenderTask() = default;

  virtual void Execute()
  {

  }
};

class RenderTaskFactory : public ObjectFactory< RenderTask >, public Singleton< RenderTaskFactory >
{
public:
  RenderTaskFactory()
  {
    registerCreator<BeginRenderTask>();
    registerCreator<EndRenderTask>();
    registerCreator<ClearRenderTargetTask>();
  }

  virtual ~RenderTaskFactory() = default;
};

int main()
{
  static const std::string BeginTaskId("class BeginRenderTask");
  std::shared_ptr< RenderTask > beginTask = RenderTaskFactory::getInstance().createObject(BeginTaskId);
  beginTask->Execute();
  return 0;
}
```

### Timer

Timer for rendering loops, or get the elapsed time

```
#include <Timer.hpp>
#include <thread>
int main()
{
  bool exit = false;

  Timer timer;
  while (!exit)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
    timer.update();
    std::cout << timer.deltaTime() << std::endl;
  }
  return 0;
}
```

### Enum To String / String To Enum

Having an enum like this:

```
enum class Severity
  {
    eInfo = 0,
    eWarning,
    eError,
    eFatal,
    MAX
  };
```

We can register its conversion to string, globaly:

```
#include <EnumStringConversor.hpp>

Begin_Enum_String(Logger::Severity)
{
  Register_Enum_String(Logger::Severity::eFatal, "Fatal");
  Register_Enum_String(Logger::Severity::eError, "Error");
  Register_Enum_String(Logger::Severity::eWarning, "Warning");
  Register_Enum_String(Logger::Severity::eInfo, "Info");
}
End_Enum_String;

```

And afterwards use it in any piece of code that we need a conversion to string, or string to enum

```
int main()
{
  std::cout << "Enum as Strings" << std::endl;
  std::vector< std::string > enumAsString;
  for (size_t i = 0; i < static_cast<size_t>(Logger::Severity::MAX); ++i)
  {
    enumAsString.push_back(EnumString<Logger::Severity>::asString(static_cast<Logger::Severity>(i)));
    std::cout << enumAsString[i] << std::endl;
  }

  std::cout << "Strings as Enums" << std::endl;
  for (size_t i = 0; i < static_cast<size_t>(Logger::Severity::MAX); ++i)
  {
    Logger::Severity enumSeverity = EnumString<Logger::Severity>::asEnum(enumAsString[i]);
    std::cout << EnumString<Logger::Severity>::asString(static_cast<Logger::Severity>(enumSeverity)) << std::endl;
  }
  return 0;
}

```

### Logging

Api to log errors, info, warnings in our apps. You need to register the output function that you want to be called. 

Note: ENABLE_LOGGING macro is needed to enable logging functions

```
#include <Logger.hpp>
int main()
{

  Logger::BindOutputFunction
  (
    [](Logger::Severity _e, const std::string& _msg)
    {
      if (_e == Logger::Severity::eError)
        std::cerr << _msg << std::endl;
      else
        std::cout << _msg << std::endl;
    }
  );

  Log_Error("error!!!!!");
  return 0;
}
```

### Simple Coroutine

Actualy, is not a couroutine system with threads or forks, but it allow us to call functions when a time is passed

```
#include <Timer.hpp>
#include <Coroutine.hpp>
#include <thread>
int main()
{
  bool exit = false;

  Timer timer;
  Coroutine::Wait(20.0f, [] {std::cout << "elapsed time 20 seconds";});
  while (!exit)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
    timer.update();
    Coroutine::update(timer.deltaTime());
  }
  return 0;
}
```