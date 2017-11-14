#include <stdio.h>
#include <iostream>

#include <String.hpp>
#include <Singleton.hpp>
#include <ObjectFactory.hpp>

class A : public Singleton< A >
{
public:
  A() = default;
  virtual ~A() = default;
  int i;
};


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