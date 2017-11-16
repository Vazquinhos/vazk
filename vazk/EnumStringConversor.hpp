#pragma once

// Original version: http://www.codeproject.com/Articles/42035/Enum-to-String-and-Vice-Versa-in-C> from Francis Xavier Joseph Pulikotil

#include <unordered_map>
#include <array>
#include <cassert>

// Helper macros
#define Begin_Enum_String(EnumerationName)                                      \
    template <> struct EnumString<EnumerationName> :                            \
        public EnumStringBase< EnumString<EnumerationName>, EnumerationName >   \
    {                                                                           \
        static void RegisterEnumerators()

#define Enum_String(EnumeratorName)                                             \
            RegisterEnumerator( EnumeratorName, #EnumeratorName );

#define Register_Enum_String(EnumeratorName , EnumeratorString )                \
            RegisterEnumerator( EnumeratorName, EnumeratorString );

#define End_Enum_String                                                         \
    }                                                                           \

template <class DerivedType, class EnumType>
class EnumStringBase
{

private:
  EnumStringBase(const EnumStringBase&) = delete;
  EnumStringBase& operator=(const EnumStringBase& other) = delete;

  static std::unordered_map<std::string, EnumType> &GetMap()
  {
    static std::unordered_map<std::string, EnumType> assocMap;
    static bool sInited = false;
    if (sInited == false)
    {
      sInited = true;
      DerivedType::RegisterEnumerators();
      assert(!assocMap.empty());
    }
    return assocMap;
  }

  static std::vector<std::string> &GetVector()
  {
    static std::vector<std::string> assocVector;
    static bool sInited = false;
    if (sInited == false)
    {
      sInited = true;
      assocVector.resize(static_cast<size_t>(EnumType::MAX));
      DerivedType::RegisterEnumerators();
      assert(!assocVector.empty());
    }
    return assocVector;
  }

protected:
  EnumStringBase() = default;
  virtual ~EnumStringBase() = default;

  static void RegisterEnumerator(const EnumType e, const std::string &eStr)
  {
    GetMap()[eStr] = e;
    GetVector()[static_cast<size_t>(e)] = eStr;
  }

public:
  static const std::string & asString(const EnumType e)
  {
    return GetVector()[static_cast<size_t>(e)];
  }

  static const EnumType asEnum(const std::string &str)
  {
    std::unordered_map<std::string, EnumType>::const_iterator itr(GetMap().find(str));
    return (itr == GetMap().end()) ? EnumType::MAX : itr->second;
  }
};

template <class EnumType>
struct EnumString : public EnumStringBase< EnumString<EnumType>, EnumType >
{
  static void RegisterEnumerators();
};