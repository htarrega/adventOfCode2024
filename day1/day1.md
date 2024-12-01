# Day [X]: [First Part](https://adventofcode.com/2024/day/1)

## Problem Description
Brief problem about ordering two vectors and then traversing them. 

---

## Solution

- **Approach:** The first part will be to order inplace the vectors in an optimal way. After that, the problem is trivial, just doing the difference between the ordered values and getting the total. For the sorting I have used Tim sort in it's python default implementation, with a worst case computational cost of O(nlogn) and spatial cost of O(n). I'm assuming that len(n) = len(m)
n = first vector
m = second vector
- **Time Complexity:** O(n+m+ nlogn + (mlogm + max(n,m)))  = O(nlogn)
- **Space Complexity:** O(2n) = O(n)

---

## Notes

# Day [X]: [Second Part](https://adventofcode.com/2024/day/1)

## Problem Description
In the second part was necessary to count the repetitions of each number in the right vector. After that, the number of aparitions should be multiplied by the number in the right. I used a dictionary, that is suitable to be used to count aparitions. 

---

## Solution

- **Approach:** Store in a dictionary the number of apparitions of each number in the right column. Traverse left column multiplying the number to the total apparitions. The total is the sum of all multiplications. 
n = vector size
- **Time Complexity:** For the average case,  O(n+n) = O(n)  
- **Space Complexity:** Mainly the size of the vector and the dictionary, O(2n) = O(n) 
---

## Notes