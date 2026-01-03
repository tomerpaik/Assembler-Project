# Two-Pass Assembler (C Implementation)

A full-scale **Assembler** written in **ANSI C** for a hypothetical 12-bit CPU architecture.
This program translates Assembly language source code (`.as` files) into machine code, implementing the logic of a two-pass compilation process.

**Created in collaboration with:** Roy Kagan.

## 🚀 Overview

The main goal of this project was to build a system that parses complex text inputs, validates syntax, manages symbol tables, and generates binary machine code. It handles:
* **Memory Management:** Dynamic allocation for symbol tables and code images.
* **Data Structures:** Linked lists for handling labels and macro definitions.
* **Bitwise Operations:** Manipulating bits to construct specific CPU instructions.
* **File I/O:** Reading source files and writing `.ob` (Object), `.ent` (Entries), and `.ext` (Externals) files.

## 🛠️ Key Features

* **Macro Expansion:** Detects and deploys macro definitions (`mcro` ... `endmcro`) before compilation.
* **Two-Pass Algorithm:**
    * **First Pass:** Scans code, counts instruction length (IC/DC), builds the **Symbol Table**, and identifies syntax errors.
    * **Second Pass:** Completes the binary encoding using the symbol table and generates output files.
* **Error Handling:** Robust error reporting that identifies specific lines and syntax violations without crashing.
* **Addressing Modes:** Supports Immediate (0), Direct (1), Index (2 - if applicable), and Register Direct (3) addressing.

## 🏗️ How It Works

The assembler processes a file (e.g., `input.as`) through three main stages:

1.  **Pre-Assembly:**
    Scans for macros and expands them, creating an expanded source file (`.am`).

2.  **First Pass:**
    * Parses lines for labels, instructions, and directives (`.data`, `.string`).
    * Calculates the memory address for each instruction (IC - Instruction Counter).
    * Stores labels in a Symbol Table.

3.  **Second Pass:**
    * Re-reads the code.
    * Encodes the instructions into machine word format (Base64/Binary/Special).
    * Resolves symbolic addresses using the table created in Pass 1.
    * Produces the final output files.

## 📂 Output Files

For a valid input file `ps.as`, the program generates:
* `ps.ob`: **Object File** - Contains the memory address and the machine code (in encrypted/base64 format).
* `ps.ent`: **Entry File** - Lists symbols exported to other files.
* `ps.ext`: **External File** - Lists symbols imported from other files and where they are used.

## 💻 Compilation & Usage

This project includes a `makefile` for easy compilation.

1.  **Build the project:**
    ```bash
    make
    ```

2.  **Run the assembler:**
    Pass the file names without the `.as` extension.
    ```bash
    ./assembler input_file1 input_file2
    ```

## 🧠 Tech Stack

* **Language:** C (C90 Standard)
* **Tools:** GCC Compiler, Make, Valgrind (for memory leak testing).
* **Concepts:** Pointers, Structs, Dynamic Memory, Bitwise Manipulation, Parsing.

---
*This project demonstrates low-level system programming skills and a deep understanding of computer architecture.*
