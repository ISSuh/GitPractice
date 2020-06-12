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

    template <class... Args>
    struct type_list {
      template <std::size_t N>
      using type = typename std::tuple_element<N, std::tuple<Args...>>::type;
    };
}

template < typename... Ts>
class Action {
 public:
    template <typename F, typename... Args>
    Action(F&& func, Args&&... args) : f(std::forward<F>(func)),
                                       args(std::forward<Args>(args)...) {}

    template <typename... Args, int... Is>
    void func(std::tuple<Args...>& tup, helper::index<Is...>) {
        f(std::get<Is>(tup)...);
    }

    template <typename... Args>
    void func(std::tuple<Args...>& tup) {
        func(tup, helper::gen_seq<sizeof...(Args)>{});
    }

    void act() {
        func(args);
    }

    int argCount() const {
      std::cout << std::tuple_size<std::tuple<Ts...>>::value << std::endl;
    }

 private:
  std::tuple<Ts...> args;
};

class Route {
 public:
  Route();
  ~Route();

  template<typename F>
  void bindFunction(const std::string& name, F&& f) {
    registFunction(name, std::forward<F>(f));
  }

 private:
  template<typename F, >
  void registFunction(const std::string& name, F&& f) {
    m_funcMap[name] = {f}
  }

  template<typename F, typename ...Args>
  void caller(F&& f, Args&& ...args) {
    f(std::forward<f>(f)(std::forward<Args>(args)));
  }

 private:
  std::map<std::string, std::function<void()>> m_funcMap;
}

template <typename F, typename... Args>
Action<Args...> make_action(F&& f, Args&&... args) {
    return Action<Args...>(std::forward<F>(f), std::forward<Args>(args)...);
}

int main() {
  auto add = make_action([](int a, int b, float c){ std::cout << a + b + c; }, 2, 2, 3.5);
  add.argCount();
  
  auto sub = make_action([](int a, int b){ std::cout << a - b; }, 2, 2);
  sub.argCount();

  add.act();
  sub.act();

  return 0;
}
