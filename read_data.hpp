#include <iostream>
#include <fstream>
#include <vector>

std::vector<double> read_data(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<double> data;
    double value;
    while (file >> value) {
        data.push_back(value);
    }
    return data;
}