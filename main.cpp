#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

class Person {
public:
    std::string firstName;
    std::string lastName;
    std::vector<float> homeworkResults;
    float examResult;
    float finalGradeAvg;
    float finalGradeMed;

    Person() : finalGradeAvg(0.0f), finalGradeMed(0.0f), examResult(0.0f) {}

    void calculateFinalGrades() {
        finalGradeAvg = (calculateAverage(homeworkResults) + examResult) / 2;
        finalGradeMed = (calculateMedian(homeworkResults) + examResult) / 2;
    }

    float calculateAverage(const std::vector<float>& scores) {
        float sum = 0;
        for (float score : scores) {
            sum += score;
        }
        return scores.empty() ? 0 : sum / scores.size();
    }

    float calculateMedian(std::vector<float> scores) {
        std::sort(scores.begin(), scores.end());
        if (scores.size() % 2 == 0) {
            return (scores[scores.size() / 2 - 1] + scores[scores.size() / 2]) / 2;
        } else {
            return scores[scores.size() / 2];
        }
    }


    void print() const {
        std::cout << std::setw(10) << firstName << " "
                  << std::setw(10) << lastName << " "
                  << std::setw(10) << std::fixed << std::setprecision(2) << finalGradeAvg << " | "
                  << std::setw(10) << finalGradeMed << std::endl;
    }
};

std::vector<Person> readFromFile(const std::string& filename) {
    std::vector<Person> students;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return students;  
    }

    std::string line;
    std::getline(file, line); 
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Person p;

        std::cout << "Reading line: " << line << std::endl;

        ss >> p.firstName >> p.lastName;

        std::cout << "First name: " << p.firstName << ", Last name: " << p.lastName << std::endl;

        float hw;
        while (ss >> hw) {
            p.homeworkResults.push_back(hw);
        }

        if (!(ss >> p.examResult)) {
            std::cerr << "Error: Could not read exam result for " << p.firstName << " " << p.lastName << std::endl;
        }

        p.calculateFinalGrades();
        students.push_back(p);
    }
    file.close();
    return students;
}

bool compareByName(const Person& a, const Person& b) {
    return a.lastName < b.lastName;
}

int main() {
    srand(time(0));  

    std::string filename = "students.txt";
    std::vector<Person> students = readFromFile(filename);

    if (students.empty()) {
        std::cerr << "No students found. Exiting..." << std::endl;
        return 1;
    }

    std::sort(students.begin(), students.end(), compareByName);

    std::cout << "Name       Surname        Final (Avg.) | Final (Med.)" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    for (const Person& student : students) {
        student.print();
    }

    return 0;
}
