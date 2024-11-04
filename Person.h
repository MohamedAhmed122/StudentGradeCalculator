#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

class Person {
public:
    std::string firstName;
    std::string lastName;
    std::vector<float> homeworkResults;
    float examResult;
    float finalGradeAvg;
    float finalGradeMed;

    Person();

    void calculateFinalGrades();
    float calculateAverage(const std::vector<float>& scores) const;
    float calculateMedian(std::vector<float> scores) const;
    void print() const;
};

#endif 
