#pragma once

#include <chrono>
class Timer
{
public:
  Timer()
    : start( std::chrono::system_clock::now() )
    , dt(0.0f)
  {

  }
  virtual ~Timer() = default;

  void update()
  {
    end = std::chrono::system_clock::now();
    dt = (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) * 0.001f;
    start = end;
  }

  float deltaTime()
  {
    return dt;
  }

private:
  std::chrono::time_point<std::chrono::system_clock> start, end;
  float dt;
};
