# Student Grades Project

## Overview
The **Student Grades Project** is a C++ application that processes a large dataset of student records. It categorizes students into two groups (`passed` and `failed`) based on their final grade and measures the performance of different container types (`std::vector`, `std::list`, and `std::deque`) using two strategies:

1. **Strategy 1**: Splits the dataset into two new containers (`passed` and `failed`), leaving the original dataset untouched.
2. **Strategy 2**: Modifies the original dataset in place, removing failed students and resizing the container.

The program uses Makefile or CMake for building and supports performance analysis for the different strategies and containers.

---

## Features
- Reads student data from input files.
- Processes students into `passed` and `failed` categories.
- Measures execution time for different container types and strategies.
- Supports two build systems: Makefile and CMake.
- Debugging enabled using GDB or LLDB.

---

## File Structure
```
|-- src
    |-- main.cpp
    |-- Person.cpp
    |-- FileGenerator.cpp
    |-- Utilities.cpp
|-- include
    |-- Person.h
    |-- FileGenerator.h
    |-- Utilities.h
|-- build/        # Build directory (created by CMake or manually)
|-- Makefile      # Makefile for building the project
|-- CMakeLists.txt
|-- README.md     # Project documentation
```

---

## Usage

### 1. Generate Student Files
The program generates random test files with varying sizes:
- `students_10000.txt`
- `students_100000.txt`
- `students_1000000.txt`
- `students_10000000.txt`

### 2. Build the Project

#### **Using Makefile**
1. Open a terminal and navigate to the project directory.
2. Run:
   ```bash
   make
   ```
3. Clean build files (optional):
   ```bash
   make clean
   ```

#### **Using CMake**
1. Create a `build` directory and navigate into it:
   ```bash
   mkdir build && cd build
   ```
2. Configure the project:
   ```bash
   cmake ..
   ```
3. Build the project:
   ```bash
   cmake --build .
   ```
4. Clean the build (optional):
   ```bash
   rm -rf build && mkdir build && cd build && cmake ..
   ```

### 3. Run the Program
After building, run the program from the terminal:
```bash
./student_grades
```

### 4. Debug the Program (Optional)

#### Using GDB (Makefile):
```bash
gdb ./student_grades
```

#### Using LLDB (CMake):
```bash
lldb ./build/student_grades
```

---

## Performance Analysis
The program measures execution time for:
1. Strategy 1 (Two new containers).
2. Strategy 2 (In-place modification).

It outputs the time taken for each strategy and container type (`std::vector`, `std::list`, `std::deque`). Use these results to choose the most efficient approach for your use case.

---

## Results

The final grade calculation for students is based on the following formula:

$$
Final\ Grade = \frac{0.5 \times Average(HW) + 0.5 \times Median(HW) + Exam\ Score}{2}
$$

- **Strategy 1**: Faster for smaller datasets but uses more memory.
- **Strategy 2**: More memory-efficient but slower due to frequent deletions.

### **Container Performance**:
- `std::vector`: Best overall performance for most operations.
- `std::list`: Suitable for frequent insertions and deletions.
- `std::deque`: A hybrid between `vector` and `list`.

---

## Contributions
Feel free to contribute by submitting a pull request or reporting issues.

---

## License
This project is licensed under the MIT License.

