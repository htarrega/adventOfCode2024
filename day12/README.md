# Day 12: [First Part](https://adventofcode.com/2024/day/12)

## Problem Description
The problem involves analyzing a grid of plants where each character represents a plant type. Connected plants of the same type form regions. For each region, we need to calculate the total cost of fencing, where the cost is determined by multiplying the area (number of tiles) by the perimeter (exposed edges).
---

## Solution

- **Approach:** 
1.Read the input grid and create a 2D vector of Tile objects
2.Use a flood-fill algorithm with BFS to assign unique IDs to connected regions of the same plant type
3.Calculate the area (count of tiles) for each region
4.Calculate the perimeter by counting exposed edges for each region
5.Compute the final cost by multiplying area × perimeter for each region and summing the results

- **Time Complexity:** O(N × M) where N and M are the dimensions of the grid 
- **Space Complexity:** O(N × M)

---

## Notes
- I Use BFS instead of DFS for flood fill to ensure efficient region labeling
- The Tile struct stores additional data like coordinates and ID

# Day 12: [Second Part](https://adventofcode.com/2024/day/12)

## Problem Description
Similar to Part 1, but the fencing cost calculation changes to use the number of corners in each region instead of the perimeter. A corner is defined by specific patterns of occupied and empty cells around each tile.
---

## Solution

- **Approach:** 
The difference to part1 has been creating a function that calculates the number of sides per ID. This is done by:
- Checking 2×2 cell patterns around each tile
- Counting corners formed by specific arrangements of same-ID cells
- **Time Complexity:** O(N × M)
- **Space Complexity:** O(N × M)

---

## Notes
- I use a helper function to check if points are in bounds and in the same region