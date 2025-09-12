#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {

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

    for (const auto& row : maze) {
        for (int cell : row) {
            std::cout << cell;
        }
        std::cout << std::endl;
    }


    return 0;
}