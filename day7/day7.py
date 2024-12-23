from itertools import combinations

def count_combinations(numbers: str) -> int:
    nums = [int(x) for x in numbers.split()]
    if len(nums) < 2:
        return 0

    target = nums[0]
    numbers = nums[1:]

    def try_operations(nums, target):
        def evaluate_expression(nums, ops):
            result = nums[0]
            for i, op in enumerate(ops):
                if op == '+':
                    result += nums[i + 1]
                else:
                    result *= nums[i + 1]
            return result

        n = len(nums) - 1
        for _ in range(n):
            ops = [''] * n
            stack = [(0, ops[:])]

            while stack:
                pos, current_ops = stack.pop()
                if pos == n:
                    if evaluate_expression(nums, current_ops) == target:
                        return True
                else:
                    for op in ['+', '*']:
                        new_ops = current_ops[:]
                        new_ops[pos] = op
                        stack.append((pos + 1, new_ops))
        return False

    for r in range(2, len(numbers) + 1):
        for combo in combinations(numbers, r):
            if try_operations(list(combo), target):
                return target

    return 0

def part1():
    file = open('aux.txt', 'r')
    for line in file:
        print(line)
        line = file.readline()
        div = line.split()
        if len(div) > 0:
            div[0] = div[0][:-1]
            print(div)
            print(count_combinations(" ".join(div)))

part1()
