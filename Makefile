all: test

#Tests
test: tests/shape_tests.cpp
	g++ -std=c++11 src/shape.cpp src/shape.h tests/shape_tests.cpp tests/catch.hpp -o hbg_shape_test
ex: examples/example_main.cpp
	g++ -std=c++11 src/shape.cpp src/shape.h examples/example_main.cpp -o hbg_ex_check
	
#cleanup
clean:
	rm hbg_* *.ps
