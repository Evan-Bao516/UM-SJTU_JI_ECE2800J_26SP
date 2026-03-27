/*
// Crtical Thinking: Give one concrete example in your code where dispatch through a function pointer
//                   replaces what would otherwise be a long if-else chain over plugin names.
//                   Why is the function pointer version better?
// Answer: 1. Inside the function void simulateCreature(creature_t &creature, grid_t &grid, bool verbose),
//            the execution of the CALLPLUGIN opcode uses dispatch through a function pointer:
//            plugin->action(creature, grid);. Without this, we would need a long chain like
//            if (pName == "leap") leapPlugin(...); else if (pName == "fly") flyPlugin(...);.
//         2. Using a function pointer enforces the Open/Closed Principle and strict decoupling.
//            It allows us to add infinite new plugins in Layer 2 without ever modifying the core
//            simulation engine in Layer 3.
//            Furthermore, it keeps the code clean and readable by replacing a massive if-else chain
//            with a single dispatch line.
*/

#include "simulation.h"

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using std::cout;
using std::ifstream;
using std::string;

namespace {
instruction_t getInstruction(const creature_t& creature) {
    if (creature.programID < 1 || creature.programID > creature.species->programSize) {
        std::cerr << "Fatal Error: programID out of bounds for species " << creature.species->name << "!\n";
        exit(1);
    }
    return creature.species->program[creature.programID - 1];
}

bool parseOpcode(const string& token, opcode_t& op) {
    const string opNames[] = {"hop",    "left",   "right", "infect",     "ifempty", "ifenemy",
                              "ifsame", "ifwall", "go",    "callplugin", "ifplugin"};
    for (size_t i = 0; i < sizeof(opNames) / sizeof(opNames[0]); ++i) {
        if (token == opNames[i]) {
            op = static_cast<opcode_t>(i);
            return true;
        }
    }
    return false;
}

bool parseDirection(const string& dirStr, direction_t& dir) {
    for (int i = 0; i < 4; ++i) {
        if (dirStr == directName[i] || dirStr == directShortName[i]) {
            dir = static_cast<direction_t>(i);
            return true;
        }
    }
    return false;
}

void parseOneSpecies(species_t& species, const string& dir) {
    string spPath = dir + "/" + species.name;
    ifstream spIn(spPath);
    if (!spIn) {
        cout << "Error: Cannot open file " << spPath << "!\n";
        exit(0);
    }
    string token;
    while (spIn >> token) {
        if (token == "plugin") {
            string pluginName;
            spIn >> pluginName;
            if (findPlugin(pluginName) == nullptr) {
                cout << "Error: Plugin " << pluginName << " is not registered!\n";
                exit(0);
            }
            if (species.numPlugins < MAX_PLUGINS) {
                species.pluginNames[species.numPlugins] = pluginName;
                species.numPlugins++;
            }
        } else {
            if (species.programSize >= MAXPROGRAM) {
                cout << "Error: Too many instructions for species " << species.name << "!\n";
                cout << "Maximal number of instructions is " << MAXPROGRAM << ".\n";
                exit(0);
            }
            opcode_t oper = opcode_t::HOP;
            if (!parseOpcode(token, oper)) {
                cout << "Error: Instruction " << token << " is not recognized!\n";
                exit(0);
            }
            instruction_t& inst = species.program[species.programSize];
            inst.op = oper;
            inst.pluginSlot = 0;
            if (oper == opcode_t::IFEMPTY || oper == opcode_t::IFENEMY || oper == opcode_t::IFSAME ||
                oper == opcode_t::IFWALL || oper == opcode_t::GO || oper == opcode_t::CALLPLUGIN) {
                spIn >> inst.address;
            } else if (oper == opcode_t::IFPLUGIN) {
                spIn >> inst.pluginSlot >> inst.address;
            }
            species.programSize++;
        }
    }
    spIn.close();
}

void parseAllSpecies(world_t& world, const string& speciesFile) {
    ifstream sumIn(speciesFile);
    if (!sumIn) {
        cout << "Error: Cannot open file " << speciesFile << "!\n";
        exit(0);
    }
    string dir;
    sumIn >> dir;
    string spName;
    while (sumIn >> spName) {
        if (world.numSpecies >= MAXSPECIES) {
            cout << "Error: Too many species!\n";
            cout << "Maximal number of species is " << MAXSPECIES << ".\n";
            exit(0);
        }
        world.species[world.numSpecies].name = spName;
        world.species[world.numSpecies].programSize = 0;
        world.species[world.numSpecies].numPlugins = 0;
        world.numSpecies++;
    }
    sumIn.close();
    for (unsigned int i = 0; i < world.numSpecies; ++i) {
        parseOneSpecies(world.species[i], dir);
    }
}

void parseWorld(world_t& world, const string& worldFile) {
    ifstream wIn(worldFile);
    if (!wIn) {
        cout << "Error: Cannot open file " << worldFile << "!\n";
        exit(0);
    }
    unsigned int height = 0;
    unsigned int width = 0;
    wIn >> height;
    if (height < 1 || height > MAXHEIGHT) {
        cout << "Error: The grid height is illegal!\n";
        cout << "A legal grid height is at least 1 and at most " << MAXHEIGHT << ".\n";
        exit(0);
    }
    wIn >> width;
    if (width < 1 || width > MAXWIDTH) {
        cout << "Error: The grid width is illegal!\n";
        cout << "A legal grid width is at least 1 and at most " << MAXWIDTH << ".\n";
        exit(0);
    }
    world.grid.height = height;
    world.grid.width = width;
    string spName;
    string dirName;
    int row = 0;
    int col = 0;
    while (wIn >> spName >> dirName >> row >> col) {
        if (world.numCreatures >= MAXCREATURES) {
            cout << "Error: Too many creatures!\n";
            cout << "Maximal number of creatures is " << MAXCREATURES << ".\n";
            exit(0);
        }
        species_t* species = nullptr;
        for (unsigned int i = 0; i < world.numSpecies; ++i) {
            if (world.species[i].name == spName) {
                species = &world.species[i];
                break;
            }
        }
        if (species == nullptr) {
            cout << "Error: Species " << spName << " not found!\n";
            exit(0);
        }
        direction_t dir = direction_t::EAST;
        if (!parseDirection(dirName, dir)) {
            cout << "Error: Direction " << dirName << " is not recognized!\n";
            exit(0);
        }
        const point_t point = {row, col};
        if (!isInsideGrid(world.grid, point)) {
            cout << "Error: Creature (" << spName << " " << dirName << " " << row << " " << col
                 << ") is out of bound!\n";
            cout << "The grid size is " << height << "-by-" << width << ".\n";
            exit(0);
        }
        const creature_t* existing = getCreature(world.grid, point);
        if (existing != nullptr) {
            string existDirName = directName[static_cast<int>(existing->direction)];
            cout << "Error: Creature (" << spName << " " << dirName << " " << row << " " << col
                 << ") overlaps with creature (" << existing->species->name << " " << existDirName << " "
                 << existing->location.r << " " << existing->location.c << ")!\n";
            exit(0);
        }
        creature_t& creature = world.creatures[world.numCreatures];
        creature.location = point;
        creature.direction = dir;
        creature.species = species;
        creature.programID = 1;
        world.grid.squares[row][col] = &creature;
        world.numCreatures++;
    }
    wIn.close();
}

void printInstructionVerbose(const creature_t& creature, const instruction_t& inst) {
    cout << "Instruction " << creature.programID << ": ";
    const string opNames[] = {"hop",    "left",   "right", "infect",     "ifempty", "ifenemy",
                              "ifsame", "ifwall", "go",    "callplugin", "ifplugin"};
    const string opStr = opNames[static_cast<int>(inst.op)];
    cout << opStr;
    if (inst.op == opcode_t::IFEMPTY || inst.op == opcode_t::IFENEMY || inst.op == opcode_t::IFSAME ||
        inst.op == opcode_t::IFWALL || inst.op == opcode_t::GO || inst.op == opcode_t::CALLPLUGIN) {
        cout << " " << inst.address;
    } else if (inst.op == opcode_t::IFPLUGIN) {
        cout << " " << inst.pluginSlot << " " << inst.address;
    }
    cout << "\n";
}

bool checkCondition(const creature_t& creature, const grid_t& grid, const instruction_t& inst, const point_t& targetPt,
                    const creature_t* targetCreature) {
    switch (inst.op) {
        case opcode_t::IFEMPTY:
            return isInsideGrid(grid, targetPt) && targetCreature == nullptr;
        case opcode_t::IFWALL:
            return !isInsideGrid(grid, targetPt);
        case opcode_t::IFSAME:
            return isInsideGrid(grid, targetPt) && targetCreature != nullptr &&
                   targetCreature->species == creature.species;
        case opcode_t::IFENEMY:
            return isInsideGrid(grid, targetPt) && targetCreature != nullptr &&
                   targetCreature->species != creature.species;
        case opcode_t::IFPLUGIN: {
            const string pName = creature.species->pluginNames[inst.pluginSlot];
            const plugin_entry_t* plugin = findPlugin(pName);
            if (plugin != nullptr && plugin->sensor != nullptr) {
                return plugin->sensor(creature, grid);
            }
            return false;
        }
        default:
            return false;
    }
}

bool executeInstruction(creature_t& creature, grid_t& grid, const instruction_t& inst) {
    const point_t targetPt = adjacentPoint(creature.location, creature.direction);
    creature_t* targetCreature = isInsideGrid(grid, targetPt) ? getCreature(grid, targetPt) : nullptr;
    switch (inst.op) {
        case opcode_t::HOP:
            if (isInsideGrid(grid, targetPt) && targetCreature == nullptr) {
                grid.squares[creature.location.r][creature.location.c] = nullptr;
                creature.location = targetPt;
                grid.squares[targetPt.r][targetPt.c] = &creature;
            }
            creature.programID++;
            return true;
        case opcode_t::LEFT:
            creature.direction = leftFrom(creature.direction);
            creature.programID++;
            return true;
        case opcode_t::RIGHT:
            creature.direction = rightFrom(creature.direction);
            creature.programID++;
            return true;
        case opcode_t::INFECT:
            if (isInsideGrid(grid, targetPt) && targetCreature != nullptr) {
                if (targetCreature->species != creature.species) {
                    targetCreature->species = creature.species;
                    targetCreature->programID = 1;
                }
            }
            creature.programID++;
            return true;
        case opcode_t::CALLPLUGIN: {
            const string pName = creature.species->pluginNames[inst.address];
            const plugin_entry_t* plugin = findPlugin(pName);
            if (plugin != nullptr && plugin->action != nullptr) {
                plugin->action(creature, grid);
            }
            creature.programID++;
            return true;
        }
        case opcode_t::GO:
            creature.programID = inst.address;
            return false;
        case opcode_t::IFEMPTY:
        case opcode_t::IFWALL:
        case opcode_t::IFSAME:
        case opcode_t::IFENEMY:
        case opcode_t::IFPLUGIN:
            if (checkCondition(creature, grid, inst, targetPt, targetCreature)) {
                creature.programID = inst.address;
            } else {
                creature.programID++;
            }
            return false;
        default:
            return false;
    }
}
}  // namespace

bool initWorld(world_t& world, const string& speciesFile, const string& worldFile) {
    initPluginRegistry();
    for (unsigned int row = 0; row < MAXHEIGHT; ++row) {
        for (unsigned int col = 0; col < MAXWIDTH; ++col) {
            world.grid.squares[row][col] = nullptr;
        }
    }
    world.numSpecies = 0;
    world.numCreatures = 0;
    parseAllSpecies(world, speciesFile);
    parseWorld(world, worldFile);
    return true;
}

const int MAX_EXECUTION_PER_TURN = 1000;

void simulateCreature(creature_t& creature, grid_t& grid, bool verbose) {
    const string spName = creature.species->name;
    const string dirName = directName[static_cast<int>(creature.direction)];
    const int startR = creature.location.r;
    const int startC = creature.location.c;
    if (verbose) {
        std::cout << "Creature (" << spName << " " << dirName << " " << startR << " " << startC << ") takes action:\n";
    }
    bool turnFinished = false;
    int executionCount = 0;
    opcode_t finalAction = opcode_t::HOP;
    while (!turnFinished) {
        executionCount++;
        if (executionCount > MAX_EXECUTION_PER_TURN) {
            break;
        }
        const instruction_t inst = getInstruction(creature);
        finalAction = inst.op;
        if (verbose) {
            printInstructionVerbose(creature, inst);
        }
        turnFinished = executeInstruction(creature, grid, inst);
    }
    if (!verbose) {
        const std::string opNames[] = {"hop",    "left",   "right", "infect",     "ifempty", "ifenemy",
                                       "ifsame", "ifwall", "go",    "callplugin", "ifplugin"};
        std::cout << "Creature (" << spName << " " << dirName << " " << startR << " " << startC
                  << ") takes action: " << opNames[static_cast<int>(finalAction)] << "\n";
    }
}

void runSimulation(world_t& world, int rounds, bool verbose) {
    std::cout << "Initial state\n";
    printGrid(world.grid);
    for (int round = 1; round <= rounds; ++round) {
        std::cout << "Round " << round << "\n";
        for (unsigned int i = 0; i < world.numCreatures; ++i) {
            simulateCreature(world.creatures[i], world.grid, verbose);
            if (verbose) {
                printGrid(world.grid);
            }
        }
        if (!verbose) {
            printGrid(world.grid);
        }
    }
}

void printGrid(const grid_t& grid) {
    for (unsigned int row = 0; row < grid.height; ++row) {
        for (unsigned int col = 0; col < grid.width; ++col) {
            if (grid.squares[row][col] == nullptr) {
                cout << "____ ";
            } else {
                string spName = grid.squares[row][col]->species->name;
                string dirStr = directShortName[static_cast<int>(grid.squares[row][col]->direction)];
                string display = spName.substr(0, 2) + "_" + dirStr;
                cout << std::setw(4) << std::left << display << " ";
            }
        }
        cout << "\n";
    }
}
