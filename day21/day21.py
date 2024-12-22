from collections import deque

class Node:
    def __init__(self, state, transitions=None):
        self._state = state
        self._transitions = transitions or []
    
    @property
    def state(self):
        return self._state
    
    @state.setter
    def state(self, value):
        self._state = value
    
    @property
    def transitions(self):
        return self._transitions
    
    @transitions.setter
    def transitions(self, value):
        self._transitions = value
    
    def add_transition(self, target_node, symbol):
        self._transitions.append((target_node, symbol))

# Dirpad State Machine
start_A = Node("A")
up = Node("^")
down = Node("v")
left = Node("<")
right = Node(">")

start_A.transitions = [(right, "v"),(up, "<")]
up.transitions = [(start_A, ">"), (down, "v")]
down.transitions = [(left, "<"), (right, ">"), (up, "^")]
right.transitions = [(down, "<"), (start_A, "^")]
left.transitions = [(down, ">")]

# Keypad State Machine
start_keypad = Node("A")
n0 = Node("0")
n1 = Node("1")
n2 = Node("2")
n3 = Node("3")
n4 = Node("4")
n5 = Node("5")
n6 = Node("6")
n7 = Node("7")
n8 = Node("8")
n9 = Node("9")

# Set transitions for each node
start_keypad.transitions = [(n0, "<"), (n3, "^")]
n0.transitions = [(start_keypad, ">"), (n8, "^"), (n2, "^")]
n1.transitions = [(n4, "^")]
n2.transitions = [(n1, "<"), (n3, ">"), (n0, "v"), (n5, "^")]
n3.transitions = [(start_keypad, "v"), (n2, "<"), (n6, "^")]
n4.transitions = [(n5, ">"), (n7, "^")]
n5.transitions = [(n2, "v"), (n4, "<"), (n6, ">"), (n8, "^")]
n6.transitions = [(n3, "v"), (n5, "<"), (n9, "^")]
n7.transitions = [(n8, ">")]
n8.transitions = [(n7, "<"), (n9, ">"), (n5, "v")]
n9.transitions = [(n8, "<"), (n6, "v")]

node_dict = {
    '0': n0, '1': n1, '2': n2, '3': n3, '4': n4,
    '5': n5, '6': n6, '7': n7, '8': n8, '9': n9, 'A': start_keypad
}

dir_dict = {
    '^': up,
    'v': down,
    '<': left,
    '>': right,
    'A': start_A
}

def find_shortest_path(start_node, end_node):
    queue = deque([(start_node, [start_node])])
    visited = {start_node}
    
    while queue:
        current_node, path = queue.popleft()
        
        if current_node == end_node:
            return path
        
        for next_node, _ in current_node.transitions:
            if next_node not in visited:
                visited.add(next_node)
                new_path = path + [next_node]
                queue.append((next_node, new_path))
    
    return None

def process_to_directions(input_sequence, start_node, dict):
    res = ""
    current_node = start_node
    node_map = dict
    
    for char in input_sequence:
        target_node = node_map.get(char)
        
        if target_node:
            path = find_shortest_path(current_node, target_node)
            if path:
                for i in range(len(path) - 1):
                    current = path[i]
                    next_node = path[i + 1]
                    for node, direction in current.transitions:
                        if node == next_node:
                            res += direction
                            break
                current_node = target_node
            res += 'A'
    
    return res


def part1():
    total = 0

    with open('aux.txt', 'r') as file:
        lines = [line.strip() for line in file.readlines() if line.strip()]
    
    for line in lines:
        print(line)
        result = process_to_directions(line, start_keypad, node_dict)
        result2 = process_to_directions(result, start_A, dir_dict)
        result3 = process_to_directions(result2, start_A, dir_dict)

        parts = line.split("A")
        print(len(result3))
        print(parts[0])
        print("----")
        total = total + len(result3)*int(parts[0])


    print("Total for part 1: " + str(total))

part1()