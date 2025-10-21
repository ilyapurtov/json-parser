
#include "json.h"

namespace json {
  value::Any Object::get(const std::string& key) {
    if (data.contains(key)) return data[key];
    return value::Undefined{};
  }

  void Object::add(const std::string& key, const value::Any& v) {
    data.insert_or_assign(key, v);
  }

  void Object::remove(const std::string& key) {
    data.erase(key);
  }

};