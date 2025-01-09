# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(StudentGrades VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
set(SOURCES
    main.cpp
    Person.cpp
    FileGenerator.cpp
    Utilities.cpp
)

# Add executable target
add_executable(student_grades ${SOURCES})
