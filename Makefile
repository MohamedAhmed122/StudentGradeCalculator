# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Source files
SRCS = main.cpp Person.cpp FileGenerator.cpp Utilities.cpp
OBJS = $(SRCS:.cpp=.o)

# Output binary
TARGET = student_grades

# Build rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
