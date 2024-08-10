
#include <functional>

#include "example_lambda.h"

#include "logger.h"

namespace cc::action::example_lambda {

  void example1() {

    std::function<int(int x)> f1a = [](int x) { return x * 2; };

    auto f1b = []{ return 10; };

    LOGINFO("f1a: ", f1a(1));

    LOGINFO("f1b: ", f1b());
  }

  class c2 {

  public:

    int f(int x) {

      return x*3;
    }
  };

  void example2() {

    std::unique_ptr<c2> c(std::make_unique<c2>());

    std::function<int(int x)> f2 = [&c](int i) -> int { return c->f(i); };

    auto v2 = f2(2);

    LOGINFO("v2: ", v2);
  }

  void example3() {

    std::array<int, 5> data { 4, 5, 3, 1, 2 };

    std::ranges::sort(data, [](int a, int b) { return a > b; } );

    std::ostringstream os;

    os << "{";

    std::for_each(data.begin(), data.end(), [&os](int i) { os << " " << i; } );

    os << " }";

    LOGINFO("os: ", os.str());
  }

  bool examples() {

    LOGINFO("examples start.");

    example1();

    example2();

    example3();

    LOGINFO("examples stop.");

    return true;
  }
}
