#include "../include/output.hpp"
#include "../include/types.hpp"
#include <iostream>
#include <vector>

int main() {
    // 1. Create dummy data to test the output module
    std::size_t frameCount = 3;
    std::size_t totalReferences = 20;

    SimulationResult dummyFifo;
    dummyFifo.hits = 5;
    dummyFifo.faults = 15;
    
    // Add one dummy step to show how step printing works
    StepResult dummyStep;
    dummyStep.page = 7;
    dummyStep.hit = false;
    dummyStep.frames = {7, 0, 1};
    dummyFifo.steps.push_back(dummyStep);

    SimulationResult dummyLru;
    dummyLru.hits = 8;
    dummyLru.faults = 12;

    SimulationResult dummyOpt;
    dummyOpt.hits = 11;
    dummyOpt.faults = 9;

    std::cout << "Testing Output and Comparison Module...\n";

    // 2. Test Step-by-Step Output
    printSimulationSteps("FIFO", dummyFifo, frameCount);

    // 3. Test Comparison Table
    printComparisonTable(totalReferences, dummyFifo, dummyLru, dummyOpt);

    return 0;
}
