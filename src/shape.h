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
#include <cmath>

#include <iostream>

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
    
    vector<pair<double,double>> verts;
    
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
    
    Polygon(double l, int n);
    
    Polygon(double w, double h, int n);
    
    void scale(double x, double y);
    
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
    Mod_shape(B_shape * bsp):bShapeP_(bsp)
    {
        bShapeP_=bsp;
    }
protected:
    B_shape * bShapeP_;
};

class S_shape : public Mod_shape{
public:
    S_shape(B_shape * bsp, double x, double y):Mod_shape(bsp),scaleX_(x),scaleY_(y)
    {
        scale();
    }
    
    void scale()
    {
        for(int i=0; i<bShapeP_->verts.size();++i)
        {
            bShapeP_->verts[i].first*=scaleX_;
            bShapeP_->verts[i].second*=scaleY_;
        }
    }
    
    virtual  string draw(const pair<double, double> & coord, bool to_file)
    {
        return bShapeP_->draw(coord, to_file);
    }
    
protected:
    double scaleX_;
    double scaleY_;
    
};

class R_shape : public Mod_shape{
public:
    R_shape(B_shape * bsp, double angle):Mod_shape(bsp), angle_(angle)
    {}
    
    virtual  string draw(const pair<double, double> & coord, bool to_file)
    {
        string outStr = bShapeP_->draw(coord, to_file);
        
        string add = std::to_string(angle_) + " rotate \n";
        
        int rLoc = outStr.find("translate \n") + 11; //12 is the size of the searched string
        
        outStr.insert(rLoc, add);
        
        return outStr;
    }

    
protected:
    double angle_;
    
};

// Triangle
// Derived from B_shape
// default is equalateral Triangle (same as Polygon(3))
//
//    **INVARIANTS**
//      height_ and width_ >= 0
//      b_box.y == height_
//      b_box.x == width
class E_triangle : public B_shape{
public:
    E_triangle(int x, int y);
    
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
// ex: __
//    |\ |
//    |_\|
//
class R_triangle : public B_shape{
public:
    R_triangle(int x, int y);
    
    // draw
    // takes point for center
    // bool decides if postscript code get written or returned
    string draw(const pair<double, double> & coord, bool to_file);
protected:
    bounding_box b_box;
    double height_;
    double width_;
};



class Circle : public B_shape{
public:
    Circle(double r):radius_(r)
    {}
    
    virtual string draw(const pair<double, double> & coord, bool to_file);
protected:
    double radius_;
};

#endif
