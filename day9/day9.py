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

part1()

