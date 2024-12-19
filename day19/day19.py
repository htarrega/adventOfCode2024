class TreeNode:
    def __init__(self, value=""):
        self.value = value
        self.children = {}
        self.is_pattern = False
        
    def insert(self, string):
        current = self
        for char in string:
            if char not in current.children:
                current.children[char] = TreeNode(current.value + char)
            current = current.children[char]
        current.is_pattern = True
    
    def display(self, level=0):
        print(" " * level + self.value)
        for child in sorted(self.children.values(), key=lambda x: x.value):
            child.display(level + 2)
    
    def can_form(self, design, memo=None):
        if memo is None:
            memo = {}
        
        if not design:
            return True
        
        if design in memo:
            return memo[design]
        
        current = self
        for i, char in enumerate(design):
            if char not in current.children:
                break
            current = current.children[char]
            if current.is_pattern:
                if self.can_form(design[i + 1:], memo):
                    memo[design] = True
                    return True
        
        memo[design] = False
        return False

def part1():
    with open('input.txt', 'r') as file:
        lines = [line.strip() for line in file.readlines() if line.strip()]
    
    towels = None
    designs = []
    root = TreeNode()
    
    for i, line in enumerate(lines):
        if i == 0:
            towels = [item.strip() for item in line.split(",")]
        else:
            designs.append(line)
    
    for towel in towels:
        root.insert(towel)
    
    valids = 0
    for design in designs:
        if root.can_form(design):
            valids += 1
    
    print("Total valid designs for part1:", valids)

part1()