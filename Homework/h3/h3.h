#ifndef H3_H
#define H3_H

#include <string>

inline constexpr int kGridSize = 5;

inline constexpr char kUppercaseSquare[kGridSize][kGridSize] = {
    {'A', 'B', 'C', 'D', 'E'}, {'F', 'G', 'H', 'I', 'K'}, {'L', 'M', 'N', 'O', 'P'},
    {'Q', 'R', 'S', 'T', 'U'}, {'V', 'W', 'X', 'Y', 'Z'},
};

inline constexpr char kLowercaseSquare[kGridSize][kGridSize] = {
    {'a', 'b', 'c', 'd', 'e'}, {'f', 'g', 'h', 'i', 'k'}, {'l', 'm', 'n', 'o', 'p'},
    {'q', 'r', 's', 't', 'u'}, {'v', 'w', 'x', 'y', 'z'},
};

void printHelp();

#endif  // H3_H
