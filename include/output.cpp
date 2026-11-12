#pragma once

#include <string>
#include "types.hpp"

// Prints the step-by-step memory (frame) state and hit/fault result for each algorithm
void printSimulationSteps(const std::string& algorithmName, const SimulationResult& result, std::size_t frameCount);

// Prints a comparison table showing total hits, faults, and fault rates for all algorithms
void printComparisonTable(std::size_t totalReferences, const SimulationResult& fifoRes, const SimulationResult& lruRes, const SimulationResult& optRes);
