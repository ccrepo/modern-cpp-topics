#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <iostream>
#include <sstream>
#include <memory>

#include "utility.h"

namespace cc {

class FATAL;
class ERROR;
class WARN;
class INFO;
class DEBUG;
class TRACE;
class ALL;

static constexpr const char *C_LOGGER_LEVEL_DEBUG { "debug" };
static constexpr const char *C_LOGGER_LEVEL_ERROR { "error" };
static constexpr const char *C_LOGGER_LEVEL_FATAL { "fatal" };
static constexpr const char *C_LOGGER_LEVEL_INFO  { "info" };
static constexpr const char *C_LOGGER_LEVEL_WARN  { "warn" };
static constexpr const char *C_LOGGER_LEVEL_TRACE { "trace" };
static constexpr const char *C_LOGGER_LEVEL_ALL   { "all" };

template<typename T>
class loggerT final {

  using value_type [[maybe_unused]] = typename std::enable_if<
      std::is_same<FATAL, T>::value ||
      std::is_same<ERROR, T>::value ||
      std::is_same<WARN,  T>::value ||
      std::is_same<INFO,  T>::value ||
      std::is_same<DEBUG, T>::value ||
      std::is_same<TRACE, T>::value ||
      std::is_same<ALL,   T>::value>::type;

public:
  loggerT() {
  }

  virtual ~loggerT() {
  }

public:
  static bool is_level_on();

  const char* get_prefix() const;

  void log(const std::string& s) {

    static const bool is_on(is_level_on());

    if (is_on &&
        !s.empty()) {

      std::cout << s;
      std::cout.flush();
    }
  }

private:
  loggerT(const loggerT<T>&) = delete;

  loggerT<T>& operator=(const loggerT<T>&) = delete;

};

extern thread_local const std::string thread_name;

inline std::ostringstream& operator<<(std::ostringstream& os,
    const std::ostringstream& s) {
  os << s.str();
  return os;
}

template<typename T>
void log(std::ostringstream& os, const T& t) {
  os << t;
}

template<typename T, typename ... Args>
void log(std::ostringstream& os, const T& t, const Args &... args) {
  os << t;
  log<Args...>(os, args...);
}

template<typename T, typename ... Args>
void log(loggerT<T>& logger, const char *file, uint32_t lineno,
    const char *function, const Args &... args) {

  static const std::string prefix(utility::rpad(logger.get_prefix(), 5));

  std::ostringstream os;

  os << utility::system_clock_as_string_ms()
      << " ["
      << thread_name
      << "]["
      << prefix
      << "]["
      << static_cast<void*>(&logger)
      << "] "
      << file
      << ":"
      << lineno
      << "("
      << function
      << ") ";

  log<Args...>(os, args...);

  os << std::endl;

  logger.log(os.str());
}

}

#ifndef LOGALL
#define LOGALL(...) {                                                         \
  if (cc::loggerT<cc::ALL>::is_level_on())                                    \
  {                                                                           \
    static constexpr const char* __basename(cc::utility::basename(__FILE__)); \
    thread_local static cc::loggerT<cc::ALL> __logger;                        \
    cc::log<cc::ALL>                                                          \
    (__logger, __basename, __LINE__, __FUNCTION__, __VA_ARGS__);              \
  }                                                                           \
}
#endif

#ifndef LOGTRACE
#define LOGTRACE(...) {                                                       \
  if (cc::loggerT<cc::TRACE>::is_level_on())                                  \
  {                                                                           \
    static constexpr const char* __basename(cc::utility::basename(__FILE__)); \
    thread_local static cc::loggerT<cc::TRACE> __logger;                      \
    cc::log<cc::TRACE>                                                        \
    (__logger, __basename, __LINE__, __FUNCTION__, __VA_ARGS__);              \
  }                                                                           \
}
#endif

#ifndef LOGDEBUG
#define LOGDEBUG(...) {                                                       \
  if (cc::loggerT<cc::DEBUG>::is_level_on())                                  \
  {                                                                           \
    static constexpr const char* __basename(cc::utility::basename(__FILE__)); \
    thread_local static cc::loggerT<cc::DEBUG> __logger;                      \
    cc::log<cc::DEBUG>                                                        \
    (__logger, __basename, __LINE__, __FUNCTION__, __VA_ARGS__);              \
  }                                                                           \
}
#endif

#ifndef LOGINFO
#define LOGINFO(...) {                                                        \
  if (cc::loggerT<cc::INFO>::is_level_on())                                   \
  {                                                                           \
    static constexpr const char* __basename(cc::utility::basename(__FILE__)); \
    thread_local static cc::loggerT<cc::INFO> __logger;                       \
    cc::log<cc::INFO>                                                         \
    (__logger, __basename, __LINE__, __FUNCTION__, __VA_ARGS__);              \
  }                                                                           \
}
#endif

#ifndef LOGWARN
#define LOGWARN(...) {                                                        \
  if (cc::loggerT<cc::WARN>::is_level_on())                                   \
  {                                                                           \
    static constexpr const char* __basename(cc::utility::basename(__FILE__)); \
    thread_local static cc::loggerT<cc::WARN> __logger;                       \
    cc::log<cc::WARN>                                                         \
    (__logger, __basename, __LINE__, __FUNCTION__, __VA_ARGS__);              \
  }                                                                           \
}
#endif

#ifndef LOGERROR
#define LOGERROR(...) {                                                       \
  if (cc::loggerT<cc::ERROR>::is_level_on())                                  \
  {                                                                           \
    static constexpr const char* __basename(cc::utility::basename(__FILE__)); \
    thread_local static cc::loggerT<cc::ERROR> __logger;                      \
    cc::log<cc::ERROR>                                                        \
    (__logger, __basename, __LINE__, __FUNCTION__, __VA_ARGS__);              \
  }                                                                           \
}
#endif

#ifndef LOGFATAL
#define LOGFATAL(...) {                                                       \
  if (cc::loggerT<cc::FATAL>::is_level_on())                                  \
  {                                                                           \
    static constexpr const char* __basename(cc::utility::basename(__FILE__)); \
    thread_local static cc::loggerT<cc::FATAL> __logger;                      \
    cc::log<cc::FATAL>                                                        \
    (__logger, __basename, __LINE__, __FUNCTION__, __VA_ARGS__);              \
  }                                                                           \
}
#endif

#endif
