// shape.h
// Header file containing declarations for our shape class hierarchy
// for cs372
// Spring 2016
// Heart Break Gorillas

#include <string>
using std::string;

// Shape
// Virtual class that all others are derived from
// Doesn't really do much
//
//    **INVARIANTS**
//      this should be never used for anything
class Shape{
public:
    ~Shape()
    {}
    virtual  string draw(double coord, bool to_file) = 0;
};

// B_shape
// Virtual class derived from Shape
// Includes bounding box (b_box) for all following
// which are shapes eg. Rectangle, Triangle
// Doesn't actually do anything itself
//
//    **INVARIANTS**
//      this should be never used for anything
class B_shape : public Shape{
public:
    virtual string draw(double coord, bool to_file) = 0;
protected:
    struct bounding_box{
        double x;
        double y;
        double center;
    };
};

// Rectangle
// Derived from B_shape
// Is a rectangle! Has a height and a width
// knows how to draw itself
// draw is still virtual for Spacer, a specialized version of a Rectangle
//
//    **INVARIANTS**
//      height_ and width_ >= 0
//      b_box.y == height_
//      b_box.x == width
class Rectangle : public B_shape{
public:
    Rectangle(int y, int x):height_(y), width_(x){
        b_box.x = x;
        b_box.y = y;
        b_box.center = (x/2) + (y/2);
    }
    
    // draw
    // takes point for center
    // bool decides if postscript code get written or returned
    virtual string draw(double coord, bool to_file);
protected:
    struct bounding_box{
        double x;
        double y;
        double center;
    };
    bounding_box b_box;
    double height_;
    double width_;
};

// Spacer
// Special type of Rectangle
// Does not draw lines around itself when it draws
// Everything else is the same as Rectangle
class Spacer : public Rectangle{
    public:
    Spacer(int y, int x):Rectangle(y, x)
    {}
    string draw(double coord, bool to_file);
protected:
    struct bounding_box{
        double x;
        double y;
        double center;
    };
    bounding_box b_box;
    double height_;
    double width_;
};