# Day 19: [Part 1](https://adventofcode.com/2024/day/19)

## The Problem
The onsen staff needs help arranging towels! We have a list of available towel patterns (like "rg" or "bw") and want to know which target designs we can create by combining these patterns. Each towel pattern represents different colored stripes, and we can use each pattern as many times as we want.

## Solution Approach
I used a trie (prefix tree) - here's why:
- Perfect for storing and searching patterns efficiently
- Easy to check substrings against available patterns

The core idea is to build a tree of valid patterns, then for each design, try to match it using combinations of our patterns. I store successful attempts in memory to speed things up.

Time Complexity: O(N * M) where N is design length and M is number of possible patterns at each position
Space: O(P * L) for the trie, where P is pattern count and L is max pattern length

# Day 19: [Part 2](https://adventofcode.com/2024/day/19)

## The Problem
Now we need to count ALL the different ways each design can be made. Instead of just checking if a design is possible, we need to find every valid combination of patterns that creates it.

## Solution Approach
I modified our trie solution to count arrangements instead of just checking possibility. The key difference is we keep going after finding a valid match to count all possibilities.

Here's what changed:
- Instead of returning true/false, we return counts
- At each position, we sum up all possible ways to form the rest of the string

The tricky part was handling overlapping patterns correctly. For example, if we have patterns "rg" and "r", and we're matching "rgr", we need to count both:
- Using "rg" + "r"
- Using "r" + "g" + "r"

Time Complexity: Same as part 1 but multiplied by average number of valid arrangements
Space: Still O(P * L) for the trie, plus memoization storage

## Notes
- Trie structure was perfect for both parts with minimal changes needed