# Day [11]: [First and Second Part](https://adventofcode.com/2024/day/11)

## Problem Description

The problem involves transforming a collection of numerical "stones" through multiple iterations. Each stone can split into smaller stones based on specific rules or grow in size depending on its properties. The objective is to determine the total number of stones remaining after 75 transformations, following a given set of rules.

## Solution

- **Approach:**  
  1. **Parse Input:** Read the initial list of stone values from the input file.  
  2. **Initialize State:** Count the frequency of each stone value, storing them in a dictionary (`d`).  
  3. **Define Transformation Rules:**  
     - If the value is `0`, transform it into `[1]`.  
     - For even-length numbers, split the number into two halves and treat them as new stones.  
     - For odd-length numbers, multiply the value by `2024` to generate a single new stone.  
  4. **Iterate N Times:** Perform the following steps in each iteration:  
     - Create a temporary dictionary (`d2`) to hold new stone values generated during this step.  
     - For each stone in the current state:
       - Apply the transformation rules to generate new stones.
       - Update `d2` with the frequency of these new stones.  
     - Merge the updated frequencies from `d2` back into the main dictionary (`d`).  
  5. **Calculate the Result:** After 75 iterations, sum all frequencies in `d` to find the total number of stones.