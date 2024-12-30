#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

struct Tile {
  char plant;
  int id;
  int x;
  int y;

  Tile(char p, int x, int y) : plant(p), id(-1), x(x), y(y) {}
};

vector<pair<int, int>> directions = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

vector<vector<Tile>> readTilesFromFile(const string& filename) {
  vector<vector<Tile>> tiles;
  ifstream file(filename);
  if (!file.is_open()) {
    cerr << "Error: Could not open file " << filename << endl;
    return tiles;
  }

  string line;
  int y = 0;
  while (getline(file, line)) {
    vector<Tile> row;
    for (int x = 0; x < line.size(); ++x) {
      row.emplace_back(line[x], x, y);
    }
    tiles.push_back(row);
    ++y;
  }

  file.close();
  return tiles;
}

void populateIDs(vector<vector<Tile>>& grid) {
  int idIndex = -1;
  int id;
  char plant;
  int matrix_width = grid[0].size();
  int matrix_height = grid.size();
  queue<pair<int, int>> tilesToProcess;

  for (int j = 0; j < matrix_height; ++j) {
    for (int i = 0; i < matrix_width; ++i) {
      if (grid[j][i].id != -1) {
        continue;
      }

      idIndex += 1;
      id = idIndex;
      grid[j][i].id = id;
      plant = grid[j][i].plant;

      tilesToProcess.emplace(i, j);

      while (!tilesToProcess.empty()) {
        auto [x, y] = tilesToProcess.front();
        tilesToProcess.pop();

        for (const auto& [dx, dy] : directions) {
          int nx = x + dx;
          int ny = y + dy;

          if (nx >= 0 && ny >= 0 && nx < matrix_width && ny < matrix_height &&
              grid[ny][nx].id == -1 && plant == grid[ny][nx].plant) {
            tilesToProcess.emplace(nx, ny);
            grid[ny][nx].id = id;
          }
        }
      }
    }
  }
}

vector<int> countElementsById(const vector<vector<Tile>>& grid) {
  int maxId = 0;
  for (const auto& row : grid) {
    for (const auto& tile : row) {
      if (tile.id > maxId) maxId = tile.id;
    }
  }

  vector<int> idCount(maxId + 1, 0);
  for (const auto& row : grid) {
    for (const auto& tile : row) {
      idCount[tile.id]++;
    }
  }

  return idCount;
}

vector<int> calculatePerimeterById(const vector<vector<Tile>>& grid) {
  int matrix_width = grid[0].size();
  int matrix_height = grid.size();
  vector<int> perimeterCount;

  for (int j = 0; j < matrix_height; ++j) {
    for (int i = 0; i < matrix_width; ++i) {
      int id = grid[j][i].id;
      int perimeter = 0;

      for (const auto& [dx, dy] : directions) {
        int nx = i + dx;
        int ny = j + dy;

        if (nx < 0 || ny < 0 || nx >= matrix_width || ny >= matrix_height ||
            grid[ny][nx].id != id) {
          perimeter++;
        }
      }

      if (perimeter > 0) {
        if (id >= perimeterCount.size()) {
          perimeterCount.resize(id + 1, 0);
        }
        perimeterCount[id] += perimeter;
      }
    }
  }

  return perimeterCount;
}

void printTiles(const vector<vector<Tile>>& tiles) {
  for (const auto& row : tiles) {
    for (const auto& tile : row) {
      cout << tile.plant;
    }
    cout << endl;
  }
}

void printIDs(const vector<vector<Tile>>& tiles) {
  for (const auto& row : tiles) {
    for (const auto& tile : row) {
      cout << tile.id;
    }
    cout << endl;
  }
}

int part1() {
  string filename = "input.txt";
  vector<vector<Tile>> tiles = readTilesFromFile(filename);
  populateIDs(tiles);
  vector<int> areas = countElementsById(tiles);
  vector<int> perimeters = calculatePerimeterById(tiles);

  int total = 0;
  for (int i = 0; i < areas.size(); i++) {
    total += areas[i] * perimeters[i];
  }

  return total;
}

int main() {
  int result = part1();
  cout << "Total price of fencing all regions: " << result << endl;
  return 0;
}
