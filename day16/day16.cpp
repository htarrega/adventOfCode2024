#include <climits>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

const vector<pair<int, int>> DIRECTIONS = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
const int TURN_PENALTY = 1000;
const int MOVE_PENALTY = 1;

struct State {
  int x, y, direction, score;

  bool operator>(const State &other) const { return score > other.score; }
};

int findLowestScorePath(vector<vector<char>> &maze) {
  int rows = maze.size();
  int cols = maze[0].size();

  pair<int, int> start, end;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (maze[i][j] == 'S')
        start = {i, j};
      if (maze[i][j] == 'E')
        end = {i, j};
    }
  }

  vector<vector<vector<bool>>> visited(
      rows, vector<vector<bool>>(cols, vector<bool>(4, false)));

  priority_queue<State, vector<State>, greater<State>> pq;
  pq.push({start.first, start.second, 0, 0});

  while (!pq.empty()) {
    State current = pq.top();
    pq.pop();

    if (current.x == end.first && current.y == end.second) {
      return current.score;
    }

    if (visited[current.x][current.y][current.direction])
      continue;
    visited[current.x][current.y][current.direction] = true;

    int newX = current.x + DIRECTIONS[current.direction].first;
    int newY = current.y + DIRECTIONS[current.direction].second;

    if (newX >= 0 && newX < rows && newY >= 0 && newY < cols &&
        maze[newX][newY] != '#') {
      pq.push({newX, newY, current.direction, current.score + MOVE_PENALTY});
    }

    int clockwiseDir = (current.direction + 1) % 4;
    pq.push({current.x, current.y, clockwiseDir, current.score + TURN_PENALTY});

    int counterClockwiseDir = (current.direction - 1 + 4) % 4;
    pq.push({current.x, current.y, counterClockwiseDir,
             current.score + TURN_PENALTY});
  }

  return -1;
}

vector<vector<char>> loadMaze(const string &filename) {
  vector<vector<char>> maze;
  ifstream file(filename);
  string line;

  while (getline(file, line)) {
    maze.push_back(vector<char>(line.begin(), line.end()));
  }

  return maze;
}

void part1() {
  vector<vector<char>> maze = loadMaze("input.txt");
  int lowestScore = findLowestScorePath(maze);
  cout << "Lowest possible score: " << lowestScore << endl;
}

int main() {
  part1();
  return 0;
}