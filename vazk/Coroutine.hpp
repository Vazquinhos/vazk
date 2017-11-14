#pragma once

#include <vector>
#include <functional>

namespace Coroutine
{
  void update(float _dt);
  void Wait(float _timeToStart, std::function<void()> _fnc);
};