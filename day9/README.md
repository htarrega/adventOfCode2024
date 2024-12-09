# Day 9: [Disk Fragmenter](https://adventofcode.com/2024/day/9)

## Problem Description

The task here is to organize files on a disk, represented by a map. This map consists of a sequence of numbers where digits show file sizes, and spaces represent free space. The goal is to move the files, either by shifting individual blocks or whole files, and then compute a checksum based on the final arrangement.

### Part One:
The disk map alternates between numbers representing files and gaps representing free space. Each file has an ID based on the order it appears. The challenge is to move the file blocks to the left to fill gaps, and then calculate the checksum by multiplying the block position by its file ID and summing them up.

### Part Two:
Now, instead of moving individual blocks, the amphipod moves entire files to the leftmost available space that can fit them. The process starts with the largest file and works its way down to the smallest. If there’s not enough space for a file, it stays in its original spot. After compacting the files, we calculate the checksum the same way as before.

## Solution

- **Approach:**  
  1. **Parse Input:** The disk map is parsed into files and spaces. In Part One, files are moved block by block to fill gaps. In Part Two, whole files are moved to the leftmost available space that can accommodate them.
  2. **File Compaction (Part One):** Move file blocks left to fill gaps and calculate the checksum based on their final positions.
  3. **File Compaction (Part Two):** Move entire files (starting with the largest) to the leftmost available space, then calculate the checksum again.
  4. **Checksum Calculation:** For each block that isn’t free space, compute the product of its position and file ID, and sum the values to get the final checksum.

- **Time Complexity:**  
  - **Part One:** O(N)  
    - N: Length of the disk map.  
  - **Part Two:** O(N * F)  
    - N: Length of the disk map.  
    - F: Number of files.

- **Space Complexity:**  
  - **Part One and Part Two:** O(N)  
    - N: Space needed to store the disk map and positions of files and free space.

---

## Notes
- In Part One, files are moved block by block to fill the leftmost free space.
- Part Two is about moving whole files, looking for the first block of free space big enough to fit each file, starting with the largest one.

---

# Day 9: [Second Part](https://adventofcode.com/2024/day/9)

## Problem Description

In Part Two, things change a bit. Now the goal is to compact the disk by moving entire files, not just blocks. The objective remains the same, though: move the files efficiently and calculate the checksum.

---

## Solution

- **Approach:**  
  1. **Parse Input:** Like in Part One, we parse the disk map into files and free spaces.
  2. **File Compaction (Part Two):** Move each file as a whole, starting with the largest, into the first available space that can fit it.
  3. **Checksum Calculation:** Calculate the checksum the same way as Part One by multiplying the block positions with the file IDs and summing them up.

- **Time Complexity:** O(N * F)  
  - N: Length of the disk map.  
  - F: Number of files.

- **Space Complexity:** O(N)  
  - N: Space to store the disk map and the positions of files and free space.

---

## Notes
