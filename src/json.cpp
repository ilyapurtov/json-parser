
#include "json.h"

namespace json {
  value::Any Object::get(const std::string& key) const {
    if (data.contains(key)) return data.at(key);
    return value::Undefined{};
  }

  bool Object::empty() const {
    return data.empty();
  }

  void Object::add(const std::string& key, const value::Any& v) {
    data.insert_or_assign(key, v);
  }

  void Object::remove(const std::string& key) {
    data.erase(key);
  }

  void print(std::ostream& stream, const Object& obj, int level) {
    stream << "{\n";
    bool first = true;
    const std::string margin(level * 2, ' ');
    for (const auto& [key, value] : obj.data) {
      if (first) first = false;
      else stream << ",\n";
      stream << margin;
      stream << "\"" << key << "\"" << ": ";
      if (auto o = std::get_if<Object>(&value)) {
        print(stream, *o, level + 1);
      } else {
        stream << value;
      }
    }
    stream << "\n";
    if (level > 1) {
      stream << std::string((level - 1) * 2, ' ');
    }
    stream << "}";
  }

};