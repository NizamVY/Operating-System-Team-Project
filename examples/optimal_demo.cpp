#include "optimal.hpp"

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

void check(bool condition, const std::string& message) {
    if (!condition) {
        throw std::runtime_error("Test failed: " + message);
    }
}

void runTests() {
    // Optimal evicts page 2 (used farthest in the future) while keeping pages 1 and 3.
    auto result = simulateOptimal({3, {1, 2, 3, 4, 1, 3}});
    check(result.hits == 2, "Basic hit count");
    check(result.faults == 4, "Basic fault count");
    check(result.steps[3].frames == std::vector<int>{1, 4, 3},
          "Optimal must evict page 2 on step 4");

    // Sequence from input.txt: 3 frames -> 7 faults, 6 hits.
    auto sampleInput = simulateOptimal(
        {3, {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2}});
    check(sampleInput.faults == 7 && sampleInput.hits == 6,
          "input.txt reference sequence");

    // Classic 20-reference textbook sequence: 3 frames -> 9 faults, 11 hits with Optimal.
    auto classic = simulateOptimal(
        {3, {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1}});
    check(classic.faults == 9 && classic.hits == 11, "Textbook sequence");

    // Repeated references should produce hits after the initial load.
    auto repeated = simulateOptimal({2, {5, 5, 5}});
    check(repeated.hits == 2 && repeated.faults == 1, "Repeated page");

    // With one frame, each page transition causes a fault.
    auto single = simulateOptimal({1, {1, 2, 2, 1}});
    check(single.hits == 1 && single.faults == 3, "Single frame");

    // Empty input is allowed at the algorithm level.
    auto empty = simulateOptimal({3, {}});
    check(empty.steps.empty() && empty.hits == 0 && empty.faults == 0,
          "Empty reference sequence");

    bool rejectedZeroFrames = false;
    try {
        simulateOptimal({0, {1}});
    } catch (const std::invalid_argument&) {
        rejectedZeroFrames = true;
    }
    check(rejectedZeroFrames, "Reject zero frames");

    bool rejectedNegativePage = false;
    try {
        simulateOptimal({3, {1, -2}});
    } catch (const std::invalid_argument&) {
        rejectedNegativePage = true;
    }
    check(rejectedNegativePage, "Reject negative pages");

    std::cout << "All Optimal tests passed.\n\n";
}

int main() {
    try {
        runTests();

        SimulationInput input{3, {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2}};
        SimulationResult result = simulateOptimal(input);

        std::cout << "Algorithm: Optimal\n";
        std::cout << "Frames: " << input.frameCount << "\n\n";
        std::cout << "Step\tPage\tResult\tFrames\n";

        for (std::size_t i = 0; i < result.steps.size(); ++i) {
            const StepResult& step = result.steps[i];

            std::cout << i + 1 << '\t' << step.page << '\\t'
                      << (step.hit ? "HIT" : "FAULT") << "\t[";

            for (std::size_t j = 0; j < input.frameCount; ++j) {
                if (j > 0) std::cout << ' ';
                if (j < step.frames.size()) std::cout << step.frames[j];
                else std::cout << '-';
            }
            std::cout << "]\n";
        }

        double faultRate = input.references.empty()
            ? 0.0
            : 100.0 * result.faults / input.references.size();

        std::cout << "\nHits: " << result.hits;
        std::cout << "\nFaults: " << result.faults;
        std::cout << "\nFault rate: " << std::fixed << std::setprecision(2)
                  << faultRate << "%\n";
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
    return 0;
}