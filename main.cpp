#include <iostream>
#include <map>
#include <functional>
#include <tuple>

void HelloWorld() {
  std::cout << "HelloWorld" << std::endl;
}

void printArg(const std::string& arg) {
  std::cout << arg << std::endl;
}

int sum(int a, int b) {
  return a + b;
}

class FunctionMap {
 public:
  FunctionMap() = default;
  ~FunctionMap() = default;

  template<typename F>
  void registFunction(const std::string& name, F func) {
    m_functionMap.insert(
        td::make_pair(
          name, func));
  }

  void callFunction(const std::string& name) {}

 private:
  std::map<std::string, std::function<()>> m_functionMap;
};

int main() {
  FunctionMap funcMap;

  funcMap.registFunction("HelloWorld", HelloWorld);
  funcMap.registFunction("printArg", printArg);
  funcMap.registFunction("sum", sum);

  funcMap["HelloWorld"]();
  funcMap["printArg"]("Hello!!");
  funcMap["sum"](1, 3);

  return 0;
}
