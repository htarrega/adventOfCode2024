#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

std::vector<std::vector<char>> fillGrid(const std::string& input, size_t& nrows,
                                        size_t& ncols) {
  std::vector<std::string> lines;
  std::string line;
  nrows = 0;
  ncols = 0;

  for (char c : input) {
    if (c == '\n') {
      if (!line.empty()) {
        lines.push_back(line);
        nrows++;
        ncols = std::max(ncols, line.size());
        line.clear();
      }
    } else {
      line += c;
    }
  }
  if (!line.empty()) {
    lines.push_back(line);
    nrows++;
    ncols = std::max(ncols, line.size());
  }

  std::vector<std::vector<char>> grid(nrows, std::vector<char>(ncols, ' '));
  for (size_t i = 0; i < nrows; i++) {
    for (size_t j = 0; j < lines[i].size(); j++) {
      grid[i][j] = lines[i][j];
    }
  }

  return grid;
}

int main() {
  std::ifstream file("aux.txt");
  std::string input;

  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      input += line + '\n';
    }
    file.close();
  }
  size_t nrows, ncols;
  auto grid = fillGrid(input, nrows, ncols);

  for (const auto& row : grid) {
    for (const auto& cell : row) {
      std::cout << cell;
    }
    std::cout << '\n';
  }

  // flowers
  // unordered_map<char

  return 0;
}
