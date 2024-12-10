#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

void part1() {
  ifstream file("input.txt");
  vector<vector<int>> grid;
  string line;
  while (getline(file, line)) {
    if (!line.empty()) {
      vector<int> row;
      for (char ch : line) {
        if (isdigit(ch)) {
          row.push_back(ch - '0');
        }
      }
      if (!row.empty()) {
        grid.push_back(row);
      }
    }
  }

  int totalTrailheadScore = 0;
  for (int x = 0; x < grid.size(); ++x) {
    for (int y = 0; y < grid[x].size(); ++y) {
      if (grid[x][y] == 0) {
        int score = 0;
        vector<vector<bool>> visited(grid.size(),
                                     vector<bool>(grid[0].size(), false));
        queue<pair<int, int>> q;
        q.emplace(x, y);
        visited[x][y] = true;

        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        while (!q.empty()) {
          auto [currX, currY] = q.front();
          q.pop();

          if (grid[currX][currY] == 9) {
            score++;
          }

          for (auto [dx, dy] : directions) {
            int newX = currX + dx;
            int newY = currY + dy;

            if (newX >= 0 && newX < grid.size() && newY >= 0 &&
                newY < grid[0].size() && !visited[newX][newY] &&
                grid[newX][newY] == grid[currX][currY] + 1) {

              q.emplace(newX, newY);
              visited[newX][newY] = true;
            }
          }
        }

        totalTrailheadScore += score;
      }
    }
  }

  cout << "Total trailhead score: " << totalTrailheadScore << endl;
}

void part2() {
  ifstream file("input.txt");
  vector<vector<int>> grid;
  string line;
  while (getline(file, line)) {
    if (!line.empty()) {
      vector<int> row;
      for (char ch : line) {
        if (isdigit(ch)) {
          row.push_back(ch - '0');
        }
      }
      if (!row.empty()) {
        grid.push_back(row);
      }
    }
  }

  int totalTrailheadScore = 0;
  for (int x = 0; x < grid.size(); ++x) {
    for (int y = 0; y < grid[x].size(); ++y) {
      if (grid[x][y] == 0) {
        int score = 0;
        queue<pair<int, int>> q;
        q.emplace(x, y);

        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        while (!q.empty()) {
          auto [currX, currY] = q.front();
          q.pop();

          if (grid[currX][currY] == 9) {
            score++;
          }

          for (auto [dx, dy] : directions) {
            int newX = currX + dx;
            int newY = currY + dy;

            if (newX >= 0 && newX < grid.size() && newY >= 0 &&
                newY < grid[0].size() &&
                grid[newX][newY] == grid[currX][currY] + 1) {

              q.emplace(newX, newY);
            }
          }
        }

        totalTrailheadScore += score;
      }
    }
  }

  cout << "Total 2 trailhead score: " << totalTrailheadScore << endl;
}

int main() {
  part1();
  part2();
  return 0;
}