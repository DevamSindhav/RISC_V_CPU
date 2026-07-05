# RISC-V CPU Simulator Architecture

This document outlines the planned structure for the single-cycle RV32I RISC-V CPU simulator and describes the purpose of each file we will be creating.

## Project Structure (Component-Based)

```text
risc_V_cpu/
├── .gitignore               # Tells Git which compiled/temporary files to ignore
├── risc_V_cpu.slnx          # Visual Studio Solution file (the main workspace container)
├── ARCHITECTURE.md          # A guide to the project's structure
└── risc_V_cpu/              # The actual C++ Project folder
    ├── risc_V_cpu.vcxproj   # Visual Studio Project configuration
    └── src/                 
        ├── core/            # The CPU Brain
        │   ├── CPU.h
        │   └── CPU.cpp
        ├── memory/          # RAM and Data Storage
        │   ├── Memory.h
        │   └── Memory.cpp
        └── main.cpp         # The entry point of the application
```

## File Purposes

### 1. `src/main.cpp`
*   **Purpose:** The starting point of the program. 
*   **What it does:** It will create an instance of our `CPU` and `Memory` classes, load a small RISC-V program into Memory, and tell the CPU to start running its execution loop.

### 2. `src/core/CPU.h` & `src/core/CPU.cpp`
*   **Purpose:** Simulates the actual hardware processor core.
*   **What it does:** 
    *   Holds the 32 General-Purpose Registers (`x0` to `x31`).
    *   Holds the Program Counter (`PC`).
    *   Contains the `step()` function which runs the instruction cycle:
        1. **Fetch:** Grabs the next 32-bit instruction from memory.
        2. **Decode:** Looks at the bits to figure out if it's an `ADD`, `SUB`, `LOAD`, etc.
        3. **Execute:** Performs the math or logic.
        4. **Writeback:** Saves the result back into a register and updates the `PC`.

### 3. `src/memory/Memory.h` & `src/memory/Memory.cpp`
*   **Purpose:** Simulates the computer's RAM.
*   **What it does:**
    *   Holds a large array of `uint8_t` (bytes). 
    *   Provides simple functions like `readWord(address)` to let the CPU fetch 32-bit instructions.
    *   Provides functions like `readByte(address)` and `writeByte(address, data)` so the CPU can execute Load and Store instructions.
