from itertools import product

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
                elif op == '*':
                    result *= nums[i + 1]
            return result

        n = len(nums) - 1
        for ops in product(['+', '*'], repeat=n):
            if evaluate_expression(nums, ops) == target:
                return True
        return False

    return target if try_operations(numbers, target) else 0

def count_combinations_with_concat(numbers: str) -> int:
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
                elif op == '*':
                    result *= nums[i + 1]
                elif op == '||':
                    result = int(str(result) + str(nums[i + 1]))
            return result

        n = len(nums) - 1
        for ops in product(['+', '*', '||'], repeat=n):
            if evaluate_expression(nums, ops) == target:
                return True
        return False

    return target if try_operations(numbers, target) else 0

def part1():
    total_calibration = 0
    with open('input.txt', 'r') as file:
        for line in file:
            line = line.strip()
            if line:
                parts = line.split(':')
                if len(parts) == 2:
                    test_value = int(parts[0].strip())
                    numbers = f"{test_value} {parts[1].strip()}"
                    total_calibration += count_combinations(numbers)

    print(total_calibration)

def part2():
    total_calibration = 0
    with open('input.txt', 'r') as file:
        for line in file:
            line = line.strip()
            if line:
                parts = line.split(':')
                if len(parts) == 2:
                    test_value = int(parts[0].strip())
                    numbers = f"{test_value} {parts[1].strip()}"
                    total_calibration += count_combinations_with_concat(numbers)

    print(total_calibration)

part1()
part2()
