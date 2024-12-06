#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> loadGridFromFile(const std::string& filename) {
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

//     |
// ^   |
// y   |
//     --------
//     x ->
int part1(std::vector<std::string>& lab) {
  bool endReached = false;
  int xpos = 0;
  int ypos = 0;
  std::vector<int> xdir = {-1, 0, 1, 0};  // UP, RIGHT, DOWN, LEFT
  std::vector<int> ydir = {0, 1, 0, -1};  // UP, RIGHT, DOWN, LEFT
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
    if (found) break;
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

void printGrid(const std::vector<std::string>& grid) {
  for (const auto& row : grid) {
    std::cout << row << std::endl;
  }
}

int main() {
  std::vector<std::string> grid = loadGridFromFile("input.txt");
  std::cout << "Part 1 - Distinct positions: " << part1(grid) << std::endl;
  return 0;
}