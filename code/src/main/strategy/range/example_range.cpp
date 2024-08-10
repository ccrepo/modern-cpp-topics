
#include <string>
#include <algorithm>
#include <ranges>

//

#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <vector>

#include <map>
#include <set>

#include <unordered_map>
#include <unordered_set>

#include <queue>
#include <stack>

//

#include "example_range.h"
#include "logger.h"

namespace cc::action::example_range {

  void example1() {

    std::string foo("foo");

    std::string bar("bar");

    std::string foo_2("foo");

    bool is_equal_1(std::equal(foo.begin(), foo.end(), bar.begin())); // ugly and verbose.

    bool is_equal_2(std::equal(foo.begin(), foo.end(), foo_2.begin()));

    LOGINFO("done: is_equal '", foo, "' and '", bar, "' are ", (is_equal_1 ? "" : "NOT "), "equal");

    LOGINFO("done: is_equal '", foo, "' and '", foo_2, "' are ", (is_equal_2 ? "" : "NOT "), "equal");
  }

  void example2() {

    std::array<int, 6> data { 1, 6, 2, 5, 3, 4 };

    std::sort(data.begin(), data.end());

    bool found (std::find(data.begin(), data.end(), 6) != data.end());

    LOGINFO("done: found ", found ? "yes" : "no");
  }

  void example3() {

    std::array<int, 6> data { 1, 6, 2, 5, 3, 4 };

    std::ranges::sort(data);

    bool found (std::ranges::find(data, 6) != data.end());

    LOGINFO("done: found ", found ? "yes" : "no");
  }

  auto odd = [](const int i) { return i%2; };

  auto doubled = [](const int i) { return i*2; };

  void example4() {

    std::array<int, 6> data { 1, 6, 2, 5, 3, 4 };

    std::ranges::sort(data);

    auto results = data | std::ranges::views::filter(odd) | std::ranges::views::transform(doubled);

    std::ostringstream os;

    os << "{ ";

    for (const auto& result : results) {

      os << result
          << " ";
    }

    os << "}";

    LOGINFO("done: ", os.str())
  }

  void example5() {

    LOGINFO("array ", std::ranges::range<std::array<int, 1>>);
    LOGINFO("forward_list ", std::ranges::range<std::forward_list<int>>);
    LOGINFO("deque ", std::ranges::range<std::deque<int>>);
    LOGINFO("list ", std::ranges::range<std::list<int>>);
    LOGINFO("vector ", std::ranges::range<std::vector<int>>);

    LOGINFO("map ", std::ranges::range<std::map<int, int>>);
    LOGINFO("set ", std::ranges::range<std::set<int>>);
    LOGINFO("multimap ", std::ranges::range<std::multimap<int, int>>);
    LOGINFO("multiset ", std::ranges::range<std::multiset<int>>);

    LOGINFO("unordered_map ", std::ranges::range<std::unordered_map<int, int>>);
    LOGINFO("unordered_set ", std::ranges::range<std::unordered_set<int>>);
    LOGINFO("unordered_multimap ", std::ranges::range<std::unordered_multimap<int, int>>);
    LOGINFO("unordered_multiset ", std::ranges::range<std::unordered_multiset<int>>);

    LOGINFO("queue ", std::ranges::range<std::queue<int>>);
    LOGINFO("priority_queue ", std::ranges::range<std::priority_queue<int>>);
    LOGINFO("stack ", std::ranges::range<std::stack<int>>);
  }

  bool examples() {

    LOGINFO("examples start.");

    example1();

    example2();

    example3();

    example4();

    example5();

    LOGINFO("examples stop.");

    return true;
  }
}

