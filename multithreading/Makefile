CXX = g++
CXXFLAGS = -g -std=c++23 -Wall -Werror
LDFLAGS = -lpthread

TARGET = build/out
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf build

.PHONY: all run clean