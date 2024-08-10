
#include <thread>

#include "example_futurepromise.h"

#include "logger.h"

namespace cc::action::example_futurepromise {

  std::atomic<bool> a3(false);

  bool examples() {

    LOGINFO("start examples.");

    example1();

    example2();

    example3();

    example4();

    example5();

    LOGINFO("stop examples.");

    return true;
  }

  //

  void f1(unsigned int i) {

    long result(0);

    while (i) {

      result += i--;
    }

    LOGINFO("done: ", result);
  }

  void example1() {

    f1(10);
  }

  //

  void f2(unsigned int i) {

    long result(0);

    while (i) {

      result += i--;
    }

    LOGINFO("done: ", result);
  }

  void example2() {

    std::thread t(f2, 11);

    t.join();
  }


  void f3(unsigned int i, long& buffer) {

    long result(0);

    while (i) {

      result += i--;
    }

    buffer = result;

    LOGINFO("done: ", result);

    a3 = true;
  }

  void example3() {

    long buffer(0);

    std::thread t(f3, 12, std::ref(buffer));

    t.join();

    while (!a3) {

    }

    LOGINFO("buffer: ", buffer);
  }

  void example4() {

    std::future<int> result = std::async(std::launch::async, f4, 5); // std::deferred::async

    LOGINFO("result: ", result.get());
  }

  int f4(unsigned int i) {

    long result(0);

    while (i) {

      result += i--;
    }

    LOGINFO("done: ", result);

    return result;
  }

  void example5() {

    std::promise<unsigned int> p;

    std::future<unsigned int> f = p.get_future();

    std::future<int> result = std::async(std::launch::async, f5, std::ref(f));

    p.set_value(3);

    LOGINFO("done: ", result.get());
  }

  int f5(std::future<unsigned int>& f) {

    long result(0);

    unsigned int i(f.get());

    while (i) {

      result += i--;
    }

    LOGINFO("done: ", result);

    return result;
  }

}

