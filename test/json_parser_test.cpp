#include <gtest/gtest.h>
#include <parser.h>

#include "exceptions.h"


TEST(PARSER_TEST, EMPTY_JSON) {
  const std::string data = R"({})";
  json::Object parsed = json::parser::parse(data);
  ASSERT_TRUE(parsed.empty());
}

TEST(PARSER_TEST, NORMAL_JSON) {
  const std::string data = R"({"name": "Ilya", "age": 19, "married": false})";
  json::Object parsed = json::parser::parse(data);

  auto name = parsed.get("name");
  ASSERT_TRUE(std::holds_alternative<std::string>(name));
  EXPECT_EQ(std::get<std::string>(name), "Ilya");

  auto age = parsed.get("age");
  ASSERT_TRUE(std::holds_alternative<int>(age));
  EXPECT_EQ(std::get<int>(age), 19);

  auto married = parsed.get("married");
  ASSERT_TRUE(std::holds_alternative<bool>(married));
  EXPECT_EQ(std::get<bool>(married), false);
}

TEST(PARSER_TEST, NESTED_SPACED_JSON) {
  const std::string data = R"({  "we": {"are": "the champions",   "null_field":  null }  })";
  json::Object parsed = json::parser::parse(data);
  auto res = parsed.get("we");
  ASSERT_TRUE(std::holds_alternative<json::Object>(res));

  auto obj = std::get<json::Object>(res);

  auto are = obj.get("are");
  ASSERT_TRUE(std::holds_alternative<std::string>(are));
  EXPECT_EQ(std::get<std::string>(are), "the champions");

  auto null_field = obj.get("null_field");
  ASSERT_TRUE(std::holds_alternative<json::value::Null>(null_field));
}

TEST(PARSER_TEST, INVALID_JSON) {
  const std::string data = R"({"maim": "me",,})";
  ASSERT_THROW(json::parser::parse(data), json::parser::UnexpectedTokenError);
}

TEST(PARSER_TEST, INVALID_JSON2) {
  const std::string data = R"({)";
  ASSERT_THROW(json::parser::parse(data), json::parser::UnexpectedTokenError);
}