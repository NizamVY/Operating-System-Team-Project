#pragma once

#include "types.hpp"

// Simulates Least Recently Used (LRU) page replacement.
// Throws std::invalid_argument for zero frames or negative page numbers.
SimulationResult simulateLRU(const SimulationInput& input);
