#ifndef __EXAMPLE_FUTUREPROMISE_H__
#define __EXAMPLE_FUTUREPROMISE_H__

#include <future>

namespace cc::action::example_futurepromise {

  void f1(unsigned int i);

  void example1();

  //

  void f2(unsigned int i);

  void example2();

  //

  void f3(unsigned int i, long& buffer);

  void example3();

  //

  int f4(unsigned int i);

  void example4();

  //

  int f5(std::future<unsigned int>& f);

  void example5();

  //

  bool examples();
}

#endif
