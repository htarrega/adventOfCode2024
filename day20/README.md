# Day 20: [Part 1](https://adventofcode.com/2025/day/20)

## The Problem
In this problem, we are given a grid with obstacles (`#`) and special positions (`S` for start and `E` for end). Our goal is to find the shortest path from `S` to `E`, while considering the possibility of "cheats" — smaller paths through the grid that could save us time.

## Solution Approach
I used **Breadth-First Search (BFS)** to compute the shortest paths from the start to the end. Here's the breakdown:
- I started by computing the normal shortest path from `S` to `E` using BFS.
- Then, I looked for possible "cheats" — smaller paths through the grid that start from a valid position, take a detour, and then reach the end. I checked if these cheats saved time over the normal path.
- For each valid cheat, I calculated the savings in terms of distance and added it to a list if it met the criteria (savings >= 100).

The core idea was to use BFS for shortest path calculations, then explore nearby positions to see if shortcuts (cheats) could save time.

* Time Complexity: **O(N * M)** where N is the number of rows and M is the number of columns in the grid. This accounts for the BFS computations.
* Space: **O(N * M)** for storing distances and visited positions in the grid.

# Day 20: [Part 2](https://adventofcode.com/2024/day/20)

## The Problem
Now, we need to count all the different "cheats" that can help shorten the path. The task is to identify all valid cheats, where the savings in time meet a certain threshold, and count them.

## Solution Approach
For Part 2, I modified the approach from Part 1 to count how many different cheats can be found. Here's what changed:
- Instead of just finding one possible cheat, I now count every valid cheat.
- After calculating the shortest path using BFS, I check every pair of positions to calculate if there is a valid cheat that saves time and meets the threshold.
- I used a combination of BFS and sorting to identify the optimal cheats for each path.

The tricky part was ensuring that cheats were identified efficiently. I considered nearby positions (within a 2-step radius) and calculated the distance between them to see if it saved enough time.

* Time Complexity: Similar to Part 1 with an added factor for counting each possible cheat combination.
* Space: **O(N * M)** for storing BFS results and paths.

## Notes
- **BFS** was an excellent fit for calculating the shortest path and finding valid positions for cheats.
