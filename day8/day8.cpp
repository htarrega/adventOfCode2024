#include <cmath>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

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

unordered_map<string, vector<pair<int, int>>>
getAntennasPos(std::vector<std::string> &grid) {
  unordered_map<string, vector<pair<int, int>>> antennas;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].size(); j++)
      if (grid[i][j] != '.') {
        string key(1, grid[i][j]);
        if (antennas.find(key) != antennas.end()) {
          antennas[key].emplace_back(i, j);
        } else {
          antennas[key] = {{i, j}};
        }
      }
  }
  return antennas;
}

int checkPairs(const unordered_map<string, vector<pair<int, int>>> &antennas,
               vector<string> &grid) {
  int total = 0;

  for (const auto &entry : antennas) {
    const vector<pair<int, int>> &positions = entry.second;

    for (int i = 0; i < positions.size(); i++) {
      for (int j = i + 1; j < positions.size(); j++) {
        int x1 = positions[i].first;
        int y1 = positions[i].second;
        int x2 = positions[j].first;
        int y2 = positions[j].second;

        int dx = x2 - x1;
        int dy = y2 - y1;

        int x1_extra = x1 - dx;
        int y1_extra = y1 - dy;
        int x2_extra = x2 + dx;
        int y2_extra = y2 + dy;

        if (x1_extra >= 0 && x1_extra < grid.size() && y1_extra >= 0 &&
            y1_extra < grid[x1_extra].size()) {
          if (grid[x1_extra][y1_extra] != '#') {
            grid[x1_extra][y1_extra] = '#';
            total++;
          }
        }

        if (x2_extra >= 0 && x2_extra < grid.size() && y2_extra >= 0 &&
            y2_extra < grid[x2_extra].size()) {
          if (grid[x2_extra][y2_extra] != '#') {
            grid[x2_extra][y2_extra] = '#';
            total++;
          }
        }
      }
    }
  }

  return total;
}

int checkPairs2(const unordered_map<string, vector<pair<int, int>>> &antennas,
                vector<string> &grid) {
  int total = 0;
  set<pair<int, int>> antinodes;

  for (const auto &entry : antennas) {
    const vector<pair<int, int>> &positions = entry.second;

    if (positions.size() < 2)
      continue;

    for (int i = 0; i < positions.size(); i++) {
      for (int j = i + 1; j < positions.size(); j++) {
        auto [x1, y1] = positions[i];
        auto [x2, y2] = positions[j];

        for (const auto &[x, y] : positions) {
          int cross_product = (x - x1) * (y2 - y1) - (y - y1) * (x2 - x1);

          if (cross_product == 0) {
            antinodes.insert({x, y});
          }
        }

        int dx = x2 - x1;
        int dy = y2 - y1;

        vector<pair<int, int>> steps = {{dx, dy}, {-dx, -dy}};

        for (auto [sdx, sdy] : steps) {
          int x = x1, y = y1;

          while (true) {
            x += sdx;
            y += sdy;

            if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size()) {
              break;
            }

            antinodes.insert({x, y});
          }
        }
      }
    }
  }

  return antinodes.size();
}

void part1() {
  int total = 0;
  std::vector<std::string> grid = loadGridFromFile("input.txt");
  unordered_map<string, vector<pair<int, int>>> antennas = getAntennasPos(grid);
  total = checkPairs(antennas, grid);
  std::cout << "Part 1 - Total antinodes: " << total << std::endl;
}

void part2() {
  int total = 0;
  std::vector<std::string> grid = loadGridFromFile("input.txt");
  unordered_map<string, vector<pair<int, int>>> antennas = getAntennasPos(grid);
  total = checkPairs2(antennas, grid);
  std::cout << "Part 2 - Total antinodes: " << total << std::endl;
}

int main() {
  part1();
  part2();
  return 0;
}