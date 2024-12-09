from collections import deque

def part1():
    mem = []
    checksum = 0

    with open('input.txt', 'r') as file:
        line = file.readline().strip()
    index = 0
    for num in line:
        number = int(num)
        even = index % 2 == 0
        for x in range(0,number):
            if even:
                mem.append(index//2)
            else:
                mem.append(None)
        
        index += 1
    ##Two indexes (both sides)
    begin = 0
    end = len(mem)-1
    while(begin < end):
        if(mem[end]  == None):
            end-=1
            continue
        if(mem[begin]  != None):
            begin+=1
            continue
        if(mem[begin]== None and mem[end]  != None):
            mem[begin]= mem[end]
            mem[end] = None
            begin+= 1
            end-=1
            continue

    for x in range(0,len(mem)):
        if mem[x] == None:
            break
        checksum+= x*mem[x]



    print("Part 1 checksum: "+ str(checksum))


def part2():
    d = open('input.txt').read().strip()
    mem = []
    checksum = 0
    file_id = 0
    pos = 0
    a = []
    space = []

    for i, c in enumerate(d):
        if i % 2 == 0:
            a.append((pos, int(c), file_id))
            for _ in range(int(c)):
                mem.append(file_id)
                pos += 1
            file_id += 1
        else:
            space.append((pos, int(c)))
            for _ in range(int(c)):
                mem.append(None)
                pos += 1

    for (pos, sz, file_id) in reversed(a):
        for space_i, (space_pos, space_sz) in enumerate(space):
            if space_pos < pos and sz <= space_sz:
                for i in range(sz):
                    mem[pos + i] = None
                    mem[space_pos + i] = file_id
                space[space_i] = (space_pos + sz, space_sz - sz)
                break

    for i, c in enumerate(mem):
        if c is not None:
            checksum += i * c

    print("Part 2 checksum:", checksum)


part1()
part2()
