# Day [4]: [First Part](https://adventofcode.com/2024/day/4)

## Problem Description

The task is to find the occurrences of the word **"XMAS"** in a grid of letters. Words can be oriented in any of the following directions:
1. Horizontally (left-to-right or right-to-left).
2. Vertically (top-to-bottom or bottom-to-top).
3. Diagonally (in all four diagonal directions).  

Words can overlap other occurrences, and all instances must be counted. The overlapping makes the problem considerably more difficult.

---

## Solution

- **Approach:**  
  Iterate through each cell in the grid. For each cell, check in all eight directions to see if the word **"XMAS"** appears. This involves:
  1. Defining the eight directions to explore.
  2. For each starting cell, checking up to four letters in the chosen direction.
  3. Validating the word matches **"XMAS"** in that direction.

- **Time Complexity:** O(N × M × D × L)  
  - N: Number of rows in the grid.  
  - M: Number of columns in the grid.  
  - D: Number of directions (8).  
  - L: Length of the word (**"XMAS"**).

- **Space Complexity:** O(N × M)  
  - The grid.

---

## Notes
- Overlapping occurrences of **"XMAS"** are counted individually.  

---

# Day [4]: [Second Part](https://adventofcode.com/2024/day/4)

## Problem Description

Identify patterns shaped like an **X-MAS**, where two diagonals of length 3 form an "X". Each diagonal must spell "MAS" or "SAM", and their center letter overlaps.

---

## Solution

- **Approach:**  
  1. Iterate through each cell in the grid, treating it as a potential center (`A`) of the "X".  
  2. Check the four diagonals (`top-left ↔ bottom-right` and `top-right ↔ bottom-left`).  
  3. For each diagonal:
     - Ensure it fits within the grid boundaries.
     - Validate that each diagonal spells either **"MAS"** or **"SAM"**.  
  4. If both diagonals are valid, count the "X-MAS".

- **Time Complexity:** O(N × M × D × L)  
  - N: Number of rows in the grid.  
  - M: Number of columns in the grid.  
  - D: Number of diagonals (4).  
  - L: Length of each diagonal (3).

- **Space Complexity:** O(1)  
  - Uses constant space beyond the input grid.

---

## Notes
- Both diagonals must independently validate as "MAS" or "SAM".  
- Overlapping patterns can occur, and each valid "X-MAS" is counted separately.  
- Edge cases include grids too small to form a valid "X-MAS".