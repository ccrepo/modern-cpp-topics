#ifndef __STRATEGY_H__
#define __STRATEGY_H__

#include <string>

namespace cc {

class strategy {

public:
  virtual ~strategy() {}

  virtual bool run() = 0;

protected:
  strategy() {}

private:
  strategy(const strategy&) = delete;

  const strategy& operator=(const strategy&) = delete;

private:
  friend class factory;

};

}

#endif
