#include "../include/output.hpp"
#include <iostream>
#include <iomanip>

// Function to print step-by-step simulation outputs
void printSimulationSteps(const std::string& algorithmName, const SimulationResult& result, std::size_t frameCount) {
    std::cout << "\nAlgorithm: " << algorithmName << "\n";
    std::cout << "Frame count: " << frameCount << "\n\n";
    
    // Table headers
    std::cout << std::left << std::setw(10) << "Step" 
              << std::setw(10) << "Page" 
              << std::setw(10) << "Result" 
              << "Frames\n";
    std::cout << "--------------------------------------------\n";

    int stepNum = 1;
    for (const auto& step : result.steps) {
        // Row data
        std::cout << std::left << std::setw(10) << stepNum++
                  << std::setw(10) << step.page
                  << std::setw(10) << (step.hit ? "HIT" : "FAULT") 
                  << "[";
        
        // Frame contents (Prints '-' for empty slots)
        for (std::size_t i = 0; i < frameCount; ++i) {
            if (i > 0) std::cout << ' ';
            if (i < step.frames.size()) {
                std::cout << step.frames[i];
            } else {
                std::cout << '-';
            }
        }
        std::cout << "]\n";
    }
}

// Function to print the comparison table
void printComparisonTable(std::size_t totalReferences, 
                          const SimulationResult& fifoRes, 
                          const SimulationResult& lruRes, 
                          const SimulationResult& optRes) {
                              
    // A small helper lambda to calculate the fault rate
    auto calcRate = [&](std::size_t faults) {
        return (totalReferences == 0) ? 0.0 : (100.0 * faults / totalReferences);
    };

    std::cout << "\n=============================================================\n";
    std::cout << "                ALGORITHM COMPARISON RESULTS                 \n";
    std::cout << "=============================================================\n";
    
    // Table headers
    std::cout << std::left << std::setw(15) << "Algorithm" 
              << std::setw(15) << "Total Hits" 
              << std::setw(15) << "Total Faults" 
              << std::setw(15) << "Fault Rate (%)\n";
    std::cout << "-------------------------------------------------------------\n";
    
    // Lambda function to add a row to the table
    auto printRow = [&](const std::string& name, const SimulationResult& res) {
        std::cout << std::left << std::setw(15) << name
                  << std::setw(15) << res.hits
                  << std::setw(15) << res.faults
                  << std::fixed << std::setprecision(2) << std::setw(15) 
                  << calcRate(res.faults) << "\n";
    };

    // Print the rows for FIFO, LRU, and Optimal
    printRow("FIFO", fifoRes);
    printRow("LRU", lruRes);
    printRow("Optimal", optRes);
    std::cout << "=============================================================\n\n";
}
