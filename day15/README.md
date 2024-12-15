# Day 15: [First Part](https://adventofcode.com/2024/day/15)

## Problem Description
Simulate the movement of robots on a grid, updating their positions based on velocity, and calculate a "safety factor" based on the final positions after a set number of cycles.

---

## Solution

- **Approach:** The positions of robots are updated based on their velocities in a cyclic grid. After a fixed number of cycles, the "safety factor" is computed by counting the number of robots in each quadrant and multiplying these counts together.  
- **Time Complexity:** O(N * C)  
- **Space Complexity:** O(N)

---

## Notes
- The robots move cyclically across the grid, and their positions wrap around at the grid edges.
- The safety factor is derived from the distribution of robots in the four quadrants of the grid.

# Day 15: [Second Part](https://adventofcode.com/2024/day/15)

## Problem Description
In this part, robots are moved as a group, and the program prints the grid after each cycle, allowing user interaction to continue or stop the simulation.

---

## Solution

- **Approach:** Similar to Part One, robot's positions are updated in a cyclic grid. After each cycle, the grid is printed, and the user is prompted to continue or quit. The program checks for certain conditions, such as rows and columns with many robots, before proceeding.  
- **Time Complexity:** O(N * C)  
- **Space Complexity:** O(N)

---

## Notes
- I had to research about complex numbers here. Difficult problem.
