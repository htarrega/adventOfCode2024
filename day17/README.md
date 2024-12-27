## Day 17: [First Part](https://adventofcode.com/2024/day/17)

### Problem Description:
Simulate the behavior of a program that operates on three registers—`A`, `B`, and `C`. The program processes instructions sequentially, modifying the registers, and producing an output based on specific operations. Each instruction has an **opcode** (operation type) and an **operand** (target or value).

---

### Solution

- **Approach:**
    1. Parse the input file to initialize the registers and the program memory.
    2. Loop through the program instructions:
        - Perform mathematical operations like division, modulo, or bitwise XOR.
        - Handle conditional jumps and updates to the program counter.
        - Append results to the output string whenever instructed.
    3. Continue until all instructions are processed, then print the output.

- **Key Operations:**
    - **Division (`opcode 0`)**: Divide `regA` by powers of two based on the operand.
    - **Bitwise XOR (`opcode 1` and `4`)**: Apply XOR to registers.
    - **Modulo (`opcode 2` and `5`)**: Compute values modulo 8, appending results to the output.
    - **Conditional Jump (`opcode 3`)**: Skip instructions if `regA` is non-zero.
    - **Register Updates (`opcode 6` and `7`)**: Adjust the values in registers.

- **Output:** The program builds a string of numbers based on the modulo operation and prints the final result.

---

### Complexity Analysis:

- **Time Complexity:** O(N), where N is the number of instructions. Each instruction is processed exactly once.
- **Space Complexity:** O(1), as the program only tracks three registers and the input instructions.

---

### Notes:
- The program executes a sequence of instructions and manipulates the registers in a structured way, is a CPU!

--- 

## Day 17: [Second Part](https://adventofcode.com/2024/day/17)
### Problem Description:
Find the lowest positive initial value for register A that causes the program to output a copy of itself. The program needs to produce an output sequence that exactly matches its own instruction sequence.

---
### Solution
- **Approach:**
    1. Create a simulation function that executes the program with given register values.
    2. Implement a digit-by-digit search algorithm:
        - Build potential solutions one digit at a time (0-7).
        - Check if each partial solution produces matching output.
        - Match program output from right to left.
    3. Return the first valid value found for register A.
- **Key Components:**
    - **Simulation**: Implements all 8 opcodes and tracks register states.
    - **Recursive Search**: Builds solution incrementally by matching outputs.
    - **Pattern Matching**: Verifies partial matches from the end of sequence.
    - **Binary Operations**: Handles shifts, XOR, and modulo operations.
- **Output:** The smallest initial value for register A that generates the program.

---
### Complexity Analysis:
- **Time Complexity:** O(8^d * n), where d is the number of digits in solution and n is program length.
- **Space Complexity:** O(d) for recursion stack depth.

---
### Notes:
- The solution uses a recursive approach to build the answer digit by digit.
- Early termination occurs when partial solutions don't match expected output.
- The program effectively needs to self-replicate through its output sequence.
- This is an optimization problem requiring efficient search strategies.
---