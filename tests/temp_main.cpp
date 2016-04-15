#include "../src/shape.h"
#include <iostream>
using std::cout;
using std::endl;
#include <utility>
using std::pair;
using std::make_pair;

int main(){
    Rectangle test(3, 4);
    pair<double, double> point = make_pair(11, 18);
    test.draw(point, true);
    cout << test.draw(point, false) << endl;
    return 0;
}