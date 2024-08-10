#ifndef __ACTION_H__
#define __ACTION_H__

#include <memory>

namespace cc {

class strategy;

class action {

public:
  virtual ~action();

  void set_strategy(std::unique_ptr<cc::strategy> strategy);

  bool run();

private:
  action();

private:
  std::unique_ptr<cc::strategy> _strategy;

private:
  action(const action&) = delete;

  action& operator=(const action&) = delete;

private:
  friend class factory;

};

}

#endif
