
#include <sstream>

#include "example_coroutine.h"

#include "logger.h"

namespace cc::action::example_coroutine {

  void f1(int) {

    // do work !
  }

  void example1() {

    for (int i=0; i<5; ++i) {

      f1(i);
    }

    for (int i=5; i<10; ++i) {

      f1(i);
    }

    LOGINFO("done");
  }

  int counter() {

    static int i(0);

    return i++;
  }

  void f2(int) {

    // do work !
  }

  void example2() {

    for (int i=0; i<5; ++i) {

      f2(counter());
    }

    for (int i=5; i<5; ++i) {

      f2(counter());
    }

    LOGINFO("done");
  }

  void example3() {

    return_object o = f3();

    o._handle.resume();

    o._handle.resume();

    std::ostringstream os;

    os << std::boolalpha
        << o._handle.done();

    LOGINFO("done: ", os.str());
  }

  void example4() {

    return_object_lazy o = f4();

    o._handle.resume();

    o._handle.resume();

    o._handle.resume();

    o._handle.resume();

    std::ostringstream os;

    os << std::boolalpha
        << o._handle.done();

    LOGINFO("done: ", os.str());
  }

  return_object
  f3() {

    static constexpr int LIMIT{3};

    for (int i(0); i<LIMIT; ++i) {

      LOGINFO("step ", i+1, "/", LIMIT);

      if (i+1 != LIMIT) {

        co_await std::suspend_always{};
      }
    }
  }


  return_object_lazy
  f4() {

    static constexpr int LIMIT{4};

    for (int i(0); i<LIMIT; ++i) {

      LOGINFO("step ", i+1, "/", LIMIT);

      if (i+1 != LIMIT) {

        co_await std::suspend_always{};
      }
    }
  }

  return_object_generator
  f5(int start, int end) {

    for (int i(start); i <= end; ++i) {

      co_yield i;
    }
  }

  void example5() {

    static constexpr int LIMIT{10};

    std::ostringstream os;

    return_object_generator o = f5(1, LIMIT);

    if (!o._handle.done()) {

      os << o.get_value();

      do {

        o._handle.resume();

        if (o._handle.done()) {

          break;
        }

        os << " "
            << o.get_value();

      } while (true);
    }

    LOGINFO("done: ", os.str());
  }

  bool examples() {

    LOGINFO("examples start.");

    example1();

    example2();

    example3();

    example4();

    example5();

    LOGINFO("examples stop.");

    return true;
  }

}

