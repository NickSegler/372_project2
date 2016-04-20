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
#include <vector>
using std::vector;
#include <memory> // for shared_ptr

#include <iostream>

// ***************************************************
// **** HELPER FUNCTIONS INCLUDED FOR TESTING USE ****
// ***************************************************
pair<double, double> polygonPoint(double l, int n, int k);
string psTo(double x, double y, int t);

// Shape
// Virtual class that all others are derived from
// Doesn't really do much
//
//    **INVARIANTS**
//      this should be never used for anything
class Shape{
public:
    virtual ~Shape() = default;
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
    
    // draw
    // takes point for center
    // bool decides if postscript code get written or returned
    virtual string draw(const pair<double, double> & coord, bool to_file);
    
    vector<pair<double,double>> verts; // this should probably be protected, but friends are hard.
    
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
    Rectangle(int x, int y);
    
protected:
    bounding_box b_box;
};

// Spacer
// Special type of Rectangle
// Does not draw lines around itself when it draws
// Everything else is the same as Rectangle
class Spacer : public Rectangle{
    public:
    Spacer(int x, int y):Rectangle(x, y)
    {}
    
protected:
    bounding_box b_box;
    double height_;
    double width_;
};

class Polygon : public B_shape{
public:
    Polygon();
    
    // 2 param ctor
    // l is side lenght
    // n is number of sides
    Polygon(double l, int n); 
    
    // 3 param ctor
    // w is width of bounding box
    // h is height of bounding box
    // n is number of sides
    Polygon(double w, double h, int n);
    
    void makeBBox();
    void makeVList();
    double sideL(double r, int sides);
    
    //DEBUG INFO
    void printPoints()
    {
        for(auto x:verts)
        {
            std::cout << x.first <<" " <<x.second <<std::endl;
        }
    }
    
protected:
    bounding_box b_box;
    double sideLength_;
    int numberSides_;
};

class Mod_shape : public Shape{
public:
    Mod_shape(B_shape * bsp);
protected:
    std::shared_ptr<B_shape> bShapeP_;
};

class S_shape : public Mod_shape{
public:
    S_shape(B_shape * bsp, double x, double y);
    
    void scale();
    
    virtual string draw(const pair<double, double> & coord, bool to_file);
    
protected:
    double scaleX_;
    double scaleY_;
    
};

class R_shape : public Mod_shape{
public:
    R_shape(B_shape * bsp, double angle);
    
    virtual string draw(const pair<double, double> & coord, bool to_file);

    
protected:
    double angle_;
    
};

// Triangle
// Derived from B_shape
// Equalateral Triangle (same as Polygon(3))
//
//    **INVARIANTS**
//      height_ and width_ >= 0
//      b_box.y == height_
//      b_box.x == width
class E_triangle : public B_shape{
public:
    E_triangle(double w, double h);
    virtual string draw(const pair<double, double> & coord, bool to_file);
protected:
    Polygon me;
};

// R_triangle
// A right triangle derived from B_shape
// assumes bottom left is 90 degree angle
// ex: __
//    |\ |
//    |_\|
//
class R_triangle : public B_shape{
public:
    // two param ctor
    //     w is width (bottom side)
    //     h is height (right side)
    R_triangle(double w, double h);
    
    // draw
    // takes point for center
    // bool decides if postscript code get written or returned
protected:
    bounding_box b_box;
};



class Circle : public B_shape{
public:
    Circle(double r):radius_(r)
    {
        verts.push_back(make_pair(0,0));
        verts.push_back(make_pair(radius_, radius_));
    }
    
    virtual string draw(const pair<double, double> & coord, bool to_file);
protected:
    double radius_;
};

// ****************
// **** STACKS ****
// ****************
class Stack : public Shape {

public:

    virtual string draw(const pair<double, double> & coord, bool to_file) = 0;

    void addShape(B_shape * bsp)
    {  theStack.push_back(bsp);    }

protected:
    vector <B_shape*> theStack;
};

class H_stack : public Stack {

public:

    string draw(const pair<double, double> & coord, bool to_file);

protected:
    double center;
};

class V_stack : public Stack {

public:

    string draw(const pair<double, double> & coord, bool to_file);

    pair<double,double> findGreatest(B_shape * bsp);

    double findHeight(B_shape *bsp);

    double findWidth(B_shape *bsp);

protected:
    double center;
};

// ****************
// **** STACKS ****
// ****************

#endif
