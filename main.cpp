#include <iostream>
#include <map>
#include <functional>
class Test {
 public:
  Test() : m_data(0) {
    registEvent();
  }
  ~Test() = default;

  void selectEvent(const std::string& b) {
    m_eventMap[b](*this, b, "get");
  }

 private:
  void registEvent() {
    m_eventMap = {
      {"1", &Test::event1},
      {"2", &Test::event2}
    };
  }

  void event1(const std::string& a, const std::string& b) {
    std::cout << "event1 : " <<  a << " / " << b << std::endl;
  }

  void event2(const std::string& a, const std::string& b) {
    std::cout << "event2 : " <<  a << " / " << b << std::endl;
  }

 private:
  std::map<std::string, std::function<void(Test&, const std::string&, const std::string&)>> m_eventMap;
  int m_data;
};


int main() {
  std::cout << "Hello World! 2" << std::endl;
  Test test;

  test.selectEvent("1");
  test.selectEvent("2");
}
