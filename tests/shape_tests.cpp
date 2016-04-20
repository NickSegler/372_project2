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
        
        string output =  "% !\n0 0\nnewpath\ngsave\n200.000000 100.000000 translate\n0.000000 0.000000 moveto\n0.000000 400.000000 lineto\n300.000000 400.000000 lineto\n300.000000 0.000000 lineto\nclosepath\nstroke\ngrestore\n";
        REQUIRE(test.draw(make_pair(200., 100.), false) == output);
    }
    SECTION("Testing Circle"){
        Circle bob(10);
        string output = "% !\n0 0\nnewpath\ngsave\n100.000000 100.000000 translate\n0 0 10.000000 0 360 arc\nclosepath \nstroke\ngrestore\n";
    
        REQUIRE(bob.draw(make_pair(100,100), false) == output);
    }
    SECTION("Testing Triangles"){
        SECTION("Testing E_triangle (same as Polygon(3))"){
            E_triangle test(8, 3);
            Polygon check(5, 3);

            pair<double, double> point = make_pair(30, 40);

            REQUIRE(test.draw(point, false) == check.draw(point, false));
        }
    }
    SECTION("Testing Polygon"){
        vector<Polygon> tests;
        for(int i = 0; i < 13; ++i)  
            tests.push_back(Polygon(100, i));

        for(int i = 0; i < 13; ++i){
            string output = "% !\n0 0\nnewpath\ngsave\n200.000000 300.000000 translate\n";

            for(int j = 0; j < i; ++j){
                auto temp = polygonPoint(100, i, j);
                output += psTo(temp.first, temp.second, j);
            }

            output += "closepath\nstroke\ngrestore\n";
            REQUIRE(tests[i].draw(make_pair(200,300),false) == output);
        }
    }

}// END TEST CASE B_SHAPES
