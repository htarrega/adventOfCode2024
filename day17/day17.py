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

import math

def part2():
    # Read the input from the program
    with open('input.txt', 'r') as file:
        lines = file.readlines()

    # Initialize the registers
    regA = 0
    regB = 0
    regC = 0
    mem = []
    
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
    
    # Function to simulate the program
    def run_program(initial_A):
        regA = initial_A
        regB = 0
        regC = 0
        out = ""

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
        
        return out

    # Try all possible initial values of A
    program_output = ''.join([str(x % 8) for x in mem if x != 7])
    found_A = None
    
    # Try all possible values for register A
    for initial_A in range(0, 2**24):  # You can adjust the range based on expected input size
        output = run_program(initial_A)
        if output == program_output:
            found_A = initial_A
            break
    
    print("Part 2:", found_A)



part1()
part2()