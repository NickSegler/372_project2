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

// *****************************************
// **** CONSTRUCTORS & MEMBER FUNCTIONS ****
// *****************************************

// Mod_shape
Mod_shape::Mod_shape(B_shape * bsp){
    bShapeP_=bsp;
}

// S_shape (scaling)
S_shape::S_shape(B_shape * bsp, double x, double y):Mod_shape(bsp){
    scaleX_ = x;
    scaleY_ = y;
    scale();
}

void S_shape::scale(){
    for(int i=0; i<bShapeP_->verts.size();++i)
        {
            bShapeP_->verts[i].first*=scaleX_;
            bShapeP_->verts[i].second*=scaleY_;
        }
}

// R_shape (rotation)
R_shape::R_shape(B_shape * bsp, double angle):Mod_shape(bsp){
    angle_ = angle;
}

// ************************
// **** DRAW FUNCTIONS ****
// ************************

string S_shape::draw(const pair<double, double> & coord, bool to_file){
    return bShapeP_->draw(coord, to_file);
}

string R_shape::draw(const pair<double, double> & coord, bool to_file){
    string outStr = bShapeP_->draw(coord, to_file);
    
    string add = std::to_string(angle_) + " rotate \n";
    
    int rLoc = outStr.find("translate \n") + 11; //12 is the size of the searched string
    
    outStr.insert(rLoc, add);
    
    return outStr;
}