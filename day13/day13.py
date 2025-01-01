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


def find_intersection(a_x: int, a_y: int, b_x: int, b_y: int, x_prize: int, y_prize: int) -> tuple[float, float]:
    a_x_with_b_y = a_x * b_y
    x_prize_with_b_y = x_prize * b_y
    a_y_with_b_x = a_y * b_x
    y_prize_with_b_x = y_prize * b_x
    a = (x_prize_with_b_y - y_prize_with_b_x) / (a_x_with_b_y - a_y_with_b_x)
    b = (y_prize - a_y * a) / b_y
    return a, b

def part2():
   with open("input.txt", "r") as file:
       content = file.read()
       
   buttonApattern = r"Button A:\s*X\+(\d+),\s*Y\+(\d+)" 
   buttonBpattern = r"Button B:\s*X\+(\d+),\s*Y\+(\d+)"
   prizePattern = r"Prize:\s*X=(\d+),\s*Y=(\d+)"
   
   buttonAmatches = re.findall(buttonApattern, content)
   buttonBmatches = re.findall(buttonBpattern, content)
   prizeMatches = re.findall(prizePattern, content)
   
   INCREASE = 10_000_000_000_000
   total_prizes_won = 0
   total_tokens = 0
   
   for a, b, p in zip(buttonAmatches, buttonBmatches, prizeMatches):
       pA, qA = int(a[0]), int(a[1])
       pB, qB = int(b[0]), int(b[1])
       xP, yP = int(p[0]) + INCREASE, int(p[1]) + INCREASE
       
       try:
           a_val, b_val = find_intersection(pA, qA, pB, qB, xP, yP)
           if a_val.is_integer() and b_val.is_integer():
               total_prizes_won += 1
               total_tokens += int(3 * a_val + b_val)
       except ZeroDivisionError:
           continue
           
   print(f"Total prizes won for part2: {total_prizes_won}")
   print(f"Total tokens spent for part2: {total_tokens}")
   print()
   
   return total_tokens

part1()
part2()
