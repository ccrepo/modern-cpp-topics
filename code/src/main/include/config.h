#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <array>
#include <memory>
#include <string>
#include <vector>

namespace cc {

class config final {

private:
  config(int argc, char** argv);

private:
  static std::shared_ptr<config> _config;

public:
  static const std::array<const std::string, 5>& actions();

  static const std::array<const std::string, 7>& loglevels();

public:
  static constexpr const char *C_PARAMNAME_H { "-h" };
  static constexpr const char *C_PARAMNAME_ACTION { "-action" };
  static constexpr const char *C_PARAMNAME_LOGLEVEL { "-loglevel" };

  static constexpr const char *C_ACTION_TYPE_CONCEPT { "concept" };
  static constexpr const char *C_ACTION_TYPE_COROUTINE { "coroutine" };
  static constexpr const char *C_ACTION_TYPE_FUTUREPROMISE { "future-promise" };
  static constexpr const char *C_ACTION_TYPE_LAMBDA { "lambda" };
  static constexpr const char *C_ACTION_TYPE_RANGE { "range" };

public:
  static bool init(int argc, char** argv);

  virtual ~config();

  static const std::shared_ptr<config>& singleton();

  bool is_error() const;

  bool is_help() const;

  bool is_log_debug() const;

  bool is_log_error() const;

  bool is_log_fatal() const;

  bool is_log_info() const;

  bool is_log_trace() const;

  bool is_log_all() const;

  bool is_log_warn() const;

  bool is_no_level();

public:
  const std::string& action() const;

  const std::string& loglevel() const;

  const std::vector<std::string>& errors() const;

private:
  bool check_all();

  bool check_action();

  bool check_loglevel();

  bool set_one(const std::string& name, int& i, int argc, char** argv);

  bool set_action(int i, int argc, char** argv);

  bool set_loglevel(int i, int argc, char** argv);

private:
  config(const config&) = delete;

  config& operator=(const config&) = delete;

private:
  std::vector<std::string> _errors;

  bool _help;

  std::array<const std::string, 5> _actions;

  std::string _action;

  std::array<const std::string, 7> _loglevels;

  std::string _loglevel;

};

}

#endif
