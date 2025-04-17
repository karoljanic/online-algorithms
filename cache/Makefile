CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -pedantic -O3

TARGET = experiment

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o $(TARGET)

clean:
	rm -f $(TARGET)
