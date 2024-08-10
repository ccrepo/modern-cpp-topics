
#include "action.h"
#include "strategy.h"

namespace cc {

action::action() : _strategy() {

}

action::~action() {

}

void action::set_strategy(std::unique_ptr<strategy> strategy) {

  _strategy.reset(strategy.release());
}

bool action::run() {

  if (!_strategy) {

    return false;
  }

  return _strategy->run();
}

}
