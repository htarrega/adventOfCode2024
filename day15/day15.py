def part1():
    directions = False
    dirs = ""
    grid = []
    robot_position = None

    with open('input.txt', 'r') as file:
        for i, line in enumerate(file):
            line = line.strip()
            if directions:
                dirs += line
            elif len(line) > 3:
                grid.append(list(line))
                if "@" in line:
                    robot_position = (i, line.index("@"))
            else:
                directions = True

    moves_x = {'v': 1, '>': 0, '<': 0, '^': -1}
    moves_y = {'v': 0, '>': 1, '<': -1, '^': 0}

    for dir in dirs:
        new_x = robot_position[0]+moves_x[dir]
        new_y = robot_position[1]+moves_y[dir]

        next_elem = grid[new_x][new_y]
        if next_elem == '#':
            continue
        if next_elem == '.':
            grid[robot_position[0]][robot_position[1]] = '.'
            robot_position = (new_x,new_y)
            grid[robot_position[0]][robot_position[1]] = '@'
        elif next_elem == 'O':
            last_pos = (new_x,new_y)
            last_elem = grid[last_pos[0]][last_pos[1]]
            while(last_elem == 'O'):
                last_pos = (last_pos[0]+moves_x[dir] , last_pos[1]+moves_y[dir])
                last_elem = grid[last_pos[0]][last_pos[1]]
            if last_elem == ".":
                grid[robot_position[0]][robot_position[1]] = '.'
                robot_position = (new_x,new_y)
                grid[robot_position[0]][robot_position[1]] = '@'
                grid[last_pos[0]][last_pos[1]] = 'O'
    
    total_gps = 0
    for y, row in enumerate(grid):
        for x, cell in enumerate(row):
            if cell == 'O':
                gps_coordinate = 100 * y + x
                total_gps += gps_coordinate

    
    print("Solution 1: "+ str(total_gps))

def part2():
    conv = {'>': 1 + 0j, '<': -1 + 0j, '^': -1j, 'v': 1j}
    
    with open('input.txt', 'r') as file:
        narrow_space, directions = file.read().split('\n\n')
    
    grid = [''.join([c*2 if c in ['#','.','@'] else '[]' for c in line]).replace('@@','@.') 
             for line in narrow_space.split('\n')]
    
    width, height = len(grid[0]), len(grid)
    grid = {complex(x,y): grid[y][x] for y in range(height) for x in range(width)}

    robot_position = next(key for key in grid if grid[key] == '@')
    grid[robot_position] = '.'
    
    for direction in [conv[c] for c in directions.replace('\n','')]:
        if grid[robot_position + direction] == '.':
            robot_position += direction
        
        elif grid[robot_position + direction] in ['[', ']'] and direction in [-1+0j, 1+0j]:
            count = 1
            while grid[robot_position + count * direction] in ['[', ']']:
                count += 1
            if grid[robot_position + count * direction] == '.':
                for i in range(count, 0, -1):
                    grid[robot_position + i * direction] = grid[robot_position + (i-1) * direction]
                robot_position += direction
        
        elif grid[robot_position + direction] in ['[', ']'] and direction in [1j, -1j]:
            front = [z for z in [robot_position + direction, robot_position + direction - 1] if grid[z] == '[']
            seen = set(front)
            move = True
            
            while move and front:
                loc = front.pop()
                move = (grid[loc + direction] != '#' and 
                        grid[loc + direction + 1 + 0j] != '#')
                
                new = [z for z in [loc + direction + complex(j,0) for j in range(-1,2)] 
                       if grid[z] == '[']
                seen = seen.union(set(new))
                front += new
            
            if move:
                for layer in range(abs(int(min([-direction.imag * z.imag for z in seen]) - robot_position.imag)), 0, -1):
                    for z in [w for w in seen if w.imag == (robot_position + layer * direction).imag]:

                        grid[z] = '.'
                        grid[z + 1 + 0j] = '.'
                        
                        grid[z + direction] = '['
                        grid[z + direction + 1 + 0j] = ']'
                
                robot_position += direction

    total_gps = 0
    for loc in grid:
        if grid[loc] == '[':
            gps_coordinate = 100 * loc.imag + loc.real
            total_gps += gps_coordinate

    print("Solution 2: " + str(int(total_gps)))



part1()
part2()