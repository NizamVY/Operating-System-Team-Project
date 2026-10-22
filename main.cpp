#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

int main() {
    // 1. Open the input file.
    std::ifstream inputFile("input.txt");

    if (!inputFile) {
        std::cerr << "Error: Cannot open input.txt\n";
        return 1;
    }

    // 2. Read and validate the number of frames.
    int frameCount;

    if (!(inputFile >> frameCount) || frameCount <= 0) {
        std::cerr << "Error: Frame count must be a positive integer.\n";
        return 1;
    }

    // 3. Read the page-reference sequence.
    std::vector<int> references;
    int page;

    while (inputFile >> page) {
        if (page < 0) {
            std::cerr << "Error: Page numbers cannot be negative.\n";
            return 1;
        }

        references.push_back(page);
    }

    if (!inputFile.eof()) {
        std::cerr << "Error: Input must contain only valid integers.\n";
        return 1;
    }

    if (references.empty()) {
        std::cerr << "Error: Provide at least one page reference.\n";
        return 1;
    }

    // 4. Set up the simulated memory and counters.
    std::vector<int> frames;

    int nextVictim = 0;
    int hits = 0;
    int faults = 0;
    int step = 0;

    std::cout << "Algorithm: FIFO\n";
    std::cout << "Frame count: " << frameCount << "\n\n";
    std::cout << "Step\tPage\tResult\tFrames\n";

    // 5. Process each page request.
    for (int requestedPage : references) {
        ++step;

        bool hit =
            std::find(frames.begin(), frames.end(), requestedPage)
            != frames.end();

        if (hit) {
            ++hits;
        } else {
            ++faults;

            if (frames.size() < static_cast<std::size_t>(frameCount)) {
                frames.push_back(requestedPage);
            } else {
                frames[nextVictim] = requestedPage;
                nextVictim = (nextVictim + 1) % frameCount;
            }
        }

        // 6. Display memory after this request.
        std::cout << step << '\t'
                  << requestedPage << '\t'
                  << (hit ? "HIT" : "FAULT") << "\t[";

        for (int i = 0; i < frameCount; ++i) {
            if (i > 0) {
                std::cout << ' ';
            }

            if (i < static_cast<int>(frames.size())) {
                std::cout << frames[i];
            } else {
                std::cout << '-';
            }
        }

        std::cout << "]\n";
    }

    // 7. Display the final totals.
    double faultRate = 100.0 * faults / references.size();

    std::cout << "\nHits: " << hits << '\n';
    std::cout << "Faults: " << faults << '\n';

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Fault rate: " << faultRate << "%\n";

    return 0;
}
