# Day 13: [Part 1](https://adventofcode.com/2024/day/13)

## Problem Description

Operate claw machines with two buttons, A and B, which move the claw along the X and Y axes. To win, align the claw with the prize's exact coordinates. Button A costs 3 tokens per press, and Button B costs 1 token.

The goal is to minimize tokens spent to win as many prizes as possible, given the machine configurations:

- Button A and B movements (X, Y components)
- Prize positions (X, Y coordinates)

## Solution

- **Approach:**
  1. Parse input to extract button movements and prize positions.
  2. Use a brute-force algorithm to test all combinations of button presses (up to 100 each).
  3. Check if movements align with prize coordinates.
  4. Calculate token cost as \(3 \times A\_presses + B\_presses\).
  5. Find the minimum cost for each machine.
  6. Sum total tokens spent and count prizes won.

- **Time Complexity:** \(O(M \times L^2)\), where \(M\) is the number of machines and \(L\) is the press limit (100).
- **Space Complexity:** \(O(1)\), as storage requirements are constant.

## Notes

- This brute-force solution is effective for small limits but inefficient for larger ranges. Mathematical optimization is recommended for larger-scale inputs.

---

# Day 13: [Part 2](https://adventofcode.com/2024/day/13)

## Problem Description
Same claw machine setup as Part 1, but prize coordinates are increased by 10^13 in both X and Y dimensions, making brute force impractical.

## Solution
- **Approach:**
1. Same input parsing for button movements
2. Add 10^13 to prize coordinates
3. Use linear system solver to find intersection point:
  ```python
  a_x * a + b_x * b = x_prize
  a_y * a + b_y * b = y_prize
  ```
4. Check if solution has integer values
5. Calculate token cost: 3 * a + b

- **Time Complexity:** O(M), where M is number of machines
- **Space Complexity:**  O(1)

## Notes

- Mathematical solution scales efficiently for large coordinates
