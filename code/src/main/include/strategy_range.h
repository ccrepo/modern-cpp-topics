#ifndef __STRATEGYRANGE_H__
#define __STRATEGYRANGE_H__

#include "strategy.h"

namespace cc {

class strategy_range : public strategy {

public:
  strategy_range() {}

  virtual ~strategy_range() {}

  virtual bool run();

private:
  strategy_range(const strategy_range&) = delete;

  const strategy_range& operator=(const strategy_range&) = delete;

};

}

#endif
