
#include "maths.h"

namespace cc {

  thread_local std::random_device maths::_device;

  thread_local std::mt19937 maths::_generator(_device());

  uint32_t maths::rand_in_range(uint32_t low, uint32_t high) {

    if (low > high) {

      assert(!"upper is not more than lower");
    }

    return (
        std::uniform_int_distribution<>(
            low, high)).operator()(_generator);
  }

  uint32_t maths::get_short_rand_in_range() {

    return rand_in_range(C_DURATIONS_MINISCULE,
        C_DURATIONS_SHORTEST);
  }

}
