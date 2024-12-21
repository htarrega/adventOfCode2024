from collections import deque

class Node:
    def __init__(self, state, transitions=None):
        self.state = state
        self.transitions = transitions or []

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

start_A.transitions = [(up, "^"), (down, "v")]
up.transitions = [(down, "v")]
right.transitions = [(down, "v")]
down.transitions = [(up, "^"), (left, "<"), (right, ">")]
left.transitions = [(down, "v")]


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
n0.transitions = [(n8, "^"), (n2, "^"), (start_keypad, ">")]
n1.transitions = [(n4, "^")]
n2.transitions = [(n5, "^"), (n1, "<"), (n3, ">"), (n0, "v")]
n3.transitions = [(n6, "^"), (n2, "<"),(start_keypad,"v")]
n4.transitions = [(n7, "^"), (n5, ">")]
n5.transitions = [(n8, "^"), (n4, "<"), (n6, ">"), (n2, "v")]
n6.transitions = [(n9, "^"), (n5, "<"), (n3, "v")]
n7.transitions = [(n8, ">")]
n8.transitions = [(n7, "<"), (n9, ">"), (n5, "v"), (n0, "v")]
n9.transitions = [(n8, "<"), (n6, "v")]

node_dict = {
    '0': n0, '1': n1, '2': n2, '3': n3, '4': n4,
    '5': n5, '6': n6, '7': n7, '8': n8, '9': n9, 'A': start_keypad
}

def combination_to_directions(combination, start_node):
    res = ""
    current_node = start_node
    visited_nodes = set()  # Initialize a set to track visited nodes
    
    for char in combination:
        print("-----------")
        print(char)
        print("-----------")
        target_node = node_dict[char]
        
        
        found = False
        visited_nodes.clear()
        while not found:
            for next_node, direction in current_node.transitions:
                if next_node == target_node and next_node not in visited_nodes:
                    res += direction
                    current_node = next_node
                    visited_nodes.add(current_node)
                    found = True
                    break
            if not found:
                for next_node, direction in current_node.transitions:
                    if next_node == n5 or next_node == n2 and next_node not in visited_nodes:
                        res += direction
                        current_node = next_node
                        visited_nodes.add(current_node)  
                        break       
            if not found:
                for next_node, direction in current_node.transitions:
                    if next_node not in visited_nodes:
                        res += direction
                        current_node = next_node
                        visited_nodes.add(current_node) 
                        break
    
        res += 'A'
        visited_nodes.clear()
        
    return res

def bfs_shortest_path(start_node, target_node):
    queue = deque([(start_node, [])])
    visited = set([start_node])

    while queue:
        current_node, path = queue.popleft()

        if current_node == target_node:
            return path

        for neighbor, symbol in current_node.transitions:
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append((neighbor, path + [(neighbor, symbol)]))

    return None

combination = "029A"
#print(combination_to_directions(combination, start_keypad))
print(bfs_shortest_path(n9,start_keypad))