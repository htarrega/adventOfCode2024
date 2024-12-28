#include <climits>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
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

struct State2 {
  int x, y, direction, score;
  bool operator>(const State2 &other) const { return score > other.score; }
};

map<tuple<int, int, int>, int>
findAllPaths(const vector<vector<char>> &maze,
             const vector<tuple<int, int, int>> &starts) {
  int rows = maze.size();
  int cols = maze[0].size();

  map<tuple<int, int, int>, int> dist;
  priority_queue<State2, vector<State2>, greater<State2>> pq;

  for (const auto &[startX, startY, startDir] : starts) {
    dist[make_tuple(startX, startY, startDir)] = 0;
    pq.push({startX, startY, startDir, 0});
  }

  while (!pq.empty()) {
    State2 current = pq.top();
    pq.pop();

    auto currentState = make_tuple(current.x, current.y, current.direction);
    if (dist[currentState] < current.score)
      continue;

    for (int newDir = 0; newDir < 4; newDir++) {
      if (newDir == current.direction)
        continue;

      auto turnState = make_tuple(current.x, current.y, newDir);
      int newScore = current.score + 1000; // Turn penalty

      if (dist.find(turnState) == dist.end() || dist[turnState] > newScore) {
        dist[turnState] = newScore;
        pq.push({current.x, current.y, newDir, newScore});
      }
    }

    int newX = current.x + DIRECTIONS[current.direction].first;
    int newY = current.y + DIRECTIONS[current.direction].second;

    if (newX >= 0 && newX < rows && newY >= 0 && newY < cols &&
        maze[newX][newY] != '#') {
      auto moveState = make_tuple(newX, newY, current.direction);
      int newScore = current.score + 1; // Move penalty

      if (dist.find(moveState) == dist.end() || dist[moveState] > newScore) {
        dist[moveState] = newScore;
        pq.push({newX, newY, current.direction, newScore});
      }
    }
  }

  return dist;
}

int getOptimalScore(const vector<vector<char>> &maze) {
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

  auto distances = findAllPaths(maze, {{start.first, start.second, 0}});

  int bestScore = INT_MAX;
  for (int dir = 0; dir < 4; dir++) {
    auto state = make_tuple(end.first, end.second, dir);
    if (distances.find(state) != distances.end()) {
      bestScore = min(bestScore, distances[state]);
    }
  }

  return bestScore;
}

void part2() {
  vector<vector<char>> maze = loadMaze("input.txt");
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

  auto fromStart = findAllPaths(maze, {{start.first, start.second, 0}});

  vector<tuple<int, int, int>> endStarts;
  for (int dir = 0; dir < 4; dir++) {
    endStarts.push_back({end.first, end.second, dir});
  }
  auto fromEnd = findAllPaths(maze, endStarts);

  int optimalScore = getOptimalScore(maze);

  set<pair<int, int>> optimalTiles;
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      for (int dir = 0; dir < 4; dir++) {
        auto stateFromStart = make_tuple(row, col, dir);
        auto stateFromEnd = make_tuple(row, col, (dir + 2) % 4);

        if (fromStart.find(stateFromStart) != fromStart.end() &&
            fromEnd.find(stateFromEnd) != fromEnd.end()) {
          if (fromStart[stateFromStart] + fromEnd[stateFromEnd] ==
              optimalScore) {
            optimalTiles.insert({row, col});
          }
        }
      }
    }
  }

  cout << "Number of tiles on optimal paths for part 2: " << optimalTiles.size()
       << endl;
}

void part1() {
  vector<vector<char>> maze = loadMaze("input.txt");
  int lowestScore = findLowestScorePath(maze);
  cout << "Lowest possible score: " << lowestScore << endl;
}

int main() {
  part1();
  part2();
  return 0;
}