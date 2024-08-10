
#include "example_coroutine.h"
#include "strategy_coroutine.h"

#include "logger.h"

namespace cc {

bool strategy_coroutine::run() {

  return cc::action::example_coroutine::examples();
}

}
