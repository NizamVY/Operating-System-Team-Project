# OS-Page-Replacement-Algorithms

A modular C++ simulation of virtual memory page replacement algorithms (**FIFO**, **LRU**, and **Optimal**). This project reads a sequence of page references and a frame allocation count, simulates the memory replacement process step by step, and outputs frame snapshots along with hit/fault performance metrics.

---

## 🚀 Features

* **Multiple Replacement Policies:** Implements **FIFO** (First-In, First-Out), **LRU** (Least Recently Used), and **Optimal** (OPT) page replacement algorithms on shared simulation data structures.
* **Robust Error Handling:** Validates inputs against zero/negative frame counts, negative page numbers, invalid characters, and empty sequences.
* **Step-by-Step Simulation:** Displays each step, showing whether a request resulted in a **HIT** or a **FAULT**, alongside the current state of memory frames.
* **Performance Metrics:** Calculates and outputs total hits, total page faults, and the final page fault rate percentage.

---

## 🛠️ Technologies

* **Language:** C++
* **Standard:** C++17 (compatible with C++11 or later)

---

## 📁 Project Structure

```text
📦 Operating-System-Team-Project
 ┣ 📂 include
 ┃ ┣ 📜 types.hpp          # Shared simulation input/step/result structs
 ┃ ┣ 📜 lru.hpp            # LRU algorithm interface
 ┃ ┗ 📜 optimal.hpp        # Optimal algorithm interface
 ┣ 📂 src
 ┃ ┣ 📜 lru.cpp            # LRU page replacement implementation
 ┃ ┗ 📜 optimal.cpp        # Optimal page replacement implementation
 ┣ 📂 examples
 ┃ ┣ 📜 lru_demo.cpp       # LRU unit tests and step-by-step demo
 ┃ ┗ 📜 optimal_demo.cpp   # Optimal unit tests and step-by-step demo
 ┣ 📜 Fifo.cpp             # Standalone FIFO simulation with input.txt parsing
 ┣ 📜 input.txt            # Sample input file (frame count and page references)
 ┗ 📜 README.md            # Project documentation