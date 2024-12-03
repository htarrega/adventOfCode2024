# Day [3]: [First Part](https://adventofcode.com/2024/day/3)

## Problem Description
The problem involves finding expressions in the form of `mul(x, y)` in a text file. Each `mul(x, y)` represents a multiplication operation where `x` and `y` are integers. The task is to calculate the sum of the results of all such operations present in the file.

---

## Solution

- **Approach:** 
  - Open and read the input file line by line.
  - Use a regular expression to find all instances of `mul(x, y)` in the file.
  - Extract the integer values `x` and `y` from each `mul` expression.
  - Perform the multiplication of `x` and `y` for each operation and accumulate the results into a total.
  - Print the final sum of all multiplications.
  
- **Time Complexity:**  
  - Scanning the input file with a regex takes `O(n)`, where `n` is the size of the input text.
  - Processing the matches (splitting, parsing, and multiplying) takes `O(m)`, where `m` is the number of `mul(x, y)` matches.
  - Total: `O(n + m)`

- **Space Complexity:**  
  - Storing the matches found by the regex takes `O(m)`.
  - The input content itself requires `O(n)` space.
  - Total: `O(n + m)`

---

## Notes


---

# Day [3]: [Second Part](https://adventofcode.com/2024/day/3)

## Problem Description
The second part introduces toggling logic with `do()` and `don't()` markers in the text file. The task is to ignore sections of the text marked with `don't()` until a `do()` marker is encountered again. Only the `mul(x, y)` operations in the "enabled" sections of the text are considered for the sum.

---

## Solution

- **Approach:** 
  - Read the content of the file.
  - Use a helper function `cleaner()` to remove portions of the text between `don't()` and the next `do()` marker. This function uses regex to split the text and a flag to toggle the inclusion of segments.
  - After cleaning the text, use the same logic as in Part 1 to find and calculate the sum of all `mul(x, y)` operations.
  
- **Time Complexity:**  
  - Splitting the text into segments using `cleaner()` takes `O(n)`, where `n` is the size of the input text.
  - Scanning the cleaned text with a regex takes `O(n)` since the size of the cleaned text cannot exceed the original text.
  - Processing the matches (splitting, parsing, and multiplying) takes `O(m)`, where `m` is the number of `mul(x, y)` matches.
  - Total: `O(n + m)`.

- **Space Complexity:**  
  - The cleaned text requires `O(n)` space.
  - Storing the matches found by the regex takes `O(m)`.
  - Total: `O(n + m)`.

---

## Notes
