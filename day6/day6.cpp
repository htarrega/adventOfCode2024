#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> loadGridFromFile(const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Unable to open file: " + filename);
  }
  std::vector<std::string> grid;
  std::string line;
  while (std::getline(file, line)) {
    if (!line.empty()) {
      grid.push_back(line);
    }
  }
  return grid;
}

int part1(std::vector<std::string> &lab) {
  bool endReached = false;
  int xpos = 0;
  int ypos = 0;
  std::vector<int> xdir = {-1, 0, 1, 0};
  std::vector<int> ydir = {0, 1, 0, -1};
  int dir = 0;
  int xlimit = lab.size() - 1;
  int ylimit = lab[0].size() - 1;
  int xprev = 0;
  int yprev = 0;
  bool found = false;
  for (int i = 0; i < lab.size(); i++) {
    for (int j = 0; j < lab[i].size(); j++) {
      if (lab[i][j] == '^') {
        xpos = i;
        ypos = j;
        found = true;
        lab[xpos][ypos] = 'X';
        break;
      }
    }
    if (found)
      break;
  }
  while (!endReached) {
    xprev = xpos;
    yprev = ypos;
    xpos = xpos + xdir[dir];
    ypos = ypos + ydir[dir];
    if (xpos >= lab.size() || ypos >= lab[0].size() || xpos < 0 || ypos < 0) {
      endReached = true;
      continue;
    }
    if (lab[xpos][ypos] == '#') {
      xpos = xprev;
      ypos = yprev;
      dir = (dir + 1) % 4;
      continue;
    }
    if (lab[xpos][ypos] != 'X') {
      lab[xpos][ypos] = 'X';
    }
  }
  int total = 0;
  for (int i = 0; i < lab.size(); i++) {
    for (int j = 0; j < lab[i].size(); j++) {
      if (lab[i][j] == 'X') {
        total++;
      }
    }
  }
  return total;
}

bool isLoop(const std::vector<std::string> &originalLab, int startX,
            int startY) {
  std::vector<std::string> lab = originalLab;
  std::vector<std::vector<std::vector<bool>>> visited(
      lab.size(), std::vector<std::vector<bool>>(lab[0].size(),
                                                 std::vector<bool>(4, false)));

  int xpos = startX;
  int ypos = startY;
  int dir = 0;
  std::vector<int> xdir = {-1, 0, 1, 0};
  std::vector<int> ydir = {0, 1, 0, -1};

  int steps = 0;
  const int MAX_STEPS = lab.size() * lab[0].size() * 4 * 2;

  while (steps < MAX_STEPS) {
    if (visited[xpos][ypos][dir]) {
      return true;
    }
    visited[xpos][ypos][dir] = true;

    int nextX = xpos + xdir[dir];
    int nextY = ypos + ydir[dir];

    if (nextX < 0 || nextX >= lab.size() || nextY < 0 ||
        nextY >= lab[0].size()) {
      return false;
    }

    if (lab[nextX][nextY] == '#' || lab[nextX][nextY] == 'O') {
      dir = (dir + 1) % 4;
    } else {
      xpos = nextX;
      ypos = nextY;
    }
    steps++;
  }
  return true;
}

int part2(const std::vector<std::string> &originalLab) {
  int startX = 0, startY = 0;
  bool found = false;
  for (int i = 0; i < originalLab.size() && !found; i++) {
    for (int j = 0; j < originalLab[i].size(); j++) {
      if (originalLab[i][j] == '^' || originalLab[i][j] == 'X') {
        startX = i;
        startY = j;
        found = true;
        break;
      }
    }
  }

  int loopCount = 0;
  for (int i = 0; i < originalLab.size(); i++) {
    for (int j = 0; j < originalLab[0].size(); j++) {
      if (originalLab[i][j] != '.' || (i == startX && j == startY)) {
        continue;
      }
      std::vector<std::string> testLab = originalLab;
      testLab[i][j] = 'O';
      if (isLoop(testLab, startX, startY)) {
        loopCount++;
      }
    }
  }
  return loopCount;
}

void printGrid(const std::vector<std::string> &grid) {
  for (const auto &row : grid) {
    std::cout << row << std::endl;
  }
}

int main() {
  std::vector<std::string> grid = loadGridFromFile("input.txt");
  std::vector<std::string> gridCopy = grid;
  std::cout << "Part 1 - Distinct positions: " << part1(grid) << std::endl;
  std::cout << "Part 2 - Possible obstruction positions: " << part2(gridCopy)
            << std::endl;
  return 0;
}