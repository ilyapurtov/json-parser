#pragma once
#include <format>

#include "json.h"
#include <sstream>


namespace json::parser {
  Object parse(const std::string& rawData);

  Object parse(std::istream& stream);

  class Parser {
  public:
    Object parse();

    explicit Parser(std::istream& stream);

  private:
    std::istream* stream;
    int line = 1;
    char c{};

    value::Any parseValue();

    std::string eatString();

    int eatNumber();

    Object eatObject();

    void get();

    char peek();
  };
}
