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
