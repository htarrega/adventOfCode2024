def part1():
	list1 = []
	list2 = []


	file = open('input.txt','r')
	while True:
		line = file.readline()
		if not line:
			break
		nums = line.split()
		list1.append(int(nums[0]))
		list2.append(int(nums[1]))
	file.close()

	list1.sort()
	list2.sort()

	total_distance = 0
	i = 0
	for num in list1:
		total_distance+= abs(list2[i] - list1[i])
		i += 1

	print("Total distance = " + str(total_distance))

def part2():
	list1 = []
	right_dict = {}


	file = open('input.txt','r')
	while True:
		line = file.readline()
		if not line:
			break
		nums = line.split()
		list1.append(int(nums[0]))
		right_num = int(nums[1])
		if int(right_num in right_dict):
			right_dict[right_num] = right_dict[right_num]+1
		else:
			right_dict[right_num] = 1
	file.close()

	total_distance = 0
	for num in list1:
		right_dict[right_num] = right_dict.get(right_num, 0) + 1
	print("Total distance for second part = " + str(total_distance))

part1()
part2()