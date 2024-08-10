
#include "example_concept.h"
#include "strategy_concept.h"

#include "logger.h"

namespace cc {

bool strategy_concept::run() {

  return cc::action::example_concept::examples();
}

}
