#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

int part1() {
  ifstream file("input.txt");
  if (!file) {
    cerr << "Error opening file!" << endl;
    return {};
  }
  vector<tuple<int, int, int, int>> data;
  string line;
  regex pattern(R"(p=(-?\d+),(-?\d+) v=(-?\d+),(-?\d+))");
  smatch matches;
  while (getline(file, line)) {
    if (regex_search(line, matches, pattern)) {
      int px = stoi(matches[1]);
      int py = stoi(matches[2]);
      int vx = stoi(matches[3]);
      int vy = stoi(matches[4]);
      data.push_back(make_tuple(px, py, vx, vy));
    }
  }
  file.close();
  int wide = 101;
  int tall = 103;
  for (int i = 0; i < 100; ++i) {
    for (auto &robot : data) {
      int px, py, vx, vy;
      tie(px, py, vx, vy) = robot;
      int newx = (px + vx + wide) % wide;
      int newy = (py + vy + tall) % tall;
      robot = make_tuple(newx, newy, vx, vy);
    }
  }
  for (const auto &entry : data) {
    int px, py, vx, vy;
    tie(px, py, vx, vy) = entry;
  }
  vector<int> robotPerQuadrant = {0, 0, 0, 0};
  for (const auto &entry : data) {
    int px, py, vx, vy;
    tie(px, py, vx, vy) = entry;
    int middle_x = wide / 2;
    int middle_y = tall / 2;
    int quadrant = 0;
    if (px != middle_x && py != middle_y) {
      if (px > middle_x && py < middle_y) {
        quadrant = 1;
      } else if (px < middle_x && py < middle_y) {
        quadrant = 2;
      } else if (px < middle_x && py > middle_y) {
        quadrant = 3;
      } else if (px > middle_x && py > middle_y) {
        quadrant = 4;
      }
    }
    if (quadrant > 0) {
      robotPerQuadrant[quadrant - 1]++;
    }
  }
  int safetyFactor = 1;
  for (int i = 0; i < robotPerQuadrant.size(); ++i) {
    safetyFactor *= robotPerQuadrant[i];
  }
  return safetyFactor;
}

void printGrid(const vector<tuple<int, int, int, int>> &data, int wide,
               int tall) {
  vector<vector<bool>> grid(tall, vector<bool>(wide, false));
  for (const auto &entry : data) {
    int px, py, vx, vy;
    tie(px, py, vx, vy) = entry;
    grid[py][px] = true;
  }
  for (const auto &row : grid) {
    for (bool hasRobot : row) {
      cout << (hasRobot ? "1" : "·");
    }
    cout << endl;
  }
  cout << endl;
}

void part2() {
  ifstream file("input.txt");
  if (!file) {
    cerr << "Error opening file!" << endl;
    return;
  }

  vector<tuple<int, int, int, int>> data;
  string line;
  regex pattern(R"(p=(-?\d+),(-?\d+) v=(-?\d+),(-?\d+))");
  smatch matches;

  while (getline(file, line)) {
    if (regex_search(line, matches, pattern)) {
      int px = stoi(matches[1]);
      int py = stoi(matches[2]);
      int vx = stoi(matches[3]);
      int vy = stoi(matches[4]);
      data.push_back(make_tuple(px, py, vx, vy));
    }
  }
  file.close();

  int wide = 101;
  int tall = 103;
  int cycle = 0;

  while (true) {
    vector<int> rowCounts(tall, 0);
    vector<int> colCounts(wide, 0);

    for (const auto &entry : data) {
      int px, py, vx, vy;
      tie(px, py, vx, vy) = entry;
      rowCounts[py]++;
      colCounts[px]++;
    }

    int rowsWithMany = 0;
    int colsWithMany = 0;

    for (int count : rowCounts) {
      if (count >= 15)
        rowsWithMany++;
    }
    for (int count : colCounts) {
      if (count >= 15)
        colsWithMany++;
    }

    if (rowsWithMany >= 2 && colsWithMany >= 2) {
      cout << "Cycle " << cycle << ":\n";
      printGrid(data, wide, tall);

      cout << "Press Enter to continue (or 'q' to quit): ";
      string input;
      getline(cin, input);

      if (input == "q") {
        break;
      }
    }

    for (auto &robot : data) {
      int px, py, vx, vy;
      tie(px, py, vx, vy) = robot;
      int newx = (px + vx + wide) % wide;
      int newy = (py + vy + tall) % tall;
      robot = make_tuple(newx, newy, vx, vy);
    }

    cycle++;
  }
}

int main() {
  int safetyFactor = part1();
  cout << "\nSolution part1: " << safetyFactor << endl;
  cout << "\nSolution part2: " << endl;
  part2();
  return 0;
}