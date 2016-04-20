#include "../src/shape.h"
#include <iostream> // for cout and endl

int main(){
    // **********************
    // **** BASIC SHAPES ****
    // **********************

    // ******************
    // **** POLYGONS ****
    // ******************
    
    // 2 Parameter Constructor
    // takes side lenght and number of sides
    // Here's how to make a pentagon with side lenght of 100
    Polygon pent(100, 5);

    // 3 Parameter Constructor
    // we can use this to make the biggest shape we can in the given space
    Polygon pent2(100, 100, 5);
    // This makes a pentagon in a box 100 x 100, instead of having side lenghts of 100
    
    // We can print this as a string, or to a file.
    // If you want to print more than one shape to a file, you need to make your own string
    // Here's how to get a string of postscript code and send it to cout
    std::cout << pent.draw(make_pair(200, 482), false) << std::endl;
    // draw takes two parameters,
    //     a pair of doubles, and a bool
    //     the pair of doubles is where on the screen postscript will print it.
    //     the bool decides if it goes to a file or not.
    pent.draw(make_pair(200, 482), true);
    // there we tell it true, so it writes to yourprogram.ps in the running directory
    // due to limitations in the code, if we call this again it will overwrite the current file
    // we can get around this by telling it false and appending the returned code to a string that we write later.
   
    // *******************
    // **** RECTANGLE ****
    // *******************
    
    // 2 Parameter Constructor
    // takes a height and a width
    Rectangle box(100, 200);
    // This makes a 100 x 200 rectangle
    
    // We can draw it the same way as a polygon
    std::cout << box.draw(make_pair(400, 823), false) << std::endl;
    // The bool works the same as above


    // *******************
    // **** TRIANGLES ****
    // *******************

    // There are 2 types of triangles available in this library
    // The first is an Equalateral triangle, called E_triangle
    
    // 2 Parameter Constructor
    // takes a height and a width
    // builds a triangle with side lenght equal to the width (bottom)
    E_triangle eqatri(100, 200);

    // You might be wondering why you would need to do this instead of a polygon with 3 sides
    // using this makes it clear that you're using a triangle, but to be honest there's not much reason not to
    // this is actually just a wrapper for a polygon with the appropriate side length

    // But we can draw it the same way as everything else
    std::cout << eqatri.draw(make_pair(200, 484), false) << std::endl;

    // The second type is a right triangle, called R_triangle
    // It isn't a wrapper, and is pretty cool

    // 2 Parameter Constructor
    // takes a height and a width
    // assumes the right angle is in the bottom left
    // and the height and width are equal to the lenght of the non-hippotenuse sides
    // ex:
    //     ______
    // h  |\     |
    // e  | \    |
    // i  |  \   |
    // g  |   \  |
    // h  |    \ |
    // t  |_____\|
    //     width
    R_triangle ritri(300, 42.21);

    // And it also prints exactly the same
    ritri.draw(make_pair(300, 200), true);

    // ****************
    // **** CIRCLE ****
    // ****************
    
    // 1 Parameter Constructor
    Circle circe(100);
    // This makes a cirlce with a radius of 100
    // We can get the postscript code the same way as before
    
    std::cout << circe.draw(make_pair(100,232), false) << std::endl;
    
    // *************************
    // **** MODIFIED SHAPES ****
    // *************************
    
    // Rotating shapes
    // To rotate a shape, we first need a shape to rotate
    // for this example, we'll use pent from before
    
    // 2 Parameter Constructor
     
    R_shape rotated_pent(&pent, 73.3);
    
    // The first parameter is the address B_shape we want to rotate
    // The second parameter is the angle of rotation
    // it rotates around the center of the bounding box
    
    // We can draw it the same way as everything else
    std::cout << rotated_pent.draw(make_pair(123, 412), false) << std::endl;
    rotated_pent.draw(make_pair(123, 412), true);
    
    // Scaling shapes
    // We follow a similar procedure as rotating a shape to scale a shape
    
    // 3 Parameter Constructor
    // As before, the first parameter is the adress of the shape we want to scale
    // the following two are the scale for X and Y respectively
    S_shape scaled_pent(&pent, 1, 3);
    
    // This makes a scaled shape that is 1 * the previous width of pent
    // and 3 * the previous height
    
    // And we draw this one the same was as well
    std::cout << scaled_pent.draw(make_pair(123, 412), false) << std::endl;
    
    // ****************
    // **** STACKS ****
    // ****************
    
    return 0; // return 0 because done.
}
