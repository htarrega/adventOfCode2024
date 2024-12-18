# Day 18: [Part 1](https://adventofcode.com/2024/day/18)

## Problem Description
In this part, the objective is to find the shortest path in a \(71 \times 71\) grid from the top-left corner \((0, 0)\) to the bottom-right corner \((70, 70)\). The grid contains corrupted cells, which are impassable. These corrupted coordinates are loaded from an input file, and only the first kilobyte (1024 bytes) of corrupted cells are considered.

---

## Solution

- **Approach:**  
  I implemented **Breadth-First Search (BFS)** to find the shortest path in the grid. BFS ensures that the shortest path is guaranteed in an unweighted grid. The first kilobyte of corrupted cells is marked as impassable before starting the search.  
- **Steps:**  
  1. Load corrupted coordinates from the input file using `loadCorrupted`.  
  2. Initialize a \(71 \times 71\) grid, marking all cells as passable (`true`).  
  3. Update the grid to mark the first 1024 corrupted cells as impassable (`false`).  
  4. Use BFS from \((0, 0)\) to explore neighbors until the destination \((70, 70)\) is reached.  
- **Time Complexity:** \(O(N \times M)\), where \(N, M = 71\), because BFS processes each cell once.  
- **Space Complexity:** \(O(N \times M)\), for the grid and visited states.

---

## Notes
- BFS is ideal for finding the shortest path as it explores all possible routes in a systematic manner.  
---

# Day 18: [Part 2](https://adventofcode.com/2024/day/18)

## Problem Description
This part introduces a new challenge: simulate corruption dynamically. At each step, a new cell is marked as corrupted, and we check if a path from \((0, 0)\) to \((70, 70)\) still exists. The task is to determine the first corrupted cell that completely blocks the path.

---

## Solution

- **Approach:**  
  The solution involves progressively marking cells as corrupted and checking if the destination is still reachable using BFS. When no path exists, the current corrupted cell is identified as the blocking byte.  
- **Steps:**  
  1. Load corrupted coordinates from the input file using `loadCorrupted`.  
  2. For each corrupted coordinate:  
     - Mark the cell as impassable in the grid.  
     - Use `hasPathToExit` to perform a BFS and verify if a path still exists from \((0, 0)\) to \((70, 70)\).  
     - If no path exists, print the coordinates of the blocking byte and exit.  
- **Time Complexity:** \(O(B \times N \times M)\), where \(B\) is the number of corrupted cells. Each byte triggers a BFS over the grid.  
- **Space Complexity:** \(O(N \times M)\), for the grid and visited states.

---

## Notes
