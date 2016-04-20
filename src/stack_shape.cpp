//scale_shape.cpp

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

// ************************
// ****     STACK      ****
// ************************

string H_stack::draw(const pair<double, double> & coord, bool to_file)
{
    string output;
    pair<double,double> start = coord;
    double total_width = 0;     // bounding box
    double greatest_width = 0;    // bounding box
    double starting_width = start.first;
    double baseline;  // record initial y



    // find greatest height item and make baseline
    for(int i = 0; i < theStack.size(); ++i)
    {
        if(greatest_width < findHeight(theStack[i]))
        {   greatest_width = findHeight(theStack[i]);  }
    }

    // Baseline = drop to middle of greatest b_shape height from starting_y
    baseline = starting_width - (greatest_width/2);

    // drop from starting point to baseline
    start.first = baseline;

    for(int i = 0; i < theStack.size(); ++i)
    {
        //Circles
        if(theStack[i]->verts.size() <= 2)
        {  
            double radius = theStack[i]->verts[1].second; 
            start.second -= radius; // shift down y_coord
            output += (theStack[i]->draw(start,false));

            if(i < theStack.size()-1)   // shift down rest of y_coord
            {   
                start.second -= radius;
             
                if(theStack[i+1]->verts.size() == 4)   // If next is a square
                {
                    double height = findHeight(theStack[i+1]);
                    start = make_pair(baseline, start.second - height);  
                }
            }
        }

        // Triangels
            // ADD

        // Rectangles
        else if(theStack[i]->verts.size() <= 4)
        {
            // find width of rect and shift right from baseline
            double width = findWidth(theStack[i]);
            start.first =  baseline - (width/2);    // x_coord
            output += (theStack[i]->draw(start,false));

            if(i < theStack.size()-1)
            {   
                if(theStack[i+1]->verts.size() == 4)
                {
                    double height = findHeight(theStack[i+1]);
                    start = make_pair(baseline, start.second - height);  
                }

                else
                { start = make_pair(baseline, start.second);}
            }
            else
            {   start = make_pair(baseline, start.second);}
            
        }

        // Polygons, start from center
        else if(theStack[i]->verts.size() > 4)
        {
            //drop to baseline and shift over half width;
            double height = findHeight(theStack[i]);
            start.first = baseline;
            start.second -= (height/2);
            output += (theStack[i]->draw(start,false));

            // shift to edge
            start.second -= (height/2);

            if(i < theStack.size()-1)
            {   
                if(theStack[i+1]->verts.size() == 4)
                {
                    double height = findHeight(theStack[i+1]);
                    start = make_pair(baseline, start.second - height);  
                }

                else
                { start = make_pair(baseline, start.second);}
            }
        }


        else
        {   output += (theStack[i]->draw(start,false)); }
    }

    if(!to_file)
    {   return output;   }

    else
    {
        ofstream write("yourprogram.ps");
        if(!write)
        throw runtime_error("invalid filename");
    
        write << output;
    
        write.close();
    }
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
    {   return output;   }

    else
    {
        ofstream write("yourprogram.ps");
        if(!write)
        throw runtime_error("invalid filename");
    
        write << output;
    
        write.close();
    }
}

pair<double,double> Stack::findGreatest(B_shape * bsp)
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

double Stack::findHeight(B_shape *bsp)
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
    {   height = greatest_y - least_y;    }

    // if positive
    else
    {   height = greatest_y - least_y;   }

    return height;
}

double Stack::findWidth(B_shape *bsp)
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
    {   height = greatest_x - least_x;    }

    // if positive
    else
    {   height = greatest_x - least_x;   }

    return height;
}