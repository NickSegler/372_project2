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


string Rectangle::draw(const pair<double, double> & coord, bool to_file){
    string output = "% ! \n";
    output += "0 0\n";
    output += "newpath \n";
    output += std::to_string(coord.first);
    output += " ";
    output += std::to_string(coord.second);
    output += " translate \n";
    output += "moveto \n"
    output += std::to_string(b_box.bleft.first);
    output += " ";
    output += std::to_string(b_box.bleft.second);
    output += " lineto \n";
    output += std::to_string(b_box.bright.first);
    output += " ";
    output += std::to_string(b_box.bright.second);
    output += " lineto \n";
    output += std::to_string(b_box.tright.first);
    output += " ";
    output += std::to_string(b_box.tright.second);
    output += " lineto \n";
    output += std::to_string(b_box.tleft.first);
    output += " ";
    output += std::to_string(b_box.tleft.second);
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