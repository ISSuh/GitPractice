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

namespace helper {
    template <int... Is>
    struct index {};

    template <int N, int... Is>
    struct gen_seq : gen_seq<N - 1, N - 1, Is...> {};

    template <int... Is>
    struct gen_seq<0, Is...> : index<Is...> {};
}

class Action {
 public:
    template <typename F>
    explicit Action(F&& func) : f(std::forward<F>(func)) {}

    template <typename... Args, int... Is>
    void func(std::tuple<Args...>& tup, helper::index<Is...>) {
        f(std::get<Is>(tup)...);
    }

    template <typename... Args>
    void func(const std::tuple<Args...>& tup) {
        func(tup, helper::gen_seq<sizeof...(Args)>{});
    }

    template<typename... Args>
    void act(Args&&... args) {
        std::tuple<Args...> params(std::forward<Args>(args)...);

        func(params);
    }
};

template <typename F>
Action make_action(F&& f) {
    return Action (std::forward<F>(f));
}

class Route {
 public:
  Route();
  ~Route();

  template<typename F>
  void bindFunction(const std::string& name, F&& f) {
    registFunction(name, std::forward<F>(f));
  }

  template<typename ...Args>
  void call(const std::string& name, Args&& ...args) {
    m_funcMap[name](std::forward<Args>(args));
  }

 private:
  template<typename F>
  struct invoker {
    template<typename... Args>
    void caller(F f, Args&& ...args) {
      f(std::forward<f>(f)(std::forward<Args>(args)));
    }
  };

 private:
  template<typename F>
  void registFunction(const std::string& name, F&& f) {
    m_funcMap[name] = {  }
  }

 private:
  std::map<std::string, std::function<void()>> m_funcMap;
};

int main() {
  Route r;
  r.bindFunction("HelloWorld", HelloWorld);
  r.bindFunction("printArg", printArg);
  r.bindFunction("sum", sum);

  r.call("HelloWorld");
  r.call("printArg", "TEST");
  r.call("sum", 1, 1);

  return 0;
}
