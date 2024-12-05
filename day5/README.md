# Day [5]: [First Part](https://adventofcode.com/2024/day/5)

## Problem Description

The task requires processing an input file and determining whether certain relationships between numbers are valid. The relationships are structured as pairs of numbers, where one number is compared against a list of valid numbers. Based on these checks, we accumulate a total sum.

## Solution

- **Approach:**  
  1. The first part of the solution involves reading pairs of numbers from the input file. Each pair defines a rule: the first number should have a corresponding second number that is considered valid.
  2. After parsing these relationships, we examine a second set of numbers, checking if each number follows the defined rules in sequence. If the rules are valid, we add the middle number in the sequence to the total sum, that is printed.

- **Time Complexity:** O(N * M)  
  - N: Number of lines in the input file.  
  - M: Average number of comparisons per line.

- **Space Complexity:** O(R)  
  - R: Number of unique rules stored in memory.

---

## Notes
- We use a dictionary to store the relationship rules.    

---

# Day [5]: [Second Part](https://adventofcode.com/2024/day/5)

## Problem Description

In the second part of the challenge, the task remains similar but now taking into account invalid sequences. 
This sequences are reordered using the alrerady defined rules and the middle number of each sorted sequence contributes to the total sum.

---

## Solution

- **Approach:**  
  1. The rules are initially processed just like in the first part.
  2. After reading and processing each sequence, if the sequence does not follow the rules, we identify the numbers that exist in the rules, sort them, and find the middle number in the sorted list.
  3. The middle number is added to the total sum.

- **Time Complexity:** O(N * M * log M)  
  - N: Number of lines in the input file.  
  - M: Number of comparisons in the sequence that requires sorting.

- **Space Complexity:** O(R)  
  - R: Number of unique rules stored in memory.

---

## Notes
- Sorting plays a crucial role in the second part of the problem. We need to define our own comparison function to pass it as a lambda to Python sorting function.Since python sorting uses key functions we need a lib that transforms our comparison function into a key function.
