all: tests

#Tests
temp: tests/temp_main.cpp
	g++ -std=c++11 src/shape.cpp src/shape.h tests/temp_main.cpp -o hb_temp_test