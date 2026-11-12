#pragma once

#include "types.hpp"

// Simulates Optimal (OPT) page replacement.
// Throws std::invalid_argument for zero frames or negative page numbers.
SimulationResult simulateOptimal(const SimulationInput& input);