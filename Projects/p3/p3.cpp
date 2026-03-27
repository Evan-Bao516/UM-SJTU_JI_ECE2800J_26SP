#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>

#include "simulation.h"

using std::cout;
using std::string;

const int MIN_REQUIRED_ARGS = 4;
const int ARGS_WITH_VERBOSE = 5;
const int VERBOSE_FLAG_INDEX = 4;
const int BASE_DECIMAL = 10;

int main(int argc, const char* argv[]) {
    try {
        if (argc < MIN_REQUIRED_ARGS) {
            cout << "Error: Missing arguments!\n";
            cout << "Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]\n";
            return 0;
        }
        string speciesFile = argv[1];
        string worldFile = argv[2];
        char* endPtr = nullptr;
        const int64_t parsedRounds = std::strtol(argv[3], &endPtr, BASE_DECIMAL);
        if (endPtr == argv[3]) {
            cout << "Error: Number of simulation rounds is invalid!\n";
            return 0;
        }
        const int rounds = static_cast<int>(parsedRounds);
        if (rounds < 0) {
            cout << "Error: Number of simulation rounds is negative!\n";
            return 0;
        }
        bool verbose = false;
        if (argc >= ARGS_WITH_VERBOSE) {
            string vFlag = argv[VERBOSE_FLAG_INDEX];
            if (vFlag == "v" || vFlag == "verbose") {
                verbose = true;
            }
        }
        world_t world;
        if (initWorld(world, speciesFile, worldFile)) {
            runSimulation(world, rounds, verbose);
        }
    } catch (...) {
        return 1;
    }
}
