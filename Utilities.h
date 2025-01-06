#ifndef UTILITIES_H
#define UTILITIES_H

#include <chrono>

class Utilities {
public:
    static double measureTime(void (*func)());
};

#endif 
