#ifndef WORLD_ENGINE_H
#define WORLD_ENGINE_H

#include <string>

#include "world_type.h"

// Plugin interface types
// A sensor plugin inspects creature/grid state and returns true or false.
typedef bool (*sensor_fn_t)(const creature_t& creature, const grid_t& grid);
// An action plugin mutates creature and/or grid state.

typedef void (*action_fn_t)(creature_t& creature, grid_t& grid);

struct plugin_entry_t {
    std::string name;
    sensor_fn_t sensor{};  // NULL if this is an action plugin
    action_fn_t action{};  // NULL if this is a sensor plugin
};

bool surroundedPlugin(const creature_t& creature, const grid_t& grid);
void leapPlugin(creature_t& creature, grid_t& grid);

// Plugin registry
void initPluginRegistry();
// EFFECTS: Registers all built-in plugins ("surrounded", "leap").
// Must be called exactly once before initWorld().

plugin_entry_t* findPlugin(const std::string& name);
// EFFECTS: Returns a pointer to the registry entry whose name equals `name`,
// or NULL if no such plugin is registered.

// Grid physics
point_t adjacentPoint(point_t pt, direction_t dir);
// EFFECTS: Returns the grid point one step from `pt` in direction `dir`.

bool isInsideGrid(const grid_t& grid, point_t pt);
// EFFECTS: Returns true iff `pt` is within the grid boundaries (0-based).

creature_t* getCreature(const grid_t& grid, point_t pt);
// REQUIRES: isInsideGrid(grid, pt)
// EFFECTS: Returns a pointer to the creature at `pt`, or NULL if the cell is empty.

direction_t leftFrom(direction_t dir);
// EFFECTS: Returns the direction 90 degrees to the left of 'dir'.

direction_t rightFrom(direction_t dir);
// EFFECTS: Returns the direction 90 degrees to the right of 'dir'.

#endif  // WORLD_ENGINE_H
