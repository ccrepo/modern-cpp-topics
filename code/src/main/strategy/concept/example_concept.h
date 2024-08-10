#ifndef __EXAMPLE_CONCEPT_H__
#define __EXAMPLE_CONCEPT_H__

#include <type_traits>

namespace cc::action::example_concept {

  template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
  auto adderA(T a, T b) {

    return a + b;
  }

  template <typename T>
  concept floating_point = std::is_floating_point_v<T>;

  template<floating_point T>
  auto adderB(T a, T b) {

    return a + b;
  }

  auto adderC(floating_point auto a, floating_point auto b) {

    return a + b;
  }

  bool examples();
}

#endif
