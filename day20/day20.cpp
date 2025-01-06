#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

struct Pos {
  int row, col;
  bool operator==(const Pos& other) const {
    return row == other.row && col == other.col;
  }
  bool operator<(const Pos& other) const {
    return row < other.row || (row == other.row && col < other.col);
  }
};

struct Cheat {
  Pos start, end;
  int savings;
  bool operator<(const Cheat& other) const { return savings > other.savings; }
};

class Solution {
  vector<string> grid;
  Pos start, end;
  int rows, cols;
  vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

  bool isValid(int row, int col, bool canCheat = false) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) return false;
    return canCheat || grid[row][col] != '#';
  }

  int bfs(Pos from, Pos to, bool allowWalls = false) {
    vector<vector<int>> dist(rows,
                             vector<int>(cols, numeric_limits<int>::max()));
    queue<Pos> q;

    q.push(from);
    dist[from.row][from.col] = 0;

    while (!q.empty()) {
      Pos curr = q.front();
      q.pop();

      if (curr == to) return dist[curr.row][curr.col];

      for (auto& dir : dirs) {
        int newRow = curr.row + dir.first;
        int newCol = curr.col + dir.second;

        if (isValid(newRow, newCol, allowWalls) &&
            dist[newRow][newCol] == numeric_limits<int>::max()) {
          dist[newRow][newCol] = dist[curr.row][curr.col] + 1;
          q.push({newRow, newCol});
        }
      }
    }
    return numeric_limits<int>::max();
  }

  vector<Cheat> findCheats(int normalPathLength) {
    vector<Cheat> cheats;

    for (int r1 = 0; r1 < rows; r1++) {
      for (int c1 = 0; c1 < cols; c1++) {
        if (!isValid(r1, c1)) continue;

        int toStart = bfs(start, {r1, c1});
        if (toStart == numeric_limits<int>::max()) continue;

        for (int r2 = max(0, r1 - 2); r2 <= min(rows - 1, r1 + 2); r2++) {
          for (int c2 = max(0, c1 - 2); c2 <= min(cols - 1, c1 + 2); c2++) {
            if (!isValid(r2, c2)) continue;
            if (abs(r2 - r1) + abs(c2 - c1) > 2) continue;

            int toEnd = bfs({r2, c2}, end);
            if (toEnd == numeric_limits<int>::max()) continue;

            int cheatedPath = toStart + abs(r2 - r1) + abs(c2 - c1) + toEnd;
            int savings = normalPathLength - cheatedPath;

            if (savings > 0) {
              cheats.push_back({{r1, c1}, {r2, c2}, savings});
            }
          }
        }
      }
    }
    return cheats;
  }

 public:
  int solve(vector<string>& input) {
    grid = input;
    rows = grid.size();
    cols = grid[0].size();

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (grid[i][j] == 'S') start = {i, j};
        if (grid[i][j] == 'E') end = {i, j};
      }
    }

    int normalPathLength = bfs(start, end);
    vector<Cheat> cheats = findCheats(normalPathLength);

    int count = 0;
    for (const auto& cheat : cheats) {
      if (cheat.savings >= 100) count++;
    }
    return count;
  }
};

void part1() {
  ifstream file("input.txt");

  vector<string> input;
  string line;
  while (getline(file, line)) {
    if (!line.empty()) {
      input.push_back(line);
    }
  }
  file.close();

  Solution solution;
  int result = solution.solve(input);
  cout << "Part 1 Result: " << result << endl;
}

class SolutionPart2 {
  vector<string> grid;
  int rows, cols;
  Pos start, end;
  vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

  bool isValid(int row, int col) {
    return row >= 0 && row < rows && col >= 0 && col < cols &&
           grid[row][col] != '#';
  }

 public:
  int solvePart2(vector<string>& input) {
    grid = input;
    rows = grid.size();
    cols = grid[0].size();

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (grid[i][j] == 'S') start = {i, j};
        if (grid[i][j] == 'E') end = {i, j};
      }
    }

    // BFS to compute shortest paths
    queue<pair<Pos, int>> q;
    map<Pos, int> visited;
    q.push({start, 0});
    visited[start] = 0;

    while (!q.empty()) {
      auto [curr, time] = q.front();
      q.pop();

      if (curr == end) continue;

      for (auto& dir : dirs) {
        int newRow = curr.row + dir.first;
        int newCol = curr.col + dir.second;
        Pos next = {newRow, newCol};

        if (isValid(newRow, newCol) && visited.find(next) == visited.end()) {
          visited[next] = time + 1;
          q.push({next, time + 1});
        }
      }
    }

    int cheats = 0;
    const int threshold = 100;
    vector<pair<Pos, int>> path(visited.begin(), visited.end());
    sort(path.begin(), path.end(),
         [](auto& a, auto& b) { return a.second < b.second; });

    for (size_t t2 = threshold; t2 < path.size(); t2++) {
      for (size_t t1 = 0; t1 < t2 - threshold; t1++) {
        Pos p1 = path[t1].first;
        Pos p2 = path[t2].first;
        int distance = abs(p1.row - p2.row) + abs(p1.col - p2.col);
        int timeSaved = path[t2].second - path[t1].second - distance;

        if (distance <= 20 && timeSaved >= threshold) {
          cheats++;
        }
      }
    }

    return cheats;
  }
};

void part2() {
  ifstream file("input.txt");
  vector<string> input;
  string line;
  while (getline(file, line)) {
    if (!line.empty()) {
      input.push_back(line);
    }
  }
  file.close();

  SolutionPart2 solutionPart2;
  int result = solutionPart2.solvePart2(input);
  cout << "Part 2 Result: " << result << endl;
}

int main() {
  part1();
  part2();
  return 0;
}
