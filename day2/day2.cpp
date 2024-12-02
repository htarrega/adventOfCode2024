#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> readFile(const string &path) {
  vector<string> lines;
  ifstream file(path);

  if (!file.is_open()) {
    cerr << "Error: Could not open file: " << path << endl;
    return lines;
  }

  string line;
  while (getline(file, line)) {
    lines.push_back(line);
  }
  file.close();

  return lines;
}

int checkReport(const string &line) {
  std::istringstream stream(line);
  std::vector<int> numbers;
  int num;

  while (stream >> num) {
    numbers.push_back(num);
  }

  if (numbers.empty() || numbers.size() == 1) {
    return 0;
  }

  int prev_num = numbers[0];
  bool increasing = false, decreasing = false;

  for (size_t i = 1; i < numbers.size(); i++) {
    int diff = abs(numbers[i] - prev_num);

    if (diff < 1 || diff > 3) {
      return 0;
    }

    if (numbers[i] > prev_num) {
      increasing = true;
      if (decreasing) return 0;
    } else if (numbers[i] < prev_num) {
      decreasing = true;
      if (increasing) return 0;
    }

    prev_num = numbers[i];
  }

  return 1;
}
int isValidReport(const std::vector<int> &numbers) {
  int prev_num = numbers[0];
  bool increasing = false, decreasing = false;

  for (size_t i = 1; i < numbers.size(); i++) {
    int diff = abs(numbers[i] - prev_num);
    if (diff < 1 || diff > 3) return 0;

    if (numbers[i] > prev_num) {
      if (decreasing) return 0;
      increasing = true;
    } else if (numbers[i] < prev_num) {
      if (increasing) return 0;
      decreasing = true;
    }

    prev_num = numbers[i];
  }
  return 1;
}

int checkReport2(const string &line) {
  std::istringstream stream(line);
  std::vector<int> numbers;
  int num;

  while (stream >> num) {
    numbers.push_back(num);
  }

  if (numbers.empty() || numbers.size() == 1) {
    return 0;
  }

  if (isValidReport(numbers)) return 1;

  for (size_t i = 0; i < numbers.size(); i++) {
    std::vector<int> modified = numbers;
    modified.erase(modified.begin() + i);
    if (isValidReport(modified)) return 1;
  }

  return 0;
}

string part1(const vector<string> &lines) {
  int total = 0;

  for (const string &line : lines) {
    total += checkReport(line);
  }

  return to_string(total);
}

string part2(const vector<string> &lines) {
  int total = 0;

  for (const string &line : lines) {
    total += checkReport2(line);
  }

  return to_string(total);
}

int main() {
  string path = "input.txt";
  vector<string> lines = readFile(path);

  if (lines.empty()) {
    cout << "No data to process." << endl;
    return 1;
  }

  cout << "Number of correct reports (Part 1): " << part1(lines) << endl;
  cout << "Number of correct reports (Part 2): " << part2(lines) << endl;

  return 0;
}
