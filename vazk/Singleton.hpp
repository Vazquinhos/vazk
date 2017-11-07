#pragma once

#include <memory>

template<typename T>
class Singleton
{
public:
  static T& getInstance()
  {
    static const std::unique_ptr<T> sObjectInstance = std::make_unique<T>();
    return *sObjectInstance;
  }
protected:
  Singleton() = default;
  virtual ~Singleton() = default;

private:
  Singleton(const Singleton&) = delete;
  Singleton& operator= (const Singleton) = delete;
};