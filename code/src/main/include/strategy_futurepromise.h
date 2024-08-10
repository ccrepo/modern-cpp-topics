#ifndef __STRATEGYFUTUREPROMISE_H__
#define __STRATEGYFUTUREPROMISE_H__

#include "strategy.h"

namespace cc {

class strategy_futurepromise : public strategy {

public:
  strategy_futurepromise() {}

  virtual ~strategy_futurepromise() {}

  virtual bool run();

private:
  strategy_futurepromise(const strategy_futurepromise&) = delete;

  const strategy_futurepromise& operator=(const strategy_futurepromise&) = delete;

};

}

#endif
