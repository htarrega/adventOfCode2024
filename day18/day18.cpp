#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

const vector<pair<int, int>> DIRECTIONS = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

vector<pair<int, int>> loadCorrupted(const string &filename) {
  vector<pair<int, int>> corrupted;
  ifstream file(filename);
  string line;
  while (getline(file, line)) {
    stringstream ss(line);
    string part1, part2;
    getline(ss, part1, ',');
    getline(ss, part2, ',');
    int x = stoi(part1);
    int y = stoi(part2);
    corrupted.push_back(make_pair(x, y));
  }
  return corrupted;
}

bool isNotCorruptedAndExistsAndNotVisited(int x, int y,
                                          vector<vector<bool>> &grid,
                                          vector<vector<bool>> &visited) {
  if (x < 0 || y < 0 || x >= grid.size() || y >= grid.size()) {
    return false;
  }
  if (visited[x][y] == true) {
    return false;
  }
  return grid[x][y];
}

void part1() {
  vector<pair<int, int>> corrupted = loadCorrupted("input.txt");
  int side = 71;
  int xdst = 70;
  int ydst = 70;

  vector<vector<bool>> grid(side, vector<bool>(side, true));

  const int KILOBYTE = 1 * 1024; // 1 KB = 1024 bytes

  for (int i = 0; i < KILOBYTE && i < corrupted.size(); ++i) {
    auto [x, y] = corrupted[i];
    grid[x][y] = false;
  }

  vector<vector<bool>> visited(side, vector<bool>(side, false));
  vector<vector<pair<int, int>>> parent(side,
                                        vector<pair<int, int>>(side, {-1, -1}));
  queue<pair<pair<int, int>, int>> q;
  q.push({{0, 0}, 0});
  visited[0][0] = true;

  int lowestScore = -1;
  pair<int, int> end;
  while (!q.empty()) {
    auto [current, dist] = q.front();
    q.pop();
    int x = current.first;
    int y = current.second;

    if (x == xdst && y == ydst) {
      lowestScore = dist;
      end = current;
      break;
    }

    for (auto &[dx, dy] : DIRECTIONS) {
      int newX = x + dx;
      int newY = y + dy;
      if (isNotCorruptedAndExistsAndNotVisited(newX, newY, grid, visited)) {
        visited[newX][newY] = true;
        parent[newX][newY] = {x, y};
        q.push({{newX, newY}, dist + 1});
      }
    }
  }

  cout << "Lowest number of steps for part 1: " << lowestScore << endl;
}

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

void part2() {
  vector<pair<int, int>> corrupted = loadCorrupted("input.txt");
  int side = 71;

  for (int i = 0; i < corrupted.size(); ++i) {
    vector<vector<bool>> grid(side, vector<bool>(side, true));

    for (int j = 0; j <= i; ++j) {
      auto [x, y] = corrupted[j];
      grid[x][y] = false;
    }
    if (!hasPathToExit(grid, side)) {
      auto [x, y] = corrupted[i];
      cout << "First block on route for part 2: ";
      cout << x << "," << y << endl;
      return;
    }
  }
}

int main() {
  part1();
  part2();
  return 0;
}