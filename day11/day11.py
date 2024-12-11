def part1():
    total = 0

    with open('input.txt', 'r') as file:
        rocks = list(map(int, file.readline().strip().split()))
    
    new_rocks = []
    for iter in range(0,25):
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

def part2():
    with open("input.txt", 'r') as file:
        input_stones = file.readline().split()
    
    d = {}
    for val in input_stones:
        val = int(val)
        d[val] = d.get(val, 0) + 1
    
    def process(num):
        if num == 0:
            return [1]
        elif len(str(num)) % 2 == 0:
            length = len(str(num))
            return [
                int(str(num)[0 : length // 2]),
                int(str(num)[length // 2 :])
            ]
        else:
            return [num * 2024]
    
    for x in range(75):
        d2 = {}
        for key in list(d):
            if d[key] > 0:
                num = d[key]
                d[key] -= num
                for val in process(key):
                    d2[val] = d2.get(val, 0) + num
        for key, value in d2.items():
            d[key] = d.get(key, 0) + value

    print(f"Part 2 total stones after 75 blinks: {sum(d.values())}")


part1()
part2()
