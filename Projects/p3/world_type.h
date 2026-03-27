#ifndef WORLD_TYPE_H
#define WORLD_TYPE_H

#include <cstdint>
#include <string>

const unsigned int MAXSPECIES = 10;        // Max number of species
const unsigned int MAXPROGRAM = 40;        // Max instructions per species
const unsigned int MAXCREATURES = 50;      // Max creatures in the world
const unsigned int MAXHEIGHT = 20;         // Max grid height
const unsigned int MAXWIDTH = 20;          // Max grid width
const unsigned int MAX_PLUGINS = 5;        // Max plugin slots per species
const unsigned int MAX_PLUGIN_TYPES = 20;  // Max entries in global registry

struct point_t {
    int r{};
    int c{};
};
/*
// Type: point_t
// ------------
// A point in the grid. r = row (top is 0, increases downward).
//                      c = column (left is 0, increases rightward).
*/

enum class direction_t : uint8_t { EAST, SOUTH, WEST, NORTH };
/*
// Type: direction_t
// ----------------
// One of the four cardinal directions.
*/

const char* const directName[] = {"east", "south", "west", "north"};
const char* const directShortName[] = {"e", "s", "w", "n"};

enum class opcode_t : uint8_t {
    HOP,
    LEFT,
    RIGHT,
    INFECT,
    IFEMPTY,
    IFENEMY,
    IFSAME,
    IFWALL,
    GO,
    CALLPLUGIN,  // execute action plugin at slot `address`
    IFPLUGIN     // test sensor plugin at slot `pluginSlot`, jump to `address` if
                 // true
};
/*
// Type: opcode_t
// -------------
// All legal instruction opcodes, including the two plugin opcodes.
// CALLPLUGIN: address = plugin slot index (0-based).
// IFPLUGIN:   address = goto step, pluginSlot = plugin slot index.
*/

const char* const opName[] = {"hop",    "left",   "right", "infect",     "ifempty", "ifenemy",
                              "ifsame", "ifwall", "go",    "callplugin", "ifplugin"};

struct instruction_t {
    opcode_t op{};
    unsigned int address{};     // goto step (if*/go), or plugin slot (callplugin)
    unsigned int pluginSlot{};  // plugin slot (ifplugin only; 0 for all others)
};
/*
// Type: instruction_t
// ------------------
// Represents one instruction. For the original nine opcodes, pluginSlot is
// always 0 and address holds the jump target (or is unused for hop/left/right/
// infect). For CALLPLUGIN, address is the plugin slot. For IFPLUGIN, address
// is the goto step and pluginSlot is the plugin slot to test.
*/

struct species_t {
    std::string name;
    unsigned int programSize{};
    instruction_t program[MAXPROGRAM];
    std::string pluginNames[MAX_PLUGINS];  // names from "plugin <name>" lines
    unsigned int numPlugins{};             // number of plugin slots declared
};
/*
// Type: species_t
// ---------------
// A species has a name, a program (array of instructions), and an optional
// list of plugin names declared in its program file. pluginNames[k] is the
// name of the plugin at slot k; it is resolved against the plugin registry
// during world initialisation.
*/

struct creature_t {
    point_t location{};
    direction_t direction{};
    species_t* species{};
    unsigned int programID{};  // 1-based index of the next instruction to execute
};
/*
// Type: creature_t
// ----------------
// A creature's current state. programID starts at 1 for every creature.
*/

struct grid_t {
    unsigned int height{};
    unsigned int width{};
    creature_t* squares[MAXHEIGHT][MAXWIDTH]{};
    // squares[r][c] == NULL means the cell is empty.
};
/*
// Type: grid_t
// ------------
// The physical grid. squares[r][c] points to the creature at (r,c),
// or NULL if empty.
*/

struct world_t {
    unsigned int numSpecies{};
    species_t species[MAXSPECIES];

    unsigned int numCreatures{};
    creature_t creatures[MAXCREATURES]{};

    grid_t grid{};
};
/*
// Type: world_t
// -------------
// The complete simulation state.
*/

#endif  // WORLD_TYPE_H
