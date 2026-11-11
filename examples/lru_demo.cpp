#include "lru.hpp"

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
    // Accessing page 1 again protects it from replacement (unlike FIFO).
    auto result = simulateLRU({3, {1, 2, 3, 1, 4}});
    check(result.hits == 1, "Basic hit count");
    check(result.faults == 4, "Basic fault count");
    check(result.steps.back().frames == std::vector<int>{1, 4, 3},
          "LRU must replace page 2, not page 1");

    // Repeated references should produce hits.
    auto repeated = simulateLRU({2, {5, 5, 5}});
    check(repeated.hits == 2 && repeated.faults == 1, "Repeated page");

    // With one frame, each change of page causes a fault.
    auto single = simulateLRU({1, {1, 2, 2, 1}});
    check(single.hits == 1 && single.faults == 3, "Single frame");

    // Classic textbook sequence: 3 frames -> 12 faults with LRU.
    auto classic = simulateLRU(
        {3, {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1}});
    check(classic.faults == 12 && classic.hits == 8, "Textbook sequence");

    // Empty input is allowed at the algorithm level.
    auto empty = simulateLRU({3, {}});
    check(empty.steps.empty() && empty.hits == 0 && empty.faults == 0,
          "Empty reference sequence");

    bool rejectedZeroFrames = false;
    try {
        simulateLRU({0, {1}});
    } catch (const std::invalid_argument&) {
        rejectedZeroFrames = true;
    }
    check(rejectedZeroFrames, "Reject zero frames");

    bool rejectedNegativePage = false;
    try {
        simulateLRU({3, {1, -2}});
    } catch (const std::invalid_argument&) {
        rejectedNegativePage = true;
    }
    check(rejectedNegativePage, "Reject negative pages");

    std::cout << "All LRU tests passed.\n\n";
}

int main() {
    try {
        runTests();

        SimulationInput input{3, {1, 2, 3, 1, 4}};
        SimulationResult result = simulateLRU(input);

        std::cout << "Algorithm: LRU\n";
        std::cout << "Frames: " << input.frameCount << "\n\n";
        std::cout << "Step\tPage\tResult\tFrames\n";

        for (std::size_t i = 0; i < result.steps.size(); ++i) {
            const StepResult& step = result.steps[i];

            std::cout << i + 1 << '\t' << step.page << '\t'
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
