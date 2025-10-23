#pragma once
#include <ostream>
#include <string>
#include <unordered_map>
#include <variant>

#include "json.h"

namespace json {
  class Object;
}

namespace json {

  void print(std::ostream& stream, const Object& obj, int level = 1);

  namespace value {
    struct Undefined {
    };

    struct Null {
    };

    using Any = std::variant<Undefined, Null, std::string, int, bool, Object>;
  }

  class Object {
  public:
    value::Any get(const std::string& key);

    void add(const std::string& key, const value::Any& v);

    void remove(const std::string& key);

    friend void print(std::ostream&, const Object&, int);

  private:
    std::unordered_map<std::string, value::Any> data;
  };
}
inline std::ostream& operator <<(std::ostream& stream, const json::Object& obj) {
  json::print(stream, obj, 1);
  return stream;
}

inline std::ostream& operator <<(std::ostream& stream, const json::value::Any& v) {
  if (std::holds_alternative<json::value::Undefined>(v)) {
    stream << "{undefined}";
  } else if (std::holds_alternative<std::string>(v)) {
    stream << "\"" << std::get<std::string>(v) << "\"";
  } else if (std::holds_alternative<int>(v)) {
    stream << std::get<int>(v);
  } else if (std::holds_alternative<json::Object>(v)) {
    stream << std::get<json::Object>(v);
  } else if (std::holds_alternative<json::value::Null>(v)) {
    stream << "null";
  } else if (std::holds_alternative<bool>(v)) {
    bool b = std::get<bool>(v);
    stream << (b ? "true" : "false");
  }
  return stream;
}
