#include "parser.h"

#include "exceptions.h"

namespace json::parser {
  Object parse(const std::string& rawData) {
    std::istringstream s(rawData);
    Parser parser(s);
    return parser.parse();
  }

  Object parse(std::istream& stream) {
    Parser parser(stream);
    return parser.parse();
  }

  Parser::Parser(std::istream& stream): stream(&stream) {}

  Object Parser::parse() {
    get();
    if (c == '{') {
      get();
      return eatObject();
    }
    throw UnexpectedTokenError(line, c);
  }

  Object Parser::eatObject() {
    Object obj;
    std::string key;
    while (c != '}') {
      if (c == '"') {
        get();
        key = eatString();
      } else if (c == ':') {
        if (!key.empty()) {
          get();
          value::Any value = parseValue();
          obj.add(key, value);
        } else {
          throw UnexpectedTokenError(line, c);
        }
      } else if (c == ',') {
        get();
        key.clear();
      } else if (isspace(c)) {
        if (c == '\n') line++;
        get();
      } else {
        throw UnexpectedTokenError(line, c);
      }
    }
    get();
    return obj;
  }

  value::Any Parser::parseValue() {
    while (isspace(c)) {
      get();
    }
    if (c == '"') {
      get();
      return eatString();
    }
    if (c == '{') {
      get();
      return eatObject();
    }
    if (isalpha(c)) {
      std::string keyword = eatKeyword();
      if (keyword == "true") return true;
      if (keyword == "false") return false;
      if (keyword == "null") return value::Null{};
    }
    if (isdigit(c)) {
      return eatNumber();
    }
    throw UnexpectedTokenError(line, c);
  }


  std::string Parser::eatString() {
    std::string value;
    while (c != '"') {
      value += c;
      get();
    }
    get();
    return value;
  }

  std::string Parser::eatKeyword() {
    std::string keyword;
    while (isalpha(c)) {
      keyword += c;
      get();
    }
    return keyword;
  }

  int Parser::eatNumber() {
    int n = 0;
    while (isdigit(c)) {
      n = n * 10 + (c - '0');
      get();
    }
    return n;
  }


  void Parser::get() {
    if (stream->eof()) {
      throw UnexpectedEofError(line);
    }
    c = static_cast<char>(stream->get());
  }

  char Parser::peek() {
    if (stream->eof()) {
      throw UnexpectedEofError(line);
    }
    return static_cast<char>(stream->peek());
  }
}
