#include "lru.hpp"

#include <algorithm>
#include <stdexcept>
#include <vector>

SimulationResult simulateLRU(const SimulationInput& input) {
    if (input.frameCount == 0) {
        throw std::invalid_argument("Frame count must be greater than zero.");
    }

    SimulationResult result;

    // Pages currently loaded in memory.
    std::vector<int> frames;

    // lastUsed[i] records when frames[i] was last accessed.
    std::vector<std::size_t> lastUsed;

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

            // A hit also makes the page recently used.
            std::size_t frameIndex =
                static_cast<std::size_t>(position - frames.begin());
            lastUsed[frameIndex] = time;
        } else {
            ++result.faults;

            if (frames.size() < input.frameCount) {
                // There is still an empty frame.
                frames.push_back(requestedPage);
                lastUsed.push_back(time);
            } else {
                // The smallest timestamp identifies the least recently used page.
                auto oldest = std::min_element(lastUsed.begin(), lastUsed.end());
                std::size_t victimIndex =
                    static_cast<std::size_t>(oldest - lastUsed.begin());

                frames[victimIndex] = requestedPage;
                lastUsed[victimIndex] = time;
            }
        }

        // Save a copy of memory after this request.
        result.steps.push_back({requestedPage, hit, frames});
    }

    return result;
}
