#ifndef __FACTORY_H__
#define __FACTORY_H__

#include <memory>
#include <string>

namespace cc {

class action;

class factory {

public:
  static std::unique_ptr<cc::action> alloc(const std::string& action_name);

private:
  factory() = delete;

};

}

#endif
