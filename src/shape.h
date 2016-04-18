// shape.h
// Header file containing declarations for our shape class hierarchy
// for cs372
// Spring 2016
// Heart Break Gorillas

#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

#include <string>
using std::string;
#include <utility>
using std::pair;
using std::make_pair;

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
    virtual  string draw(const pair<double, double> & coord, bool to_file) = 0;
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
    virtual string draw(const pair<double, double> & coord, bool to_file) = 0;
protected:
    struct bounding_box{
        pair<double, double> bright;
        pair<double, double> tright;
        pair<double, double> tleft;
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
    Rectangle(int x, int y):height_(y), width_(x){
        b_box.bright = make_pair(x, 0);
        b_box.tright = make_pair(x, y);
        b_box.tleft  = make_pair(0, y);
    }
    
    // draw
    // takes point for center
    // bool decides if postscript code get written or returned
    virtual string draw(const pair<double, double> & coord, bool to_file);
protected:
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
    Spacer(int x, int y):Rectangle(x, y)
    {}
    string draw(const pair<double, double> & coord, bool to_file);
protected:
    bounding_box b_box;
    double height_;
    double width_;
};

// Triangle
// Derived from B_shape
// default is equalateral Triangle (same as Polygon(3))
//
//    **INVARIANTS**
//      height_ and width_ >= 0
//      b_box.y == height_
//      b_box.x == width
class Triangle : public B_shape{
public:
    Triangle(int x, int y):height_(y), width_(x){
        b_box.bright = make_pair(x, 0);
        b_box.tright = make_pair(x, y);
        b_box.tleft  = make_pair(0, y);
    }
    
    // draw
    // takes point for center
    // bool decides if postscript code get written or returned
    virtual string draw(const pair<double, double> & coord, bool to_file);
protected:
    bounding_box b_box;
    double height_;
    double width_;
};

// R_triangle
// A right triangle derived from Triangle
// assumes bottom left is 90 degree angle
// ie: __
//    |\ |
//    |_\|
//
class R_triangle : public Triangle{
public:
    R_triangle(int x, int y):Triangle(x,y)
    {}
    
    // draw
    // takes point for center
    // bool decides if postscript code get written or returned
    string draw(const pair<double, double> & coord, bool to_file);
protected:
    bounding_box b_box;
    double height_;
    double width_;
};

#endif