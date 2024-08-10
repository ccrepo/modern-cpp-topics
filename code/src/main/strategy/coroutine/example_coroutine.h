#ifndef __EXAMPLE_COROUTINE_H__
#define __EXAMPLE_COROUTINE_H__

#include <coroutine>

namespace cc::action::example_coroutine {

  //

  void f1(int);

  void example1();

  //

  int counter();

  void f2(int);

  void example2();

  //

  struct return_object_lazy {

    struct promise_type {

      std::suspend_always initial_suspend() {

        return {};
      }

      std::suspend_always final_suspend() noexcept  {

        return {};
      }

      return_object_lazy get_return_object() {

        return return_object_lazy(std::coroutine_handle<promise_type>::from_promise(*this));
      }

      void unhandled_exception() {
      }
    };

    std::coroutine_handle<> _handle; // std::coroutine_handle<void> _handle;

    return_object_lazy(std::coroutine_handle<> handle): _handle(handle) {};
  };

  struct return_object {

     struct promise_type {

       std::suspend_never initial_suspend() {

         return {};
       }

       std::suspend_always final_suspend() noexcept  {

         return {};
       }

       return_object get_return_object() {

         return return_object(std::coroutine_handle<promise_type>::from_promise(*this));
       }

       void unhandled_exception() {
       }
     };

     std::coroutine_handle<> _handle; // std::coroutine_handle<void> _handle;

     return_object(std::coroutine_handle<> handle): _handle(handle) {};
   };

  return_object
  f3();

  return_object_lazy
  f4();

  void example3();

  void example4();

  //

  struct return_object_generator {

     struct promise_type {

       std::suspend_never initial_suspend() {

         return {};
       }

       std::suspend_always final_suspend() noexcept  {

         return {};
       }

       std::suspend_always yield_value(int val) {

         _val = val;

         return std::suspend_always();
       }

       return_object_generator get_return_object() {

         return return_object_generator(std::coroutine_handle<promise_type>::from_promise(*this));
       }

       void unhandled_exception() {
       }

       int _val = 0;
     };

     std::coroutine_handle<promise_type> _handle;

     return_object_generator(std::coroutine_handle<promise_type> handle): _handle(handle) {};

     int get_value() const {

       return _handle.promise()._val;
     }
  };

  return_object_generator
  f5(int start, int end);

  void example5();

  //

  bool examples();
}

#endif
