#include "Utilities.h"
#include <iostream>

double Utilities::measureTime(void (*func)()) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}
