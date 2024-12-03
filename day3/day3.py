import re

def part1():
    res = 0
    file = open("input.txt", "r")
    content = file.read()
    apparitions = re.findall("mul\([0-9]+,[0-9]+\)",content)
    file.close()
    for mul in apparitions:
        op = mul.replace("mul(", "").replace(")","")
        nums = op.split(",")
        res += int(nums[0])*int(nums[1])




    print("Total part 1: " + str(res))

def part2():
    res = 0
    file = open("aux.txt", "r")
    content = file.read()
    file.close()
    print(content)
 
    



    print("Total part 2: " + str(res))


part1()
part2() 