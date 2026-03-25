#ifndef P1_H
#define P1_H

#include <string>
#include <vector>

bool hasValidPrefix(const std::string &str,
                    const std::vector<std::string> &validPrefixes);
// REQUIRES: validPrefixes is a non-empty vector of strings.
// EFFECTS: Returns true if and only if str begins with at least one string
//          from validPrefixes. Returns false otherwise.

std::string
findLongestValidCommonPrefix(const std::vector<std::string> &strs,
                             const std::vector<std::string> &validPrefixes);
// REQUIRES: strs is a non-empty vector of strings.
//           validPrefixes is a non-empty vector of strings.
// EFFECTS: Returns the longest string from validPrefixes that appears at
//          the beginning of every string in strs. If multiple prefixes tie
//          for longest length, returns the one that appears first in
//          validPrefixes. If no prefix from validPrefixes appears at the
//          beginning of all strings in strs, returns an empty string.

#endif
