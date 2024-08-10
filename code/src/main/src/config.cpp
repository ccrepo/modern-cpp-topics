
#include <functional>
#include <atomic>

#include "config.h"
#include "logger.h"
#include "utility.h"
#include "maths.h"

namespace cc {

std::shared_ptr<config> config::_config(nullptr);

const std::array<const std::string, 5>& config::actions() {

  static const std::array<const std::string, 5> actions { C_ACTION_TYPE_CONCEPT,
    C_ACTION_TYPE_COROUTINE,
    C_ACTION_TYPE_FUTUREPROMISE,
    C_ACTION_TYPE_LAMBDA,
    C_ACTION_TYPE_RANGE };

  return actions;
}

const std::array<const std::string, 7>& config::loglevels() {

  static const std::array<const std::string, 7> loglevels { C_LOGGER_LEVEL_DEBUG,
    C_LOGGER_LEVEL_ERROR,
    C_LOGGER_LEVEL_FATAL,
    C_LOGGER_LEVEL_INFO,
    C_LOGGER_LEVEL_WARN,
    C_LOGGER_LEVEL_TRACE,
    C_LOGGER_LEVEL_ALL};

  return loglevels;
}

config::config(int argc, char** argv) :
  _errors(),
  _help(false),
  _actions(actions()),
  _action(),
  _loglevels(loglevels()),
  _loglevel() {

  for (int i(1); i < argc; ++i) {

    std::string name(argv[i]);

    if (C_PARAMNAME_H == name) {

      _help = true;

      return;
    }
  }

  for (int i(1); i < argc; ++i) {

    std::string name(argv[i]);

    if (!set_one(name, i, argc, argv)) {

      return;
    }
  }

  check_all();
}

bool config::set_one(const std::string& name, int& i, int argc, char** argv) {

  if (C_PARAMNAME_ACTION == name) {

    if (!set_action(++i, argc, argv)) {

      return false;
    }

    return true;
  }

  if (C_PARAMNAME_LOGLEVEL == name) {

    if (!set_loglevel(++i, argc, argv)) {

      return false;
    }

    return true;
  }

  std::ostringstream os;

  os << "parameter '"
      << name
      << "' unknown";

  _errors.push_back(os.str());

  return false;
}

bool config::set_action(int i, int argc, char** argv) {

  if (i >= argc) {

    std::ostringstream os;

    os << "parameter '"
        << C_PARAMNAME_ACTION
        << "' missing value";

    _errors.push_back(os.str());

    return false;
  }

  std::string action(argv[i]);

  if (std::find(_actions.begin(), _actions.end(), argv[i]) == _actions.end()) {

    std::ostringstream os;

    os << "parameter '"
        << C_PARAMNAME_ACTION
        << "' invalid value '"
        << action
        << "'";

    _errors.push_back(os.str());

    return false;
  }

  _action = action;

  return true;
}

bool config::set_loglevel(int i, int argc, char** argv) {

  if (i >= argc) {

    std::ostringstream os;

    os << "parameter '"
        << C_PARAMNAME_LOGLEVEL
        << "' missing value";

    _errors.push_back(os.str());

    return false;
  }

  std::string loglevel(argv[i]);

  if (std::find(_loglevels.begin(), _loglevels.end(), argv[i]) == _loglevels.end()) {

    std::ostringstream os;

    os << "parameter '"
        << C_PARAMNAME_LOGLEVEL
        << "' invalid value '"
        << loglevel
        << "'";

    _errors.push_back(os.str());

    return false;
  }

  _loglevel = loglevel;

  return true;
}

config::~config() {
}

bool config::init(int argc, char** argv) {

  static std::atomic<bool> guard(false);

  if (guard.exchange(true)) {

    while(guard.exchange(true) && !_config) {

      utility::do_sleep(maths::get_short_rand_in_range());
    }

    return (_config->is_help() ||
        _config->is_error()) ? false : true;
  }

  _config.reset(new config(argc, argv));

  guard = true;

  return (_config->is_help() || _config->is_error()) ?
      false : true;
}

const std::shared_ptr<config>& config::singleton() {

  assert(_config.get() ||
      !"configuration must be initialised before use!");

  return _config;
}

bool config::is_log_debug() const {

  return loglevel() == C_LOGGER_LEVEL_DEBUG;
}

bool config::is_log_error() const {

  return loglevel() == C_LOGGER_LEVEL_ERROR;
}

bool config::is_log_fatal() const {

  return loglevel() == C_LOGGER_LEVEL_FATAL;
}

bool config::is_log_info() const {

  return loglevel() == C_LOGGER_LEVEL_INFO;
}

bool config::is_log_trace() const {

  return loglevel() == C_LOGGER_LEVEL_TRACE;
}

bool config::is_log_all() const {

  return loglevel() == C_LOGGER_LEVEL_ALL;
}

bool config::is_log_warn() const {

  return loglevel() == C_LOGGER_LEVEL_WARN;
}

bool config::is_no_level() {

  return (
      static_cast<int>(singleton()->is_log_all())   +
      static_cast<int>(singleton()->is_log_trace()) +
      static_cast<int>(singleton()->is_log_debug()) +
      static_cast<int>(singleton()->is_log_info())  +
      static_cast<int>(singleton()->is_log_warn())  +
      static_cast<int>(singleton()->is_log_error()) +
      static_cast<int>(singleton()->is_log_fatal()))
      == 0;
}

bool config::is_help() const {

  return _help;
}

bool config::is_error() const {

  return !_errors.empty();
}

const std::string& config::action() const {

  return _action;
}

const std::string& config::loglevel() const {

  return _loglevel;
}

const std::vector<std::string>& config::errors() const {

  return _errors;
}

bool config::check_action() {

  if (!_action.length()) {

    std::ostringstream os;

    os << "parameter '"
        << C_PARAMNAME_ACTION
        << "' is mandatory";

    _errors.push_back(os.str());

    return false;
  }

  return true;
}

bool config::check_loglevel() {

  if (!_loglevel.length()) {

    _loglevel = C_LOGGER_LEVEL_INFO;
  }

  if (std::find(_loglevels.begin(), _loglevels.end(), _loglevel) == _loglevels.end()) {

    std::ostringstream os;

    os << "parameter '"
        << C_PARAMNAME_LOGLEVEL
        << "' is not set";

    _errors.push_back(os.str());

    return false;
  }

  return true;
}

bool config::check_all() {

  return check_action() &&
      check_loglevel();
}

}
