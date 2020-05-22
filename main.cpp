#include <iostream>

class Test {
 public:
  Test() : m_data(0) {}
  Test(const Test&& rhs) {
    std::cout << "Right side value Copy Construct" << std::endl;
    std::cout << "m_data : " << rhs.m_data << std::endl;
    std::cout << "address : " << &rhs << " / " << &(rhs.m_data) << std::endl;

    m_data = rhs.getData();
  }
  ~Test() = default;
  
  void setData(int data) { m_data = data; }
  int getData() const { return m_data; }

 private:
  int m_data;
};

const Test&& setTest(int data) {
  Test test;
  test.setData(data);
  std::cout << "m_data : " << test.getData() << std::endl;
  std::cout << "address : " << &test << std::endl;

  return std::move(test);
}

int main() {
  std::cout << "Hello World!" << std::endl;
  Test test (setTest(10));

  std::cout << test.getData() << std::endl;
}
