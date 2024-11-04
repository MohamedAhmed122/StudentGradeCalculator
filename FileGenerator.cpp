#include "FileGenerator.h"
#include <fstream>
#include <random>

void FileGenerator::generateStudentFile(const std::string& filename, int recordCount) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file for writing.");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 10);

    for (int i = 1; i <= recordCount; ++i) {
        file << "Name" << i << " Surname" << i;
        for (int j = 0; j < 5; ++j) {
            file << " " << dis(gen);
        }
        file << " " << dis(gen) << std::endl;
    }

    file.close();
}
