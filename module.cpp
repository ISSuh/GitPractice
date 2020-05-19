#include <map>

class A {
 public:
  A() { m[1] = 1; }

  int getVal(int i) { return m[i]; }
  
 private:
  std::map<int, int> m;
}
