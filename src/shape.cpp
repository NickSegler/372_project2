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
E_triangle::E_triangle(double w, double h){
    double sidelen = std::sqrt((h * h) + ((.5 * w) * (.5 * w)));
    me = Polygon(sidelen, 3);
}
//    R_triangle
R_triangle::R_triangle(double w, double h){
   b_box.bright = make_pair(w, 0);
   b_box.tright = make_pair(w, h); 
   b_box.tleft  = make_pair(0, h);

   verts.push_back(make_pair(0,0));
   verts.push_back(make_pair(0,h));
   verts.push_back(make_pair(w,0));
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

// ************************
// ****     STACK      ****
// ************************

string H_stack::draw(const pair<double, double> & coord, bool to_file)
{
    std::cout << "kek" << std::endl;
}

string V_stack::draw(const pair<double, double> & coord, bool to_file)
{   
    string output;
    pair<double,double> start = coord;
    double total_width = 0;     // bounding box
    double greatest_height = 0;    // bounding box
    double starting_height = start.second;
    double baseline;  // record initial y



    // find greatest height item and make baseline
    for(int i = 0; i < theStack.size(); ++i)
    {
        if(greatest_height < findHeight(theStack[i]))
        {   greatest_height = findHeight(theStack[i]);  }
    }

    // Baseline = drop to middle of greatest b_shape height from starting_y
    baseline = starting_height - (greatest_height/2);

    // drop from starting point to baseline
    start.second = baseline;

    for(int i = 0; i < theStack.size(); ++i)
    {
        //Circles
        if(theStack[i]->verts.size() <= 2)
        {  
            double radius = theStack[i]->verts[1].first; 
            std::cout << radius << std::endl;
            start.first += radius;
            output += (theStack[i]->draw(start,false));

            if(i < theStack.size()-1)
            {   start.first += radius;  }
        }

        // Triangles
        // Rectangles
        else if(theStack[i]->verts.size() <= 4)
        {
            // find height of rect and shift up from baseline
            double height = findHeight(theStack[i]);
            start.second =  baseline - (height/2);
            output += (theStack[i]->draw(start,false));

            // if not last
            if(i < theStack.size()-1)
            {   // shift start_y to baseline
                // shift start_x to edge of box
                double width = findWidth(theStack[i]);
                start = make_pair(start.first + width, baseline);
            }

            else    // shift start back to baseline
            {   start = make_pair(start.first, baseline);   }
        }

        // Polygons, start from center
        else if(theStack[i]->verts.size() > 4)
        {
            //drop to baseline and shift over half width;
            double width = findWidth(theStack[i]);
            start.first += width/2;
            start.second = baseline;
            output += (theStack[i]->draw(start,false));

            // shift to edge
            start.first += width/2;
        }


        else
        {   output += (theStack[i]->draw(start,false)); }
    }

    if(!to_file)
    {   std::cout << output << std::endl;   }

    else
    {
        ofstream write("yourprogram.ps");
        if(!write)
        throw runtime_error("invalid filename");
    
        write << output;
    
        write.close();
    }
}

pair<double,double> V_stack::findGreatest(B_shape * bsp)
{
    double greatest_y = 0;
    double greatest_x = 0;

    for(int j = 0; j <= (bsp->verts.size()); ++j)
    {
        // if y is greater, replace greatest y
        if(greatest_y < bsp->verts[j].second )
        {   greatest_y = bsp->verts[j].second; }

        // if x is greater, replace greatest x
        if(greatest_x < bsp->verts[j].first)
        { greatest_x = bsp->verts[j].first;}              
    }

    pair<double,double> greatest_Values = make_pair(greatest_x,greatest_y);
    return greatest_Values;
}

double V_stack::findHeight(B_shape *bsp)
{
    double greatest_y = 0;
    double least_y = 0;
    double height;

    for(int j = 0; j <= (bsp->verts.size()); ++j)
    {
        // if y is greater, replace greatest y
        if(greatest_y < bsp->verts[j].second )
        {   greatest_y = bsp->verts[j].second; }

        // if x is greater, replace greatest x
        if(least_y > bsp->verts[j].second)
        { least_y = bsp->verts[j].second;}
    }

    // if negative
    if(least_y <= 0)
    {   height = greatest_y + least_y;    }

    // if positive
    else
    {   height = greatest_y - least_y;   }

    return height;
}

double V_stack::findWidth(B_shape *bsp)
{
    double greatest_x = 0;
    double least_x = 0;
    double height;

    for(int j = 0; j <= (bsp->verts.size()); ++j)
    {
        // if x is less, replace greatest x
        if(greatest_x < bsp->verts[j].first )
        {   greatest_x = bsp->verts[j].first; }

        // if x is greater, replace least x
        if(least_x > bsp->verts[j].first)
        { least_x = bsp->verts[j].first;}
    }

    // if negative
    if(least_x <= 0)
    {   height = greatest_x- least_x;    }

    // if positive
    else
    {   height = greatest_x - least_x;   }

    return height;
}
