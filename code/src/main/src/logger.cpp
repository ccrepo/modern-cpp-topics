#include "logger.h"
#include "config.h"

namespace cc {

template<>
const char* loggerT<DEBUG>::get_prefix() const {
  return C_LOGGER_LEVEL_DEBUG;
}

template<>
const char* loggerT<ERROR>::get_prefix() const {
  return C_LOGGER_LEVEL_ERROR;
}

template<>
const char* loggerT<FATAL>::get_prefix() const {
  return C_LOGGER_LEVEL_FATAL;
}

template<>
const char* loggerT<INFO>::get_prefix() const {
  return C_LOGGER_LEVEL_INFO;
}

template<>
const char* loggerT<TRACE>::get_prefix() const {
  return C_LOGGER_LEVEL_TRACE;
}

template<>
const char* loggerT<ALL>::get_prefix() const {
  return C_LOGGER_LEVEL_ALL;
}

template<>
const char* loggerT<WARN>::get_prefix() const {
  return C_LOGGER_LEVEL_WARN;
}

template<>
bool loggerT<ALL>::is_level_on() {
  static const bool is_level(
      config::singleton()->is_log_all());

  return is_level;
}

template<>
bool loggerT<TRACE>::is_level_on() {

  static const bool is_level(
      config::singleton()->is_log_trace()
      || loggerT<ALL>::is_level_on());

  return is_level;
}

template<>
bool loggerT<DEBUG>::is_level_on() {

  static const bool is_level(
      config::singleton()->is_log_debug()
      || loggerT<TRACE>::is_level_on());

  return is_level;
}

template<>
bool loggerT<INFO>::is_level_on() {

  static const bool is_level(
      config::singleton()->is_no_level() ?
          true :
          (config::singleton()->is_log_info()
              || loggerT<DEBUG>::is_level_on()));

  return is_level;
}

template<>
bool loggerT<WARN>::is_level_on() {

  static const bool is_level(
      config::singleton()->is_no_level() ?
          true :
          (config::singleton()->is_log_warn()
              || loggerT<INFO>::is_level_on()));

  return is_level;
}

template<>
bool loggerT<ERROR>::is_level_on() {

  static const bool is_level(
      config::singleton()->is_no_level() ?
          true :
          (config::singleton()->is_log_error()
              || loggerT<WARN>::is_level_on()));

  return is_level;
}

template<>
bool loggerT<FATAL>::is_level_on() {

  static const bool is_level(
      config::singleton()->is_no_level() ?
          true :
          (config::singleton()->is_log_fatal()
              || loggerT<ERROR>::is_level_on()));

  return is_level;
}

thread_local const std::string thread_name(utility::get_thread_name());

}
