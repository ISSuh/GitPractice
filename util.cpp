#include <map>

class B {
 public:
  B() { m[1] = 1; }
  ~B() = default;

  int getVal(int i) { return m[i]; }
  
 private:
  std::map<int, int> m;
};
