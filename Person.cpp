#include "Person.h"

Person::Person() : finalGradeAvg(0.0f), finalGradeMed(0.0f), examResult(0.0f) {}

void Person::calculateFinalGrades() {
    finalGradeAvg = (calculateAverage(homeworkResults) + examResult) / 2;
    finalGradeMed = (calculateMedian(homeworkResults) + examResult) / 2;
}

float Person::calculateAverage(const std::vector<float>& scores) const {
    float sum = 0;
    for (float score : scores) {
        sum += score;
    }
    return scores.empty() ? 0 : sum / scores.size();
}

float Person::calculateMedian(std::vector<float> scores) const {
    std::sort(scores.begin(), scores.end());
    if (scores.size() % 2 == 0) {
        return (scores[scores.size() / 2 - 1] + scores[scores.size() / 2]) / 2;
    } else {
        return scores[scores.size() / 2];
    }
}

void Person::print() const {
    std::cout << std::setw(10) << firstName << " "
              << std::setw(10) << lastName << " "
              << std::setw(10) << std::fixed << std::setprecision(2) << finalGradeAvg << " | "
              << std::setw(10) << finalGradeMed << std::endl;
}
