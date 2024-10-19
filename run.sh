#!/bin/bash


# to run the project simply run  ./run.sh in the terminal:) 

# to execute the script you may need to run:
# chmod +x run.sh
# then run the project by ./run.sh

echo "Compiling the C++ program..."
g++ main.cpp -o student_grades

if [ $? -eq 0 ]; then
    echo "Compilation successful. Running the program..."
    ./student_grades
else
    echo "Compilation failed."
fi