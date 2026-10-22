# OS-Page-Replacement-Algorithms

A clean and efficient C++ simulation of virtual memory management algorithms, focusing on the **FIFO (First-In, First-Out)** page replacement algorithm. This project reads a sequence of page references and a frame allocation count from an input file, simulates the memory swapping process, and outputs step-by-step results along with performance metrics.

---

## 🚀 Features

* **File-Based Input:** Reads frame count and page reference strings dynamically from an external file (`input.txt`).
* **Robust Error Handling:** Validates inputs against negative frame counts, negative page numbers, invalid characters, and empty sequences.
* **Step-by-Step Simulation:** Displays each step, showing whether a request resulted in a **HIT** or a **FAULT**, alongside the current state of memory frames.
* **Performance Metrics:** Calculates and outputs total hits, total page faults, and the final page fault rate percentage.

---

## 🛠️ Technologies

* **Language:** C++
* **Standard:** C++11 or later

---

## 📁 Project Structure

```text
📦 OS-Page-Replacement-Algorithms
 ┣ 📜 main.cpp        # Core simulation logic and I/O parsing
 ┣ 📜 input.txt       # Input file containing frame count and page references
 ┗ 📜 README.md       # Project documentation