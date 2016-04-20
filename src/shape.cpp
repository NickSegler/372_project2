// shape.cpp
// Source file containing declarations for our shape class hierarchy
// Descriptions are in header file
// for cs372
// Spring 2016
// Heart Break Gorillas

#include "shape.h"
#include <string>
using std::string;
#include <fstream>
using std::ifstream;
using std::ofstream;
#include <stdexcept>
using std::runtime_error;
#include <utility>
using std::pair;
#include <cmath>

// **************************
// **** HELPER FUNCTIONS ****
// **************************
//this uses the formula provided
pair<double,double> polygonPoint(double l, int n, int k)
{
    double x, y;
    
    x = ((l/2)*((sin(((2*k+1)*3.14)/n)/sin(3.14/n))));
    y = ((-l/2)*((cos(((2*k+1)*3.14)/n)/sin(3.14/n))));
    
    return make_pair(x,y);
}

string head = "% !\n0 0\nnewpath\n";

string psTo(double x, double y, int t)
{
    string rStr;
    
    rStr += std::to_string(x);
    rStr += " ";
    rStr += std::to_string(y);
    
    if(t==0)
    {
        rStr += " moveto\n";
    }else
    {
        rStr += " lineto\n";
    }
    
    
    return rStr;
}


// ******************************************
// **** CONSTRUCTORS && MEMBER FUNCTIONS ****
// ******************************************

// Rectangle
Rectangle::Rectangle(int x, int y){
        b_box.bright = make_pair(x, 0);
        b_box.tright = make_pair(x, y);
        b_box.tleft  = make_pair(0, y);
        
        verts.push_back(make_pair(0,0));
        verts.push_back(make_pair(0,y));
        verts.push_back(make_pair(x,y));
        verts.push_back(make_pair(x,0));
}

// Polygon
Polygon::Polygon():sideLength_(10),numberSides_(4){
    makeBBox();
    makeVList();
}

Polygon::Polygon(double l, int n):sideLength_(l),numberSides_(n){
    makeBBox();
    makeVList();
}

Polygon::Polygon(double w, double h, int n):numberSides_(n){
    if(n%2==0)
    {
        sideLength_ = sideL(h,numberSides_);
    }else{
        sideLength_ = sideL(w,numberSides_);
    }
    makeBBox();
    makeVList();
}

void Polygon::scale(double x, double y){
    for(int i=0; i<verts.size(); ++i)
    {
        verts[i].first = verts[i].first*x;
        verts[i].second = verts[i].second*y;
    }
}
//uses the inradius to find sidelength
double Polygon::sideL(double r, int sides)
{
    return (2*r*(tan(180/sides)));
}

void Polygon::makeBBox()
{
    if(numberSides_%2==1)
    {
        double h,w;
        w=(sideLength_*((sin((3.14*(numberSides_-1))/2*numberSides_))/sin(3.14/numberSides_)));
        h=(sideLength_*((1+cos(3.14/numberSides_))/2*sin(3.14/numberSides_)));
        
        b_box.bright = make_pair(w, 0);
        b_box.tright = make_pair(w, h);
        b_box.tleft  = make_pair(0, h);
        
    }else if (numberSides_%2==0 && numberSides_%4!=0)
    {
        double h,w;
        w=(sideLength_*(1/(sin(3.14/numberSides_))));
        h=(sideLength_*((cos(3.14/numberSides_))/(sin(3.14/numberSides_))));
        
        b_box.bright = make_pair(w, 0);
        b_box.tright = make_pair(w, h);
        b_box.tleft  = make_pair(0, h);
    }else
    {
        double h,w;
        w=(sideLength_*((cos(3.14/numberSides_))/(sin(3.14/numberSides_))));
        h=(sideLength_*((cos(3.14/numberSides_))/(sin(3.14/numberSides_))));
        
        b_box.bright = make_pair(w, 0);
        b_box.tright = make_pair(w, h);
        b_box.tleft  = make_pair(0, h);
    }
}

void Polygon::makeVList()
{
    for(int i =0; i<numberSides_; ++i)
    {
        verts.push_back(polygonPoint(sideLength_ ,numberSides_ ,i));
    }
}

// Triangles
//     E_triangle
E_triangle::E_triangle(int x, int y){
    double sidelen = std::sqrt((y * y) + ((.5 * x) * (.5 * x)));
    me = Polygon(sidelen, 3);
}

// ************************
// **** DRAW FUNCTIONS ****
// ************************
string B_shape::draw(const pair<double, double> & coord, bool to_file)
{
    string outStr;
    
    outStr = "% !\n";
    outStr += "0 0\n";
    outStr += "newpath\n";
    outStr += "gsave\n";
    outStr += std::to_string(coord.first);
    outStr += " ";
    outStr += std::to_string(coord.second);
    outStr += " translate\n";

    
    for(int i =0; i<verts.size(); ++i)
    {
        outStr += psTo(verts[i].first, verts[i].second, i);
    }
    
    outStr += "closepath\n";
    outStr += "stroke\n";
    outStr += "grestore\n";
    
    if(!to_file)
        return outStr;
    else{
        ofstream write("yourprogram.ps");
        if(!write)
        throw runtime_error("invalid filename");
        
        write << outStr;
        
        write.close();
        return "";
    }
}

string Circle::draw(const pair<double, double> & coord, bool to_file)
{
    string outStr;
    
    outStr += head;
    outStr += "gsave\n";
    outStr += std::to_string(coord.first);
    outStr += " ";
    outStr += std::to_string(coord.second);
    outStr += " translate\n";
    outStr += "0 0 ";
    outStr += std::to_string(radius_);
    outStr += " 0 360 arc\n";
    outStr += "closepath \n";
    outStr += "stroke\n";
    outStr += "grestore\n";
    
    
    
    return outStr;
}

string E_triangle::draw(const pair<double, double> & coord, bool to_file){
    return me.draw(coord, to_file);
}
