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
void processStudentsStrategy1(Container& students);

template <typename Container>
void processStudentsStrategy2(Container& students);

template <typename Container>
double measureOperationTime(const std::string& operationName, void(*operation)(Container&), Container& students);

template <typename Container>
double measureOperationTime(const std::string& operationName, void(*operation)(Container&), Container& students) {
    auto start = std::chrono::high_resolution_clock::now();
    operation(students);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << operationName << " took " << duration.count() << " seconds" << std::endl;
    return duration.count();
}

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

// Strategy 1: Two new containers for passed and failed students
template <typename Container>
void processStudentsStrategy1(Container& students) {
    Container passed, failed;

    std::partition_copy(
        students.begin(), students.end(),
        std::back_inserter(passed), std::back_inserter(failed),
        [](const Person& student) { return student.finalGradeAvg >= 5.0; });

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

// Strategy 2: In-place modification of students container
template <typename Container>
void processStudentsStrategy2(Container& students) {
    auto partitionPoint = std::partition(
        students.begin(), students.end(),
        [](const Person& student) { return student.finalGradeAvg >= 5.0; });

    Container failed(partitionPoint, students.end());
    students.erase(partitionPoint, students.end());

    std::ofstream passedFile("passed_students.txt");
    for (const auto& student : students) {
        passedFile << student.firstName << " " << student.lastName << " " << student.finalGradeAvg << std::endl;
    }
    passedFile.close();

    std::ofstream failedFile("failed_students.txt");
    for (const auto& student : failed) {
        failedFile << student.firstName << " " << student.lastName << " " << student.finalGradeAvg << std::endl;
    }
    failedFile.close();
}

// Measure performance of each strategy
template <typename Container>
void measureStrategies(const std::string& filename) {
    Container students = readFromFile<Container>(filename);

    std::cout << "\nMeasuring Strategy 1 (Two New Containers) for " << typeid(Container).name() << ":" << std::endl;
    measureOperationTime("Strategy 1", processStudentsStrategy1<Container>, students);

    students = readFromFile<Container>(filename);

    std::cout << "\nMeasuring Strategy 2 (In-Place Modification) for " << typeid(Container).name() << ":" << std::endl;
    measureOperationTime("Strategy 2", processStudentsStrategy2<Container>, students);
}

void analyzePerformance() {
    const std::string filename = "students_10000.txt";

    // Vector
    std::cout << "\nPerformance with std::vector:" << std::endl;
    measureStrategies<std::vector<Person>>(filename);

    // List
    std::cout << "\nPerformance with std::list:" << std::endl;
    measureStrategies<std::list<Person>>(filename);

    // Deque
    std::cout << "\nPerformance with std::deque:" << std::endl;
    measureStrategies<std::deque<Person>>(filename);
}
