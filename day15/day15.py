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


part1()
