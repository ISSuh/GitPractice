#include <map>

class A {
 public:
  A() { m[1] = 1; }
  ~A() = default;

  int getVal(int i) { return m[i]; }
  
 private:
  std::map<int, int> m;
};
