#include "Person.h"
#include "FileGenerator.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <chrono>
#include <sstream>
#include <type_traits>

template <typename Container>
Container readFromFile(const std::string& filename);

template <typename Container>
void processStudents(Container& students);

template <typename Container>
double measureOperationTime(const std::string& operationName, void(*operation)(Container&), Container& students);

void analyzePerformance();

int main() {
    try {
        // Generate test files
        FileGenerator::generateStudentFile("students_10000.txt", 10000);
        FileGenerator::generateStudentFile("students_100000.txt", 100000);
        FileGenerator::generateStudentFile("students_1000000.txt", 1000000);
        FileGenerator::generateStudentFile("students_10000000.txt", 10000000);

        analyzePerformance();

    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

template <typename Container>
Container readFromFile(const std::string& filename) {
    Container students;
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        Person p;
        std::istringstream ss(line);
        ss >> p.firstName >> p.lastName;

        float hw;
        while (ss >> hw) {
            p.homeworkResults.push_back(hw);
        }

        if (!p.homeworkResults.empty()) {
            p.examResult = p.homeworkResults.back();
            p.homeworkResults.pop_back();
        } else {
            throw std::runtime_error("Error reading exam result for " + p.firstName + " " + p.lastName);
        }

        p.calculateFinalGrades();
        students.push_back(p);
    }
    file.close();
    return students;
}

// function to process students, divide into passed/failed and sort
template <typename Container>
void processStudents(Container& students) {
    Container passed, failed;

    for (const auto& student : students) {
        if (student.finalGradeAvg >= 5.0) {
            passed.push_back(student);
        } else {
            failed.push_back(student);
        }
    }

    // Sorting
    if constexpr (std::is_same<Container, std::list<Person>>::value) {
        // Use list's own sort method for std::list
        passed.sort([](const Person& a, const Person& b) {
            return a.lastName < b.lastName;
        });
        failed.sort([](const Person& a, const Person& b) {
            return a.lastName < b.lastName;
        });
    } else {
        // Use std::sort for std::vector and std::deque
        std::sort(passed.begin(), passed.end(), [](const Person& a, const Person& b) {
            return a.lastName < b.lastName;
        });
        std::sort(failed.begin(), failed.end(), [](const Person& a, const Person& b) {
            return a.lastName < b.lastName;
        });
    }

    // Write sorted students to files
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

//  function to measure operation time
template <typename Container>
double measureOperationTime(const std::string& operationName, void(*operation)(Container&), Container& students) {
    auto start = std::chrono::high_resolution_clock::now();
    operation(students);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << operationName << " took " << duration.count() << " seconds" << std::endl;
    return duration.count();
}

// Function to analyze performance for vector, list, and deque
void analyzePerformance() {
    const std::string filename = "students_10000.txt"; // Change this for other file sizes as needed

    // Vector
    std::vector<Person> vectorStudents = readFromFile<std::vector<Person>>(filename);
    std::cout << "\nPerformance with std::vector:" << std::endl;
    measureOperationTime("Process students with vector", processStudents<std::vector<Person>>, vectorStudents);

    // List
    std::list<Person> listStudents = readFromFile<std::list<Person>>(filename);
    std::cout << "\nPerformance with std::list:" << std::endl;
    measureOperationTime("Process students with list", processStudents<std::list<Person>>, listStudents);

    // Deque
    std::deque<Person> dequeStudents = readFromFile<std::deque<Person>>(filename);
    std::cout << "\nPerformance with std::deque:" << std::endl;
    measureOperationTime("Process students with deque", processStudents<std::deque<Person>>, dequeStudents);
}
