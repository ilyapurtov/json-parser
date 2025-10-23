#pragma once
#include <exception>
#include <format>

namespace json::parser {
  class UnexpectedTokenError : public std::exception {
  public:
    UnexpectedTokenError(int line, char token) : message(std::format("Unexpected token {} at line {}", token, line)) {
    }

    [[nodiscard]] const char* what() const noexcept override {
      return message.c_str();
    }

  private:
    std::string message;
  };

  class UnexpectedEofError : public std::exception {
  public:
    explicit UnexpectedEofError(int line) : message(std::format("Unexpected EOF at line {}", line)) {
    }

    [[nodiscard]] const char* what() const noexcept override {
      return message.c_str();
    }

  private:
    std::string message;
  };
}
