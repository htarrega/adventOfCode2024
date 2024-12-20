#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

const vector<pair<int, int>> DIRECTIONS = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

struct State {
  int x, y;
  int steps;
  bool cheating;
  int cheatStepsLeft;
  pair<int, int> cheatStart;

  State(int x, int y, int s, bool c, int cl, pair<int, int> cs)
      : x(x), y(y), steps(s), cheating(c), cheatStepsLeft(cl), cheatStart(cs) {}
};

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

bool isValidPosition(int x, int y, const vector<vector<char>> &grid) {
  return x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size();
}

pair<pair<int, int>, pair<int, int>>
findStartAndEnd(const vector<vector<char>> &grid) {
  pair<int, int> start = {-1, -1};
  pair<int, int> end = {-1, -1};
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].size(); j++) {
      if (grid[i][j] == 'S') {
        start = {i, j};
      } else if (grid[i][j] == 'E') {
        end = {i, j};
      }
    }
  }
  return {start, end};
}

int stepsToExit(const vector<vector<char>> &grid, pair<int, int> start,
                pair<int, int> end) {
  if (start.first == -1 || end.first == -1)
    return -1;

  int rows = grid.size();
  int cols = grid[0].size();
  vector<vector<bool>> visited(rows, vector<bool>(cols, false));
  vector<vector<int>> distance(rows, vector<int>(cols, -1));
  queue<pair<int, int>> q;

  q.push(start);
  visited[start.first][start.second] = true;
  distance[start.first][start.second] = 0;

  while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop();

    if (x == end.first && y == end.second) {
      return distance[x][y];
    }

    for (auto [dx, dy] : DIRECTIONS) {
      int newX = x + dx;
      int newY = y + dy;

      if (isValidPosition(newX, newY, grid) && grid[newX][newY] != '#' &&
          !visited[newX][newY]) {
        visited[newX][newY] = true;
        distance[newX][newY] = distance[x][y] + 1;
        q.push({newX, newY});
      }
    }
  }
  return -1;
}

struct CheatResult {
  int timeSaved;
  pair<int, int> startPos;
  pair<int, int> endPos;
};

vector<CheatResult> findCheats(const vector<vector<char>> &grid,
                               pair<int, int> start, pair<int, int> end) {
  vector<CheatResult> results;
  int rows = grid.size();
  int cols = grid[0].size();
  int normalTime = stepsToExit(grid, start, end);

  set<tuple<int, int, bool, int>> visited;
  queue<State> q;
  q.push(State(start.first, start.second, 0, false, 0, {-1, -1}));

  while (!q.empty()) {
    State curr = q.front();
    q.pop();

    if (curr.x == end.first && curr.y == end.second &&
        curr.cheatStart.first != -1) {
      int timeSaved = normalTime - curr.steps;
      if (timeSaved > 0) {
        results.push_back({timeSaved, curr.cheatStart, {curr.x, curr.y}});
      }
      continue;
    }

    for (auto [dx, dy] : DIRECTIONS) {
      int newX = curr.x + dx;
      int newY = curr.y + dy;

      if (!isValidPosition(newX, newY, grid))
        continue;

      if (!curr.cheating) {
        if (grid[newX][newY] != '#') {
          auto state = make_tuple(newX, newY, false, 0);
          if (visited.find(state) == visited.end()) {
            visited.insert(state);
            q.push(
                State(newX, newY, curr.steps + 1, false, 0, curr.cheatStart));
          }
        }

        auto cheatState = make_tuple(newX, newY, true, 2);
        if (visited.find(cheatState) == visited.end()) {
          visited.insert(cheatState);
          q.push(State(newX, newY, curr.steps + 1, true, 1, {curr.x, curr.y}));
        }
      } else if (curr.cheatStepsLeft > 0) {
        auto state = make_tuple(newX, newY, true, curr.cheatStepsLeft - 1);
        if (visited.find(state) == visited.end() && grid[newX][newY] != '#') {
          visited.insert(state);
          q.push(State(newX, newY, curr.steps + 1, true,
                       curr.cheatStepsLeft - 1, curr.cheatStart));
        }
      }
    }
  }
  return results;
}

int main() {
  vector<vector<char>> grid;
  string line;
  while (getline(cin, line)) {
    grid.push_back(vector<char>(line.begin(), line.end()));
  }

  auto [start, end] = findStartAndEnd(grid);
  vector<CheatResult> cheats = findCheats(grid, start, end);

  int count = 0;
  for (const auto &cheat : cheats) {
    if (cheat.timeSaved >= 100) {
      count++;
    }
  }

  cout << count << endl;
  return 0;
}