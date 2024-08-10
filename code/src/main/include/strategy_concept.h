#ifndef __STRATEGYCONCEPT_H__
#define __STRATEGYCONCEPT_H__

#include "strategy.h"

namespace cc {

class strategy_concept : public strategy {

public:
  strategy_concept() {}

  virtual ~strategy_concept() {}

  virtual bool run();

private:
  strategy_concept(const strategy_concept&) = delete;

  const strategy_concept& operator=(const strategy_concept&) = delete;

};

}

#endif
