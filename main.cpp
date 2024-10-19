#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Person {
private:
    std::string firstName;
    std::string lastName;
    std::vector<float> homeworkResults;
    std::vector<float> examResults;
    float finalGrade;

public:

    Person() : finalGrade(0.0f) {}

    void inputData() {
        std::cout << "Enter first name: ";
        std::cin >> firstName;
        std::cout << "Enter last name: ";
        std::cin >> lastName;

        int homeworkCount, examCount;
        std::cout << "How many homework results? ";
        std::cin >> homeworkCount;
        homeworkResults.resize(homeworkCount);
        std::cout << "Enter homework results: ";
        for (int i = 0; i < homeworkCount; ++i) {
            std::cin >> homeworkResults[i];
        }

        std::cout << "How many exam results? ";
        std::cin >> examCount;
        examResults.resize(examCount);
        std::cout << "Enter exam results: ";
        for (int i = 0; i < examCount; ++i) {
            std::cin >> examResults[i];
        }
    }

    void calculateFinalGrade(bool useMedian) {
        if (useMedian) {
            finalGrade = (calculateMedian(homeworkResults) + calculateMedian(examResults)) / 2;
        } else {
            finalGrade = (calculateAverage(homeworkResults) + calculateAverage(examResults)) / 2;
        }
    }

    void printData() const {
        std::cout << firstName << " " << lastName << " Final Grade: " << finalGrade << std::endl;
    }

private:
    float calculateMedian(std::vector<float> data) {
        std::sort(data.begin(), data.end());
        if (data.size() % 2 == 0) {
            return (data[data.size() / 2 - 1] + data[data.size() / 2]) / 2;
        } else {
            return data[data.size() / 2];
        }
    }

    float calculateAverage(const std::vector<float>& data) {
        float sum = 0;
        for (float val : data) {
            sum += val;
        }
        return data.empty() ? 0 : sum / data.size();
    }
};

int main() {
    int numStudents;
    std::cout << "Enter the number of students: ";
    std::cin >> numStudents;

    std::vector<Person> students(numStudents);

    for (int i = 0; i < numStudents; ++i) {
        students[i].inputData();

        bool useMedian;
        std::cout << "Do you want to calculate the final grade using the median? (1 for Yes, 0 for No): ";
        std::cin >> useMedian;

        students[i].calculateFinalGrade(useMedian);
    }

    std::cout << "\nName       Surname       Final_Point(Aver.)" << std::endl;
    std::cout << "-------------------------------------------" << std::endl;

    for (int i = 0; i < numStudents; ++i) {
        students[i].printData();
    }

    return 0;
}
