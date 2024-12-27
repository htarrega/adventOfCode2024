import math

def part1():
    regA = 0
    regB = 0
    regC = 0
    out = ""
   
    with open('input.txt', 'r') as file:
        lines = file.readlines()
    for line in lines:
        line = line.strip()
        if line.startswith("Register A:"):
            regA = int(line.split(":")[1].strip())  
        elif line.startswith("Register B:"):
            regB = int(line.split(":")[1].strip())
        elif line.startswith("Register C:"):  
            regC = int(line.split(":")[1].strip())
        elif line.startswith("Program:"):
            numbers = line.split(":")[1].strip().split(",")
            mem = [int(num.strip()) for num in numbers if num.strip().isdigit()]
    instPointer = 0
    while instPointer < len(mem):
        opcode = mem[instPointer]
        operand = mem[instPointer + 1]
        if opcode == 0 or opcode == 6 or opcode == 7:
            numerator = regA
            if operand == 4:
                denominator = regA
            elif operand == 5:
                denominator = regB
            elif operand == 6:
                denominator = regC
            else:
                denominator = operand
            result = math.trunc(numerator / (2 ** denominator))
            if opcode == 0:
                regA = result
            elif opcode == 6:
                regB = result
            elif opcode == 7:
                regC = result
        elif opcode == 1:
            regB = regB ^ operand
        elif opcode == 2:
            if operand == 4:
                regB = regA % 8
            elif operand == 5:
                regB = regB % 8
            elif operand == 6:
                regB = regC % 8
            else:
                regB = operand % 8
        elif opcode == 3:
            if regA != 0:
                instPointer = operand
                continue
        elif opcode == 4:
            regB = regB ^ regC
        elif opcode == 5:
            if operand == 4:
                out += str(regA % 8)
            elif operand == 5:
                out += str(regB % 8)
            elif operand == 6:
                out += str(regC % 8)
            else:
                out += str(operand % 8)
        else:
            exit()  
        instPointer += 2
    print("Part 1: "+",".join(list(out)))

def simulate_program(a, b, c, program):
    i = 0
    registers = {'a': a, 'b': b, 'c': c}
    output = []
    
    while i < len(program):
        opcode = program[i]
        operand = program[i + 1]
        
        operand_value = operand if operand < 4 else {
            4: registers['a'],
            5: registers['b'],
            6: registers['c']
        }.get(operand, operand)
        
        if opcode == 0:
            registers['a'] = registers['a'] >> operand_value
        elif opcode == 1:
            registers['b'] = registers['b'] ^ operand
        elif opcode == 2:
            registers['b'] = operand_value & 7
        elif opcode == 3:
            if registers['a'] != 0:
                i = operand
                continue
        elif opcode == 4:
            registers['b'] = registers['b'] ^ registers['c']
        elif opcode == 5:
            output.append(operand_value & 7)
        elif opcode == 6:
            registers['b'] = registers['a'] >> operand_value
        elif opcode == 7:
            registers['c'] = registers['a'] >> operand_value
            
        i += 2
        
    return output

def find_solution(initial_b, initial_c, program, partial_a=0, depth=0):
    output = simulate_program(partial_a, initial_b, initial_c, program)
    
    if output == program:
        return partial_a
        
    if depth == 0 or output[-depth:] == program[-depth:]:
        for n in range(8):
            new_a = (partial_a << 3) + n
            result = find_solution(initial_b, initial_c, program, new_a, depth + 1)
            if result is not None:
                return result
                
    return None

def part2():
    initial_a = 0
    initial_b = 0
    initial_c = 0
    program = []
    
    with open('input.txt', 'r') as file:
        for line in file:
            if line.startswith("Register A:"):
                initial_a = int(line.split(":")[1].strip())
            elif line.startswith("Register B:"):
                initial_b = int(line.split(":")[1].strip())
            elif line.startswith("Register C:"):
                initial_c = int(line.split(":")[1].strip())
            elif line.startswith("Program:"):
                numbers = line.split(":")[1].strip().split(",")
                program = [int(num.strip()) for num in numbers if num.strip().isdigit()]
    
    result = find_solution(initial_b, initial_c, program)
    print(f"Part 2: {result}")


part1()
part2()