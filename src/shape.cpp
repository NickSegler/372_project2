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

//this uses the formula provided
pair<double,double> polygonPoint(double l, int n, int k)
{
    double x, y;
    
    x = ((l/2)*((sin(((2*k+1)*3.14)/n)/sin(3.14/n))));
    y = ((-l/2)*((cos(((2*k+1)*3.14)/n)/sin(3.14/n))));
    
    return make_pair(x,y);
}

string head = "% ! \n0 0\nnewpath \n";

string psTo(double x, double y, int t)
{
    string rStr;
    
    rStr += std::to_string(x);
    rStr += " ";
    rStr += std::to_string(y);
    
    if(t==0)
    {
        rStr += " moveto \n";
    }else
    {
        rStr += " lineto \n ";
    }
    
    
    return rStr;
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


string B_shape::draw(const pair<double, double> & coord, bool to_file)
{
    string outStr;
    
    outStr = "% ! \n";
    outStr += "0 0\n";
    outStr += "newpath \n";
    outStr += "gsave \n";
    outStr += std::to_string(coord.first);
    outStr += " ";
    outStr += std::to_string(coord.second);
    outStr += " translate \n";

    
    for(int i =0; i<verts.size(); ++i)
    {
        outStr += psTo(verts[i].first, verts[i].second, i);
    }
    
    outStr += "closepath \n";
    outStr += "stroke \n";
    outStr += "grestore \n";
    
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

string Triangle::draw(const pair<double, double> & coord, bool to_file){
    string output = head;
    output += std::to_string(coord.first - (width_/2));
    output += " ";
    output += std::to_string(coord.second - (height_/2));
    output += " translate \n";
    output += "moveto \n";
    output += std::to_string(0);
    output += " ";
    output += std::to_string(0);
    output += " lineto \n";
    output += std::to_string(b_box.bright.first);
    output += " ";
    output += std::to_string(b_box.bright.second);
    output += " lineto \n";
    output += std::to_string(b_box.tright.first);
    output += " ";
    output += std::to_string(b_box.tright.second);
    output += " lineto \n";
    output += std::to_string(b_box.tleft.first/2);
    output += " ";
    output += std::to_string(b_box.tleft.second/2);
    output += " lineto \n";
    output += "closepath \n";
    
    
    output += "stroke";
    if(!to_file)
        return output;
    else{
        ofstream write("yourprogram.ps");
        if(!write)
            throw runtime_error("invalid filename");
        
        write << output;
        
        write.close();
        return "";
    }
}

string Circle::draw(const pair<double, double> & coord, bool to_file)
{
    string outStr;
    
    outStr += head;
    outStr += "gsave \n";
    outStr += std::to_string(coord.first);
    outStr += " ";
    outStr += std::to_string(coord.second);
    outStr += " translate \n";
    outStr += "0 0 ";
    outStr += std::to_string(radius_);
    outStr += " 0 360 arc\n";
    outStr += "closepath \n";
    outStr += "stroke\n";
    outStr += "grestore\n";
    
    
    
    return outStr;
}
