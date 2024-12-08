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
  int total = 0;

  return total;
}

void printGrid(const std::vector<std::string>& grid) {
  for (const auto& row : grid) {
    std::cout << row << std::endl;
  }
}

int main() {
  std::vector<std::string> grid = loadGridFromFile("input.txt");
  printGrid(grid);
  std::cout << "Part 1 - Distinct positions: " << part1(grid) << std::endl;
  return 0;
}