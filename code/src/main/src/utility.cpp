
#include <thread>
#include <iomanip>

#include "utility.h"

namespace cc {

const std::chrono::time_point<std::chrono::steady_clock> utility::_effective_epoch {
  std::chrono::steady_clock::now() };

const std::string utility::_thread_desc_prefix("thread-");

std::atomic<uint64_t> utility::_thread_id_counter(0);

int64_t utility::steady_clock_now_MS() {
  return std::chrono::duration_cast<std::chrono::milliseconds>
      ((std::chrono::steady_clock::now()) - _effective_epoch).count();
}

std::string utility::system_clock_as_string_sec() {

  thread_local static struct tm ts_struct;

  thread_local static std::ostringstream os;
  os.str("");

  std::time_t ts { std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) };
  localtime_r(&ts, &ts_struct);
  os << std::put_time(&ts_struct, "%Y%m%d %H:%M:%S");
  return os.str();
}

std::string utility::system_clock_as_string_ms() {

  thread_local static struct tm ts_struct;

  thread_local static std::ostringstream os;
  os.str("");

  auto now(std::chrono::system_clock::now());
  std::time_t ts { std::chrono::system_clock::to_time_t(now) };
  localtime_r(&ts, &ts_struct);

  os << std::put_time(&ts_struct, "%Y%m%d %H:%M:%S")
          << "."
          << std::setfill('0')
          << std::setw(3)
          << std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() % 1000;

  return os.str();
}

std::string utility::rpad(const std::string& s,
    uint32_t size) {

  int64_t len(size - s.length());

  if (len <= 0) {
    return s;
  }

  std::string buffer(s);

  return buffer.insert(buffer.size(), len, ' ');
}

const std::string& utility::get_thread_name() {
  thread_local static const std::string thread_name(
      get_thread_descriptor(get_thread_id()));

  return thread_name;
}

uint64_t utility::get_thread_id() {
  thread_local static const uint64_t id(++_thread_id_counter);

  return id;
}

std::string utility::get_thread_descriptor(uint64_t id) {
  std::ostringstream os;

  os << _thread_desc_prefix
      << std::setfill('0')
      << std::setw(3)
      << id;

  return os.str();
}

void utility::do_sleep(uint32_t ms) {
  try {

    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
  } catch (const std::exception& e) {

  } catch (...) {

  }
}

}
