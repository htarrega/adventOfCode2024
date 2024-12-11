import math

def part1():
    total = 0

    with open('input.txt', 'r') as file:
        rocks = list(map(int, file.readline().strip().split()))
    
    new_rocks = []
    for iter in range(0,25):
        #print("iter: "+str(iter)) 
        #print(rocks)
        for rock in rocks:
            if rock == 0:
                new_rocks.append(1)
                continue
            rock_str = str(rock)
            if len(rock_str) % 2 == 0:
                mid = len(rock_str) // 2
                n1 = rock_str[:mid]
                n2 = rock_str[mid:]
                new_rocks.append(int(n1))
                new_rocks.append(int(n2))
            else:
                new_rocks.append(rock*2024)
        rocks = new_rocks
        new_rocks = []
    total = len(rocks)

    print("Part 1 total stones: "+ str(total))

from collections import deque
import array

part1()
