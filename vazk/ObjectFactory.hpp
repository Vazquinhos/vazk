#pragma once

#include <memory>
#include <map>
#include <functional>

template<typename Base>
class ObjectFactory
{
public:
  ObjectFactory() = default;
  ~ObjectFactory() = default;
  {
    return mCreators[_creationId]();
  }

  template <typename Derived>
  {
    static_assert(std::is_base_of<Base, Derived>::value, "Invalid class");
    mCreators[typeid(Derived).name()] = []() { return std::make_shared<Derived>(); };
  }

private:
  ObjectFactory(const ObjectFactory&) = delete;
  ObjectFactory& operator= (const ObjectFactory) = delete;
  std::map < const std::string, std::function<std::shared_ptr<Base>()>> mCreators;
};
