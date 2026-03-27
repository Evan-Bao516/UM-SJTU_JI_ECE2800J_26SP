#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>

#include "world_engine.h"
#include "world_type.h"

bool initWorld(world_t& world, const std::string& speciesFile, const std::string& worldFile);

void simulateCreature(creature_t& creature, grid_t& grid, bool verbose);

void runSimulation(world_t& world, int numRounds, bool verbose);

void printGrid(const grid_t& grid);

#endif  // SIMULATION_H
