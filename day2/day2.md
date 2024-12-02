# Day [X]: [First Part - Valid Report Analysis]

## Problem Description
Given a sequence of numbers in each report, determine if it is a valid report. A report is valid if:
1. Differences between consecutive numbers are within the range `[1, 3]`.
2. All numbers in the sequence are strictly increasing or strictly decreasing.

---

## Solution

- **Approach:**  
  Parse each line into a list of numbers. Validate each sequence by:
  1. Checking if all differences between consecutive numbers are within `[1, 3]`.
  2. Ensuring the sequence is either strictly increasing or strictly decreasing.

- **Time Complexity:** O(N * L)  
  - N: Number of reports.  
  - L: Length of a report 

- **Space Complexity:** O(L)  
  - For storing the parsed sequence of numbers.

---

## Notes
- Reports with mixed trends (increasing and then decreasing) are inherently invalid.

---

# Day [X]: [Second Part - Problem Dampener]

## Problem Description
Update the report validation logic to account for the **Problem Dampener**, which allows removing a single element from a sequence to make it valid. A report is valid if:
1. It is valid as per the rules in Part 1.  
2. Removing any one number from the sequence results in a valid report.

---

## Solution

- **Approach:**  
  1. Parse the sequence of numbers from each report.  
  2. First, check if the report is valid without modification.  
  3. If not valid, iterate through the sequence and simulate the removal of each number, then check if the modified sequence becomes valid.  
  4. Use a helper function (`isValidReport`) to validate the modified sequences.

- **Time Complexity:** O(N * L²)  
  - N: Number of reports.  
  - L: Average length of a report (for iterating through each report and simulating removals).

- **Space Complexity:** O(L)  
  - For storing the parsed sequence of numbers and any temporary modifications.

---

## Notes
- This approach simulates all possible single-number removals, ensuring the dampener is applied optimally.  
- Performance could be optimized further by early termination once a valid configuration is found after a removal.

---