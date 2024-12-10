# Day [10]: [First Part](https://adventofcode.com/2024/day/10)

## Problem Description

The task involves exploring a grid-based trail network where each cell represents an elevation level. The goal is to find trailheads (`0`) and calculate scores by traversing to reachable peaks (`9`) along increasing elevation paths.

## Solution

- **Approach:**  
  1. **Parse Input:** Read the grid from the input file, where each cell contains an elevation value (0-9).  
  2. **Identify Trailheads:** Locate all cells with elevation `0`.  
  3. **Traverse from Trailheads:** For each trailhead, use Breadth-First Search (BFS) to explore the grid, ensuring that traversal only moves to adjacent cells with increasing elevation. Mark visited cells to avoid redundant computations.  
  4. **Score Calculation:** Count all reachable peaks (`9`) for each trailhead, summing them to determine the total score.

- **Time Complexity:** O(N * M * T)  
  - N: Number of grid rows.  
  - M: Number of grid columns.  
  - T: Number of trailheads.

- **Space Complexity:** O(N * M)  
  - For storing the grid and a visited matrix.

---

## Notes
- I originally solved the second part while attempting to solve the first one. Later, I came up with the solution for part one by introducing a visited matrix. For the second part, I simply removed the visited matrix to allow revisiting cells.

---

# Day [10]: [Second Part](https://adventofcode.com/2024/day/10)

## Problem Description

In the second part, the traversal rules are modified to allow revisiting cells. This enables cumulative exploration of all peaks (`9`) reachable from each trailhead across multiple paths.

---

## Solution

- **Approach:**  
  1. **Parse Input:** Read and process the grid as in the first part.  
  2. **Revisit Cells:** Remove the restriction on marking cells as visited, allowing multiple paths to explore the same grid area.  
  3. **Traverse from Trailheads:** Use BFS for exploration, following elevation rules but allowing revisits.  
  4. **Score Calculation:** Count all reachable peaks (`9`) for each trailhead, summing them to determine the total score.

- **Time Complexity:** O(N * M * T)  
  - N: Number of grid rows.  
  - M: Number of grid columns.  
  - T: Number of trailheads.

- **Space Complexity:** O(N * M)  
  - For storing the grid.

---

## Notes
- Allowing cell revisits increases flexibility but may lead to longer runtimes on denser grids.  

---
