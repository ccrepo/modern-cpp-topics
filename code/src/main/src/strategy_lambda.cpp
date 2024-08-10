
#include "example_lambda.h"
#include "strategy_lambda.h"

#include "logger.h"

namespace cc {

bool strategy_lambda::run() {

  return cc::action::example_lambda::examples();
}

}
