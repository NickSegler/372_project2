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


// CHANGE TO CONST BY REF
string Rectangle::draw(double coord, bool to_file){
    string output = "";
    double corner = coord - ((b_box.y / 2)+(b_box.x / 2));
    output += "0 0\n";
    output += "newpath \n";
    output += "moveto \n";
    output += std::to_string(corner*72);
    corner += b_box.x;
    output += " ";
    output += std::to_string(corner*72);
    output += " rlineto \n";
    corner += b_box.y;
    output += std::to_string(corner*72);
    output += " ";
    corner -= b_box.x;
    output += std::to_string(corner*72);
    output += " rlineto \n";
    corner -= b_box.y;
    output += std::to_string(corner*72);
    output += " ";
    corner -= b_box.x;
    output += std::to_string(corner*72);
    output += " rlineto \n";
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