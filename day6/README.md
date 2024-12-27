# Day 6: [Part 1](https://adventofcode.com/2024/day/6)

## The Problem
The historians need to track a guard's patrol path in a 1518 prototype suit manufacturing lab. The guard follows simple rules:
- If there's an obstacle ahead, turn right 90 degrees
- Otherwise, move forward one step
- The guard starts facing up (^)
- The guard continues until leaving the mapped area

## Solution Approach
I used a grid-based simulation with direction vectors. Here's why:
- Natural representation of the 2D movement space
- Easy to track visited positions
- Simple to implement the guard's movement rules

The core algorithm:
1. Find guard's starting position marked with '^'
2. Use direction vectors for UP, RIGHT, DOWN, LEFT
3. Simulate movement until guard leaves the grid
4. Mark visited positions with 'X'
5. Count total marked positions

Time Complexity: O(N * M) where N and M are grid dimensions
Space Complexity: O(N * M) for the grid storage

# Day 6: [Part 2](https://adventofcode.com/2024/day/6)

## The Problem
Now we need to find all possible positions where placing a new obstacle would cause the guard to get stuck in a loop. This would let the historians safely search the rest of the lab.

Key constraints:
- Can only add one new obstacle
- Can't place it at guard's starting position
- Must create a patrol loop that never exits the map

## Solution Approach
I modified the movement simulation to detect loops. The key differences:
- Track both position AND direction in visited states
- Use a maximum step limit to detect infinite loops
- Create fresh grid copy for each obstacle test

The solution process:
1. Try placing obstacle 'O' at each empty position
2. Simulate guard movement with new obstacle
3. Check if guard gets stuck in loop:
   - Return true if same position+direction is revisited
   - Return false if guard would exit map
4. Count positions that create loops

Critical insights:
- Need to track direction with position because same position with different direction isn't necessarily a loop
- Must prevent infinite loops in non-looping cases
- Important to preserve original grid state for each test

Time Complexity: O(N * M * P) where P is maximum path length
Space Complexity: O(N * M * 4) for visited states tracking

## Notes