
#include "example_concept.h"

#include "logger.h"

namespace cc::action::example_concept {

  bool examples() {

    LOGINFO("examples start.");

    auto resultA = adderA(1.1, 2.2);

    auto resultB = adderB(2.0, 1.1);

    auto resultC = adderC(3.0, 1.1);

    LOGINFO("result 1 adder '", resultA, "'");

    LOGINFO("result 2 adder '", resultB, "'");

    LOGINFO("result 3 adder '", resultC, "'");

    LOGINFO("examples start.");

    return true;
  }
}
