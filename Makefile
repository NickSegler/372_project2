all: tests

#Tests
test: tests/shape_tests.cpp
	g++ -std=c++11 src/shape.cpp src/shape.h tests/shape_tests.cpp tests/catch.hpp -o hbg_shape_test
	
#cleanup
clean:
	rm hbg_* *.ps
