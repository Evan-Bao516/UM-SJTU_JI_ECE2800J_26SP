#include <vector>
#include <string>
#include "p1.h"

bool hasValidPrefix(const std::string &str, const std::vector<std::string> &validPrefixes) {
    for (size_t Pf_num = 0; Pf_num < validPrefixes.size(); ++Pf_num) {
        if (validPrefixes.at(Pf_num).size() <= str.size()) {
            bool match = true;
            for (size_t str_num = 0; str_num < validPrefixes.at(Pf_num).size(); ++str_num) {
                if (str.at(str_num) != validPrefixes.at(Pf_num).at(str_num)) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return true;
            }
        }
    }
    return false;
}

std::string findLongestValidCommonPrefix(const std::vector<std::string> &strs,
                                        const std::vector<std::string> &validPrefixes) {
    if (strs.empty()) {
        return "";
    }
    std::string globalLCP = strs.at(0);
    for (size_t iii = 1; iii < strs.size(); ++iii) {
        const std::string &currentStr = strs.at(iii);
        size_t matchLen = 0;
        const size_t maxPossible = (globalLCP.size() < currentStr.size()) ? globalLCP.size() : currentStr.size();
        while (matchLen < maxPossible && globalLCP.at(matchLen) == currentStr.at(matchLen)) {
            matchLen++;
        }
        globalLCP.resize(matchLen);
        if (globalLCP.empty()) {
            break;
        }
    }
    std::string longestPrefix;
    bool found = false;
    for (size_t jjj = 0; jjj < validPrefixes.size(); ++jjj) {
        const std::string &ppp = validPrefixes.at(jjj);
        if (found && ppp.size() <= longestPrefix.size()) {
            continue;
        }
        if (ppp.size() <= globalLCP.size()) {
            if (globalLCP.compare(0, ppp.size(), ppp) == 0) {
                longestPrefix = ppp;
                found = true;
            }
        }
    }
    return longestPrefix;
}
