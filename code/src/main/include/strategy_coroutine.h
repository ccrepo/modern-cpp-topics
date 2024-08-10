#ifndef __STRATEGYCOROUTINE_H__
#define __STRATEGYCOROUTINE_H__

#include "strategy.h"

namespace cc {

class strategy_coroutine : public strategy {

public:
  strategy_coroutine() {}

  virtual ~strategy_coroutine() {}

  virtual bool run();

private:
  strategy_coroutine(const strategy_coroutine&) = delete;

  const strategy_coroutine& operator=(const strategy_coroutine&) = delete;

};

}

#endif
