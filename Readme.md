VazK
-------------
This is a base library to be used across multiple projects.

### Singleton
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

### Simple Coroutine

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