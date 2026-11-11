#pragma once

#include <cstddef>
#include <vector>

// Input supplied to a page-replacement algorithm.
struct SimulationInput {
    std::size_t frameCount;
    std::vector<int> references;
};

// Memory state after processing one page request.
struct StepResult {
    int page;
    bool hit;
    std::vector<int> frames;
};

// Complete output of a simulation.
struct SimulationResult {
    std::vector<StepResult> steps;
    std::size_t hits = 0;
    std::size_t faults = 0;
};
