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

#include <Logger.hpp>
#include <string>
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