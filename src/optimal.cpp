#include "optimal.hpp"

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <vector>

namespace {

// Returns the index in frames of the page whose next use is farthest in the future
// (or never used again).
std::size_t selectVictimFrame(const std::vector<int>& frames,
                              const std::vector<int>& references,
                              std::size_t currentTime) {
    std::size_t victimIndex = 0;
    std::size_t farthestNextUse = 0;

    for (std::size_t i = 0; i < frames.size(); ++i) {
        int candidatePage = frames[i];
        std::size_t nextUse = references.size(); // Sentinel: never referenced again.

        for (std::size_t future = currentTime + 1; future < references.size(); ++future) {
            if (references[future] == candidatePage) {
                nextUse = future;
                break;
            }
        }

        // A page that is never used again is an immediate optimal victim.
        if (nextUse == references.size()) {
            return i;
        }

        if (nextUse > farthestNextUse) {
            farthestNextUse = nextUse;
            victimIndex = i;
        }
    }

    return victimIndex;
}

} // namespace

SimulationResult simulateOptimal(const SimulationInput& input) {
    if (input.frameCount == 0) {
        throw std::invalid_argument("Frame count must be greater than zero.");
    }

    SimulationResult result;

    // Pages currently loaded in memory.
    std::vector<int> frames;

    for (std::size_t time = 0; time < input.references.size(); ++time) {
        int requestedPage = input.references[time];

        if (requestedPage < 0) {
            throw std::invalid_argument("Page numbers cannot be negative.");
        }

        // Search for the requested page in memory.
        auto position = std::find(frames.begin(), frames.end(), requestedPage);
        bool hit = (position != frames.end());

        if (hit) {
            ++result.hits;
        } else {
            ++result.faults;

            if (frames.size() < input.frameCount) {
                // There is still an empty frame.
                frames.push_back(requestedPage);
            } else {
                // Replace the page that will not be used for the longest time.
                std::size_t victimIndex =
                    selectVictimFrame(frames, input.references, time);
                frames[victimIndex] = requestedPage;
            }
        }

        // Save a copy of memory after this request.
        result.steps.push_back({requestedPage, hit, frames});
    }

    return result;
}