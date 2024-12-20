#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

const vector<pair<int, int>> DIRECTIONS = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

vector<vector<char>> loadGrid(const string &filename) {
  vector<vector<char>> grid;
  ifstream file(filename);
  string line;

  while (getline(file, line)) {
    vector<char> row(line.begin(), line.end());
    grid.push_back(row);
  }

  return grid;
}

void part1() { vector<vector<char>> grid = loadGrid("input.txt"); }

bool hasPathToExit(vector<vector<bool>> &grid, int side) {
  vector<vector<bool>> visited(side, vector<bool>(side, false));
  queue<pair<int, int>> q;
  q.push({0, 0});
  visited[0][0] = true;

  while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop();

    if (x == side - 1 && y == side - 1) {
      return true;
    }

    for (auto &[dx, dy] : DIRECTIONS) {
      int newX = x + dx;
      int newY = y + dy;
      if (newX >= 0 && newX < side && newY >= 0 && newY < side &&
          !visited[newX][newY] && grid[newX][newY]) {
        visited[newX][newY] = true;
        q.push({newX, newY});
      }
    }
  }
  return false;
}

int main() {
  part1();
  return 0;
}