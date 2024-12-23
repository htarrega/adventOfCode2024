# Day [7]: [First Part](https://adventofcode.com/2024/day/7)

## Problem Description

The task involves evaluating equations where a target value is given, and we need to determine whether the remaining numbers in the equation can be combined using addition (+) or multiplication (*) to produce the target. The equations are read from an input file, and we accumulate the target values of valid equations to obtain the total calibration result.

## Solution

- **Approach:**

    1.Parse each line of the input file to extract the target value and the list of numbers.
    2.Generate all possible combinations of operators (+ and *) to apply between the numbers.
    3.Evaluate each combination left-to-right and check if the result matches the target value.
    4.Accumulate the target value of equations that pass this validation.

- **Time Complexity:**  O(N * 2^M)

    - N: Number of equations in the input file.
    - M: Number of numbers in each equation (minus 1, for the number of operators).


- **Space Complexity:** O(1)

    - No additional storage beyond loop variables is required.
---

## Notes
- We use a dictionary to store the relationship rules.    

---

# Day [7]: [Second Part](https://adventofcode.com/2024/day/7)

## Problem Description

The second part extends the problem by introducing a new operator (||), which concatenates numbers (e.g., 12 || 345 becomes 12345). The task remains to determine whether the target value can be produced by combining numbers using +, *, or ||. We sum the target values of all equations that pass the validation.

---

## Solution

- **Approach:**  
  1. same as before but I extend the operator set to include concatenation (||).

- **Time Complexity:** O(N * 3^M)
  - N: Number of lines in the input file.  
  - M: Number of numbers in each equation (minus 1, for the number of operators).

- **Space Complexity:** O(1)  
  - As with the first part, no additional storage is required beyond loop variables.

---

## Notes
