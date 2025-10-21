#pragma once
#include <ostream>
#include <string>
#include <unordered_map>
#include <variant>

namespace json {
  class Object;

  namespace value {
    struct Undefined {};
    using Any = std::variant<Undefined, std::string, int, Object>;
  }


  class Object {
  public:
    value::Any get(const std::string& key);
    void add(const std::string& key, const value::Any& v);
    void remove(const std::string& key);
  private:
    std::unordered_map<std::string, value::Any> data;
  };

}

inline std::ostream& operator << (std::ostream& stream, const json::value::Any& v) {
  if (std::holds_alternative<json::value::Undefined>(v)) {
    stream << "[undefined]";
  } else if (std::holds_alternative<std::string>(v)) {
    stream << std::get<std::string>(v);
  } else if (std::holds_alternative<int>(v)) {
    stream << std::get<int>(v);
  } else if (std::holds_alternative<json::Object>(v)) {
    stream << "[object]";
  }
  return stream;
}