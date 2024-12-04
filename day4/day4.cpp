#include <fstream>
#include <iostream>
#include <stdexcept>
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

int part1(const std::vector<std::string> &grid) {
  const std::pair<int, int> DIRECTIONS[8] = {
      {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
  int totalOccurrences = 0;

  for (int row = 0; row < grid.size(); ++row) {
    for (int col = 0; col < grid[row].length(); ++col) {
      for (const auto &[dx, dy] : DIRECTIONS) {
        const std::string TARGET_WORD = "XMAS";
        bool found = true;

        for (int i = 0; i < TARGET_WORD.length(); ++i) {
          int checkRow = row + i * dx;
          int checkCol = col + i * dy;

          if (checkRow < 0 || checkRow >= grid.size() || checkCol < 0 ||
              checkCol >= grid[0].length() ||
              grid[checkRow][checkCol] != TARGET_WORD[i]) {
            found = false;
            break;
          }
        }

        if (found) {
          ++totalOccurrences;
        }
      }
    }
  }

  return totalOccurrences;
}

int part2(const std::vector<std::string> &grid) {
  int totalOccurrences = 0;

  for (int row = 1; row < grid.size() - 1; ++row) {
    for (int col = 1; col < grid[row].length() - 1; ++col) {
      bool isValid = true;

      // Check top-left to bottom-right diagonal for "MAS" or "SAM"
      std::string topLeft = "";
      for (int i = -1; i <= 1; ++i) {
        int r = row + i, c = col + i;
        if (r < 0 || r >= grid.size() || c < 0 || c >= grid[0].length()) {
          isValid = false;
          break;
        }
        topLeft += grid[r][c];
      }
      if (!(topLeft == "MAS" || topLeft == "SAM"))
        isValid = false;

      // Check top-right to bottom-left diagonal for "MAS" or "SAM"
      std::string topRight = "";
      for (int i = -1; i <= 1; ++i) {
        int r = row + i, c = col - i;
        if (r < 0 || r >= grid.size() || c < 0 || c >= grid[0].length()) {
          isValid = false;
          break;
        }
        topRight += grid[r][c];
      }
      if (!(topRight == "MAS" || topRight == "SAM"))
        isValid = false;

      if (isValid) {
        ++totalOccurrences;
      }
    }
  }

  return totalOccurrences;
}

int main() {
  try {
    std::vector<std::string> grid = loadGridFromFile("input.txt");

    std::cout << "Part 1 - XMAS occurrences: " << part1(grid) << std::endl;
    std::cout << "Part 2 - X-MAS occurrences: " << part2(grid) << std::endl;
  } catch (const std::exception &e) {
    return 1;
  }
  return 0;
}