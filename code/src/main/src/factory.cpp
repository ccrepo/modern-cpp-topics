
#include "action.h"
#include "config.h"
#include "factory.h"
#include "logger.h"
#include "strategy.h"
#include "strategy_concept.h"
#include "strategy_coroutine.h"
#include "strategy_futurepromise.h"
#include "strategy_lambda.h"
#include "strategy_range.h"

namespace cc {

std::unique_ptr<cc::action> factory::alloc(const std::string& action_name) {

  std::unique_ptr<cc::action> allocated(new cc::action());

  if (action_name == config::C_ACTION_TYPE_CONCEPT) {

    allocated->set_strategy(std::make_unique<cc::strategy_concept>());

    LOGINFO("allocated concept");

  } else if (action_name == config::C_ACTION_TYPE_COROUTINE) {

    allocated->set_strategy(std::make_unique<cc::strategy_coroutine>());

    LOGINFO("allocated coroutine");

  } else if (action_name == config::C_ACTION_TYPE_FUTUREPROMISE) {

    allocated->set_strategy(std::make_unique<cc::strategy_futurepromise>());

    LOGINFO("allocated future promise");

  } else if (action_name == config::C_ACTION_TYPE_LAMBDA) {

    allocated->set_strategy(std::make_unique<cc::strategy_lambda>());

    LOGINFO("allocated lambda");

  } else if (action_name == config::C_ACTION_TYPE_RANGE) {

    allocated->set_strategy(std::make_unique<cc::strategy_range>());

    LOGINFO("allocated range");

  } else {

    LOGINFO("allocated none");

  }

  return allocated;
}

}
