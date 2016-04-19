#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../src/shape.h"
//#include "../src/b_shape.h"
//#include "../src/mod_shape.h"
//#include "../src/stack_shape.h"

TEST_CASE("Testing Shape"){
    REQUIRE(1 + 1 == 2);

}// END TEST CASE SHAPE

TEST_CASE("Testing B_Shapes"){
    SECTION("Tesing Rectangle"){
        Rectangle test(300, 400);

        string output = "0 0\nnewpath \n50.000000 -100.000000 translate \nmoveto \n0 0 lineto \n300.000000 0.000000 lineto \n300.000000 400.000000 lineto \n0.000000 400.000000 lineto \nclosepath \nstroke";

        
        REQUIRE(test.draw(make_pair(200., 100.), false) == output);

    }

}// END TEST CASE B_SHAPES
