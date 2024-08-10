#ifndef __MATHS_H__
#define __MATHS_H__

#include <random>
#include <string>
#include <cassert>

namespace cc {

class maths final {

public:
  static constexpr uint16_t C_DURATIONS_MINIMUM   { 5 };
  static constexpr uint16_t C_DURATIONS_MINISCULE { 10 };
  static constexpr uint16_t C_DURATIONS_SHORTEST  { 25 };
  static constexpr uint16_t C_DURATIONS_SHORTER   { 50 };
  static constexpr uint16_t C_DURATIONS_SHORT     { 75 };
  static constexpr uint16_t C_DURATIONS_MEDIUM    { 100 };
  static constexpr uint16_t C_DURATIONS_LONG      { 200 };
  static constexpr uint16_t C_DURATIONS_LONGER    { 400 };
  static constexpr uint16_t C_DURATIONS_LONGEST   { 500 };

public:
  static uint32_t rand_in_range(uint32_t low, uint32_t high);

  static uint32_t get_short_rand_in_range();

private:
  thread_local static std::random_device _device;

  thread_local static std::mt19937 _generator;

private:
  maths() = delete;

};

}

#endif
