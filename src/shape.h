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
    virtual ~Shape()
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
    
    // draw
    // takes point for center
    // bool decides if postscript code get written or returned
    virtual string draw(const pair<double, double> & coord, bool to_file);
    
    vector<pair<double,double>> verts;
    
protected:
    
    struct bounding_box{
        pair<double, double> bleft = make_pair(0,0);
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
        
        verts.push_back(make_pair(0,0));
        verts.push_back(make_pair(0,y));
        verts.push_back(make_pair(x,y));
        verts.push_back(make_pair(x,0));
    }
    
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
    
protected:
    bounding_box b_box;
    double height_;
    double width_;
};

class Polygon : public B_shape{
public:
    Polygon():sideLength_(10),numberSides_(4)
    {
        makeBBox();
        makeVList();
    }
    
    Polygon(double l, int n):sideLength_(l),numberSides_(n)
    {
        makeBBox();
        makeVList();
    }
    
    Polygon(double w, double h, int n):numberSides_(n)
    {
        if(n%2==0)
        {
            sideLength_ = sideL(h,numberSides_);
        }else{
            sideLength_ = sideL(w,numberSides_);
        }
        makeBBox();
        makeVList();
    }
    
    void scale(double x, double y)
    {
        for(int i=0; i<verts.size(); ++i)
        {
            verts[i].first = verts[i].first*x;
            verts[i].second = verts[i].second*y;
        }
    }
    
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

#endif