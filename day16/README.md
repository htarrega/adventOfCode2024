# Day 16: [Reindeer Maze](https://adventofcode.com/2024/day/16)

## Problem Description
Simulate the movement of a Reindeer in a maze, navigating through walls and adjusting direction with penalties. The goal is to find the lowest score to reach the endpoint 'E' from the starting point 'S'. The Reindeer starts facing East and can move forward (1 point) or rotate (1000 points per 90-degree turn).

---

## Solution

- **Approach:** Use Dijkstra's algorithm with a priority queue to explore paths. Track the lowest score to reach 'E' while considering forward movements and rotations. A 3D visited array ensures no redundant states are processed.
- **Time Complexity:** O(N * M * 4), where N and M are the maze dimensions, and 4 represents the possible directions.
- **Space Complexity:** O(N * M * 4) for visited states and the priority queue.

---

## Notes
- The maze is explored efficiently using Dijkstra's algorithm to ensure the lowest score path is found.
- The Reindeer faces cyclic direction changes and needs to avoid walls.
---
