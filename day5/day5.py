def part1():
    rules = {}
    total = 0
    file = open('input.txt', 'r')
    while True:
        line = file.readline()
        if len(line.strip()) == 0:
            break
        clean_line = line.strip("\n")
        nums = clean_line.split("|")
        first_num = int(nums[0])
        second_num = int(nums[1])
        if first_num not in rules:
            rules[first_num] = [second_num]
        else:
            rules[first_num].append(second_num)
    
    while True:
        line = file.readline()
        if not line:
            break
        clean_line = line.strip("\n")
        nums = clean_line.split(',')
        if nums == ['']:
            continue

        correct = True
        for i in range(0, len(nums) - 1):
            current_key = int(nums[i])  
            if current_key in rules and correct:  
                for j in range(i + 1, len(nums)):
                    comparison_value = int(nums[j])  
                    if comparison_value not in rules[current_key]:
                        correct = False
                        break  
            else:
                correct = False 
                break 
            
        if correct:
            total += int(nums[len(nums) // 2])

    file.close()

    print("Total sum part 1 = " + str(total))

def compare(a, b, rules):
    if a in rules and b in rules[a]:
        return -1 
    elif b in rules and a in rules[b]:
        return 1 
    return 0  

def custom_sort(arr, compare, rules):
    from functools import cmp_to_key
    return sorted(arr, key=cmp_to_key(lambda x, y: compare(x, y, rules)))


def part2():
    rules = {}
    total = 0
    file = open('input.txt', 'r')
    while True:
        line = file.readline()
        if len(line.strip()) == 0:
            break
        clean_line = line.strip("\n")
        nums = clean_line.split("|")
        first_num = int(nums[0])
        second_num = int(nums[1])
        if first_num not in rules:
            rules[first_num] = [second_num]
        else:
            rules[first_num].append(second_num)
    
    while True:
        line = file.readline()
        if not line:
            break
        clean_line = line.strip("\n")
        nums = clean_line.split(',')
        if nums == ['']:
            continue

        correct = True
        for i in range(0, len(nums) - 1):
            current_key = int(nums[i])  
            if current_key in rules and correct:  
                for j in range(i + 1, len(nums)):
                    comparison_value = int(nums[j])  
                    if comparison_value not in rules[current_key]:
                        correct = False
                        break  
            else:
                correct = False
                break 
            
        if not correct:
            no_missing_nums = []
            for num in nums:
                if int(num) in rules:
                    no_missing_nums.append(int(num))
            sorted_nums = custom_sort(no_missing_nums, compare,rules)
            index = len(sorted_nums) // 2
            total += sorted_nums[index]


    file.close()

    print("Total sum part 2 = " + str(total))

part1()
part2()