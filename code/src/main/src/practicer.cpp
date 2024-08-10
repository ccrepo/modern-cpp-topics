
#include <iostream>
#include <memory>
#include <stdlib.h>

#include "action.h"
#include "config.h"
#include "factory.h"
#include "practicer.h"
#include "strategy.h"
#include "utility.h"

void usage(const char* program_name) {

  std::cerr << "usage: "
      << std::endl;

  std::cerr << " "
      << cc::utility::basename(program_name)
      << " "
      << cc::config::C_PARAMNAME_ACTION
      << " (";

  for (const std::string& action : cc::config::actions() ) {

    if (&action != &cc::config::actions()[0]) {

      std::cerr << "|";
    }

    std::cerr << action;
  }

  std::cerr << ") "
      << std::endl;

  std::cerr << " "
      << cc::utility::basename(program_name)
      << " "
      << cc::config::C_PARAMNAME_H
      << std::endl;
}

int main (int argc, char** argv) {

  if (!cc::config::init(argc, argv)) {

    if (cc::config::singleton()->is_help()) {

      usage(argv[0]);

      return 0;
    }

    if (cc::config::singleton()->is_error()) {

      for (const std::string& error : cc::config::singleton()->errors() ) {

        std::cerr << "error: " << error << std::endl;
      }
    }

    return 1;
  }

  LOGINFO("start");

  LOGALL   ("log all");
  LOGTRACE ("log trace");
  LOGDEBUG ("log debug");
  LOGINFO  ("log info");
  LOGWARN  ("log warn");
  LOGERROR ("log error");
  LOGFATAL ("log fatal");

  std::string action_name(cc::config::singleton()->action());

  std::string loglevel(cc::config::singleton()->loglevel());

  LOGINFO("-action: '", action_name, "'");

  LOGINFO("-loglevel: '", loglevel, "'");

  std::unique_ptr<cc::action> action(cc::factory::alloc(action_name));

  if (!action) {

    LOGERROR("action run '", action_name, "' not allocated");

  } else {

    if (action->run()) {

      LOGINFO("action run worked");

    } else {

      LOGERROR("action run error");
    }
  }

  LOGINFO("stop.");

  std::cout << "." << std::endl;

  return 0;
}
