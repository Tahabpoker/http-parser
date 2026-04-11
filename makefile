CXX = g++
CXXFLAGS = -O2 -std=c++20 -Iinclude -Wall -Wpedantic

SRC = src/main.cpp src/parser/http_parser.cpp
TEST_SRC = tests/test_parser.cpp src/parser/http_parser.cpp

all:
	if not exist build mkdir build
	$(CXX) $(CXXFLAGS) $(SRC) -o build/app.exe

test:
	if not exist build mkdir build
	$(CXX) $(CXXFLAGS) $(TEST_SRC) -o build/test.exe
	build\test.exe

clean:
	if exist build rmdir /s /q build