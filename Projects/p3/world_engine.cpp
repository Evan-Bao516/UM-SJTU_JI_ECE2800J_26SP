/*
// Critical Thinking: What is the contract (interface) that every action plugin must satisfy?
// Why is it defined at this layer rather than in simulation.h ?
// Answer: 1. It must match the signature "void (*action_fn_t)(creature_t &creature, grid_t &grid)".
//            It changes the creature/grid state.
//         2. It isolates pure physics and grid manipulation from the simulation logic.
*/

#include "world_engine.h"

#include <cstddef>
#include <string>

namespace {
plugin_entry_t pluginRegistry[MAX_PLUGIN_TYPES];
unsigned int numRegisteredPlugins = 0;
}  // namespace

direction_t leftFrom(direction_t dir) {
    switch (dir) {
        case direction_t::NORTH:
            return direction_t::WEST;
        case direction_t::WEST:
            return direction_t::SOUTH;
        case direction_t::SOUTH:
            return direction_t::EAST;
        case direction_t::EAST:
            return direction_t::NORTH;
    }
    return direction_t::NORTH;
}

direction_t rightFrom(direction_t dir) {
    switch (dir) {
        case direction_t::NORTH:
            return direction_t::EAST;
        case direction_t::EAST:
            return direction_t::SOUTH;
        case direction_t::SOUTH:
            return direction_t::WEST;
        case direction_t::WEST:
            return direction_t::NORTH;
    }
    return direction_t::NORTH;
}

point_t adjacentPoint(point_t pt, direction_t dir) {
    point_t next_pt = pt;
    switch (dir) {
        case direction_t::NORTH:
            next_pt.r -= 1;
            break;
        case direction_t::SOUTH:
            next_pt.r += 1;
            break;
        case direction_t::EAST:
            next_pt.c += 1;
            break;
        case direction_t::WEST:
            next_pt.c -= 1;
            break;
    }
    return next_pt;
}

bool isInsideGrid(const grid_t& grid, point_t pt) {
    if (pt.r < 0 || pt.c < 0) {
        return false;
    }
    return (static_cast<unsigned int>(pt.r) < grid.height) && (static_cast<unsigned int>(pt.c) < grid.width);
}

creature_t* getCreature(const grid_t& grid, point_t pt) {
    return grid.squares[pt.r][pt.c];
}

bool surroundedPlugin(const creature_t& creature, const grid_t& grid) {
    const direction_t dirs[] = {direction_t::NORTH, direction_t::EAST, direction_t::SOUTH, direction_t::WEST};
    for (int i = 0; i < 4; ++i) {
        const point_t adj = adjacentPoint(creature.location, dirs[i]);
        if (isInsideGrid(grid, adj) && getCreature(grid, adj) == nullptr) {
            return false;
        }
    }
    return true;
}

void leapPlugin(creature_t& creature, grid_t& grid) {
    const point_t step1 = adjacentPoint(creature.location, creature.direction);
    if (!isInsideGrid(grid, step1) || getCreature(grid, step1) != nullptr) {
        return;
    }
    const point_t step2 = adjacentPoint(step1, creature.direction);
    point_t final_dest = step1;
    if (isInsideGrid(grid, step2) && getCreature(grid, step2) == nullptr) {
        final_dest = step2;
    }
    grid.squares[creature.location.r][creature.location.c] = nullptr;
    creature.location = final_dest;
    grid.squares[final_dest.r][final_dest.c] = &creature;
}

void initPluginRegistry() {
    numRegisteredPlugins = 0;
    pluginRegistry[numRegisteredPlugins].name = "surrounded";
    pluginRegistry[numRegisteredPlugins].sensor = surroundedPlugin;
    pluginRegistry[numRegisteredPlugins].action = nullptr;
    numRegisteredPlugins++;
    pluginRegistry[numRegisteredPlugins].name = "leap";
    pluginRegistry[numRegisteredPlugins].sensor = nullptr;
    pluginRegistry[numRegisteredPlugins].action = leapPlugin;
    numRegisteredPlugins++;
}

plugin_entry_t* findPlugin(const std::string& name) {
    for (unsigned int i = 0; i < numRegisteredPlugins; ++i) {
        if (pluginRegistry[i].name == name) {
            return &pluginRegistry[i];
        }
    }
    return nullptr;
}
