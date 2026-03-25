#include <iostream>
#include <string>
#include <vector>

#include "p1.h"

int main() {
  try {
    int numStrs = 0;
    int numPrefixes = 0;
    if (!(std::cin >> numStrs >> numPrefixes)) {
      return 0;
    }

    std::vector<std::string> strs;
    std::vector<std::string> prefixes;
    strs.reserve(static_cast<std::size_t>(numStrs));
    prefixes.reserve(static_cast<std::size_t>(numPrefixes));

    for (int index = 0; index < numStrs; ++index) {
      std::string str;
      std::cin >> str;
      strs.push_back(str);
    }

    for (int index = 0; index < numPrefixes; ++index) {
      std::string prefix;
      std::cin >> prefix;
      prefixes.push_back(prefix);
    }

    for (int index = 0; index < numStrs; ++index) {
      std::cout << (hasValidPrefix(strs.at(static_cast<std::size_t>(index)),
                                   prefixes)
                        ? 1
                        : 0)
                << "\n";
    }

    std::cout << findLongestValidCommonPrefix(strs, prefixes) << "\n";
    return 0;
  } catch (...) {
    return 1;
  }
}
