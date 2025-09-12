#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::vector<int>> createMaze(const std::string& fileName) {
    std::vector<std::vector<int>> maze;
    std::ifstream file("maze0-1_input.txt");
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::vector<int> row;
            for (char c : line) {
                row.push_back(c - '0');
            }
            maze.push_back(row);
        }
        file.close();
    }
    else {
        std::cout << "Unable to open file" << std::endl;
    }
    return maze;
}

void printMaze(const std::vector<std::vector<int>>& maze) {
    for (const auto& row : maze) {
        for (int cell : row) {
            std::cout << cell;
        }
        std::cout << std::endl;
    }
}

std::pair<int, int> findStart(const std::vector<std::vector<int>>& maze) {
    for (int row = 0; row < maze.size(); ++row) {
        if (maze[row][0] == 0) {
            return std::make_pair(row, 0);
        }
    }

    for (int col = 0; col < maze[0].size(); ++col) {
        if (maze[0][col] == 0) {
            return std::make_pair(col, 0);
        }
    }

    std::cout << "No start position was located. RETURNING (-1, -1). " << std::endl;
    return std::make_pair(-1, -1);
}

std::pair<int, int> findTarget(const std::vector<std::vector<int>>& maze) {
    for (int row = 0; row < maze.size(); ++row) {
        if (maze[row][maze[0].size() - 1] == 0) {
            return std::make_pair(row, maze[0].size() - 1);
        }
    }

    for (int col = 0; col < maze[0].size(); ++col) {
        if (maze[maze.size() - 1][col] == 0) {
            return std::make_pair(maze.size() - 1, col);
        }
    }

    std::cout << "No tarrget was located. RETURNING (-1, -1). " << std::endl;
    return std::make_pair(-1, -1);
}

int main() {
    std::vector<std::vector<int>> maze = createMaze("maze0-1_input.txt");
    printMaze(maze);

    std::pair<int, int> start = findStart(maze);
    std ::cout << "Start position: " << start.first << ", " << start.second << std::endl;

    std::pair<int, int> target = findTarget(maze);
    std ::cout << "Target position: " << target.first << ", " << target.second << std::endl;
    return 0;
}