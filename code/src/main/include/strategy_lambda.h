#ifndef __STRATEGYLAMBDA_H__
#define __STRATEGYLAMBDA_H__

#include "strategy.h"

namespace cc {

class strategy_lambda : public strategy {

public:
  strategy_lambda() {}

  virtual ~strategy_lambda() {}

  virtual bool run();

private:
  strategy_lambda(const strategy_lambda&) = delete;

  const strategy_lambda& operator=(const strategy_lambda&) = delete;

};

}

#endif
