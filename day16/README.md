# Day 16: [First Part](https://adventofcode.com/2024/day/16)

## Problem Description
Simulate the movement of a Reindeer in a maze, navigating through walls and adjusting direction with penalties. The goal is to find the lowest score to reach the endpoint 'E' from the starting point 'S'. The Reindeer starts facing East and can move forward (1 point) or rotate (1000 points per 90-degree turn).

---

## Solution

- **Approach:** Use Dijkstra's algorithm with a priority queue to explore paths. Each state includes the Reindeer's position `(x, y)`, its current direction (0–3), and accumulated score. Moving forward costs 1 point unless blocked by a wall, and each rotation costs 1000 points.  
- **Time Complexity:** O(N * M * 4), where N and M are the maze dimensions, and 4 represents the possible directions.  
- **Space Complexity:** O(N * M * 4) for visited states and the priority queue.

---

## Notes
- Rotational penalties make minimizing turns critical to achieving the lowest score.
- A 3D visited array ensures no redundant state processing, as the Reindeer's direction affects its movement.

# Day 16: [Second Part](https://adventofcode.com/2024/day/16)

## Problem Description
In this part, the task extends to identifying all tiles in the maze that are part of any optimal path between 'S' and 'E'. These paths must achieve the same minimal score computed in the first part.

---

## Solution

- **Approach:** 
  - Use bidirectional Dijkstra-based pathfinding. First, calculate distances from 'S' to all tiles. Then, compute distances from 'E' to all tiles (considering all four directions).  
  - Identify tiles where the sum of scores from 'S' to the tile and from the tile to 'E' equals the minimal score found in Part 1.  
- **Time Complexity:** O(N * M * 4)  
- **Space Complexity:** O(N * M * 4)

---

## Notes
- Optimal tiles connect two shortest paths: one from 'S' to the tile and the other from the tile to 'E'.
- The bidirectional search ensures efficient identification of optimal paths.