#include "Person.h"
#include "FileGenerator.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <sstream>

std::vector<Person> readFromFile(const std::string& filename);
void processStudents(std::vector<Person>& students);

int main() {
    try {
        // Generate test files
        FileGenerator::generateStudentFile("students_10000.txt", 10000);
        FileGenerator::generateStudentFile("students_100000.txt", 100000);
        FileGenerator::generateStudentFile("students_1000000.txt", 1000000);
        FileGenerator::generateStudentFile("students_10000000.txt", 10000000);

        std::string filename = "students_10000.txt";
        auto students = readFromFile(filename);

        processStudents(students);

    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

std::vector<Person> readFromFile(const std::string& filename) {
    std::vector<Person> students;
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        Person p;
        std::istringstream ss(line);
        ss >> p.firstName >> p.lastName;

        // Read homework scores
        float hw;
        while (ss >> hw) {
            p.homeworkResults.push_back(hw);
        }

        // Check if there are any homework scores, and if so, pop the last one as the exam result
        if (!p.homeworkResults.empty()) {
            p.examResult = p.homeworkResults.back();
            p.homeworkResults.pop_back(); // Remove the last item from homework, which was the exam
        } else {
            throw std::runtime_error("Error reading exam result for " + p.firstName + " " + p.lastName);
        }

        // Calculate grades
        p.calculateFinalGrades();
        students.push_back(p);
    }
    file.close();
    return students;
}

void processStudents(std::vector<Person>& students) {
    std::vector<Person> passed, failed;

    for (const auto& student : students) {
        if (student.finalGradeAvg >= 5.0) {
            passed.push_back(student);
        } else {
            failed.push_back(student);
        }
    }

    // Sort both lists
    std::sort(passed.begin(), passed.end(), [](const Person& a, const Person& b) {
        return a.lastName < b.lastName;
    });

    std::sort(failed.begin(), failed.end(), [](const Person& a, const Person& b) {
        return a.lastName < b.lastName;
    });


    // Write to files
    std::ofstream passedFile("passed_students.txt");
    for (const auto& student : passed) {
        passedFile << student.firstName << " " << student.lastName << " " << student.finalGradeAvg << std::endl;
    }
    passedFile.close();

    std::ofstream failedFile("failed_students.txt");
    for (const auto& student : failed) {
        failedFile << student.firstName << " " << student.lastName << " " << student.finalGradeAvg << std::endl;
    }
    failedFile.close();
}
