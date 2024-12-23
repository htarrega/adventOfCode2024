# Day [8]: [First Part](https://adventofcode.com/2024/day/8)

## Problem Description

The task requires processing an input grid to determine the positions of antinnodes generated by mirroring antennas. The goal is to find "antinodes" based on specific geometric relationships between antenna pairs.

## Solution

- **Approach:**  
  1. **Parse Input:** Load the grid from a file, where each cell contains either an antenna (denoted by a character) or an empty space (denoted by `.`).
  2. **Identify Antennas:** Extract positions of antennas and group them by their corresponding characters.
  3. **Find Antinodes:** For each pair of antennas, compute their geometric relationship and determine the potential antinode positions in the grid. Mark new antinodes in the grid to prevent duplication.
  4. **Count Antinodes:** Count all valid antinode positions added during the process.

- **Time Complexity:** O(A² * G)  
  - A: Total number of antennas.  
  - G: Size of the grid.  

- **Space Complexity:** O(A)  
  - A: Space for storing antenna positions.

---

## Notes
- This part uses simple pairwise geometric relationships to identify antinodes, leveraging vector arithmetic.
- New antinodes are marked directly on the grid for easy deduplication.

---

# Day [8]: [Second Part](https://adventofcode.com/2024/day/8)

## Problem Description

In the second part, the task expands to consider additional geometric configurations for determining antinodes. This includes handling collinear points and extending lines to discover potential antinode positions outside the immediate vicinity of the antennas.

---

## Solution

- **Approach:**  
  1. **Parse Input:** Load the grid and group antennas as in the first part.
  2. **Handle Collinear Points:** For each pair of antennas, identify all collinear antennas and add them to a set of antinodes.
  3. **Extend Lines:** For each pair, extend the line formed by the antennas in both directions until it goes out of bounds. Add all points on this extended line to the antinode set.
  4. **Count Unique Antinodes:** The total number of unique antinodes is determined using a set.

- **Time Complexity:** O(A² * G)  
  - A: Total number of antennas.  
  - G: Size of the grid.

- **Space Complexity:** O(A + P)  
  - A: Space for storing antenna positions.  
  - P: Space for the set of antinodes.

---

## Notes
- The algorithm uses a set to ensure that antinodes are counted uniquely, irrespective of how they are derived.
- Efficient handling of extended lines is achieved by iterating step-by-step until the boundaries of the grid are reached.

---
