#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <algorithm>
#include <sstream>
#include <vector>
#include <cassert>
#include <tuple>
#include <ctime>
#include <iomanip>
#include <string>
#include <memory>
#include <chrono>
using namespace std::chrono_literals;

namespace cc {

class utility final {

public:
  std::string getenv(const std::string& name);

public:
  static constexpr const char* basename(const char *s) {
    return str_slant(s) ? r_slant(str_end(s)) : s;
  }

private:
  static constexpr char path_separator = '/';

  static constexpr const char* str_end(const char *s) {
    return *s ? str_end(s + 1) : s;
  }

  static constexpr bool str_slant(const char *s) {
    return *s == path_separator ? true : (*s ? str_slant(s + 1) : false);
  }

  static constexpr const char* r_slant(const char *s) {
    return *s == path_separator ? (s + 1) : r_slant(s - 1);
  }

public:
  static std::string rpad(const std::string& s,
      uint32_t size);

public:
  static int64_t steady_clock_now_MS();

  static std::string system_clock_as_string_ms();

  static std::string system_clock_as_string_sec();

private:
  static const std::chrono::time_point<std::chrono::steady_clock> _effective_epoch;

public:
  static const std::string& get_thread_name();

  static uint64_t get_thread_id();

  static std::string get_thread_descriptor(uint64_t id);

private:
  static const std::string _thread_desc_prefix;

  static std::atomic<uint64_t> _thread_id_counter;

public:
  static void do_sleep(uint32_t ms);

private:
  utility() = delete;

};

}

#endif

