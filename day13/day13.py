import re

def part1():
    with open("input.txt", "r") as file:
        content = file.read()

    total_tokens = 0
    total_prizes_won = 0
    max_button_presses = 100  

    buttonApattern = r"Button A:\s*X\+(\d+),\s*Y\+(\d+)"
    buttonBpattern = r"Button B:\s*X\+(\d+),\s*Y\+(\d+)"
    prizePattern = r"Prize:\s*X=(\d+),\s*Y=(\d+)"

    buttonAmatches = re.findall(buttonApattern, content)
    buttonBmatches = re.findall(buttonBpattern, content)
    prizeMatches = re.findall(prizePattern, content)

    for a, b, p in zip(buttonAmatches, buttonBmatches, prizeMatches):

        pA, qA = int(a[0]), int(a[1])  
        pB, qB = int(b[0]), int(b[1])  
        xP, yP = int(p[0]), int(p[1])  

        valid_solution = False
        min_cost = float('inf')

        for a_val in range(max_button_presses + 1):
            for b_val in range(max_button_presses + 1):
                if pA * a_val + pB * b_val == xP and qA * a_val + qB * b_val == yP:
                    cost = 3 * a_val + b_val
                    if cost < min_cost:
                        min_cost = cost
                        valid_solution = True

        if valid_solution:
            total_prizes_won += 1
            total_tokens += min_cost

    
    print(f"Total prizes won for part1: {total_prizes_won}")
    print(f"Total tokens spent for part1: {total_tokens}")
    print()

part1()