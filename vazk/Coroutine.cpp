#include "Coroutine.hpp"

namespace
{
  struct CoroutineWait
  {
    float mCurrentTime;
    float mTimeToStart;
    std::function<void()> mCallBack;
  };

  std::vector< CoroutineWait > sHoldersWait;
}

namespace Coroutine
{
  void update(float dt)
  {
    auto cw = std::begin(sHoldersWait);
    while (cw != std::end(sHoldersWait))
    {
      cw->mCurrentTime += dt;
      if (cw->mCurrentTime > cw->mTimeToStart)
      {
        cw->mCallBack();
        cw = sHoldersWait.erase(cw);
      }
      else
        ++cw;
    }
  }

  void Wait(float _timeToStart, std::function<void()> _fnc)
  {
    sHoldersWait.push_back({ 0.0f, _timeToStart, _fnc });
  }
}