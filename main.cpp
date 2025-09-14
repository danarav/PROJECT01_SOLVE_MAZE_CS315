#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <set>

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

    std::cout << "No target was located. RETURNING (-1, -1). " << std::endl;
    return std::make_pair(-1, -1);
}

std::stack<std::pair<int, int>> findPath(const std::vector<std::vector<int>>& maze, const std::pair<int, int>& start, const std::pair<int, int>& target) {
    std::stack<std::pair<int, int>> path;
    std::vector<std::vector<bool>> explored(maze.size(), std::vector<bool>(maze[0].size(), false));

    path.push(start);
    explored[start.first][start.second] = true;

    const int moves_row[] = {0, 1, -1, 0};
    const int moves_col[] = {1, 0, 0, -1};

    while (!path.empty()) {
        auto current = path.top();
        bool unexplored = false;
        int row, col;

        for (int i = 0; i < 4; ++i) {
            row = current.first + moves_row[i];
            col = current.second + moves_col[i];

            if (row >= 0 && row < maze.size() && col >= 0 && col < maze[0].size()
                && !explored[row][col] && maze[row][col] == 0) {
                unexplored = true;
                break;
            }
        }
        if (!unexplored) {
            path.pop();
        }
        else {
            path.push({row, col});
            explored[row][col] = true;
            if (row == target.first && col == target.second) {
                break;
            }
        }
    }
    return path;
}

void printSolution(const std::vector<std::vector<int>>& maze, const std::stack<std::pair<int, int>>& path_stack) {

    if (path_stack.empty()) {
        std::cout << "No path was found" << std::endl;
        return;
    }

    std::set<std::pair<int, int>> path;
    std::stack<std::pair<int, int>> temp = path_stack;
    while (!temp.empty()) {
        path.insert(temp.top());
        temp.pop();
    }

    for (int row = 0; row < maze.size(); ++row) {
        for (int col = 0; col < maze[0].size(); ++col) {
            if (maze[row][col] == 1) {
                std::cout << '1';
            } else if (path.count({row, col})) {
                std::cout << "\033[34m#\033[0m";
            } else {
                std::cout << '0';
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    std::vector<std::vector<int>> maze = createMaze("maze0-1_input.txt");
    printMaze(maze);
    std::cout << std::endl;

    std::pair<int, int> start = findStart(maze);
    std ::cout << "Start position: " << start.first << ", " << start.second << std::endl;
    std::cout << std::endl;

    std::pair<int, int> target = findTarget(maze);
    std ::cout << "Target position: " << target.first << ", " << target.second << std::endl;
    std::cout << std::endl;

    std::stack<std::pair<int, int>> path = findPath(maze, start, target);
    printSolution(maze, path);
    std::cout << std::endl;

    return 0;
}