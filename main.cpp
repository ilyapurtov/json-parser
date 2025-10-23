#include <fstream>
#include <iostream>

#include "json.h"
#include "parser.h"

int main() {
  std::ifstream stream("test.json");
  json::Object obj = json::parser::parse(stream);
  std::cout << obj.get("married") << std::endl;
system("pause");
  return 0;
}
