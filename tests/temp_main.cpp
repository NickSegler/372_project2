#include "../src/shape.h"
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <utility>
using std::pair;
using std::make_pair;

int main(){
    double x;
    double y;
    double x1;
    double y1;
    cout << "Rectangle X: ";
    cin >> x;
    cout << "Rectangle Y: ";
    cin >> y;
    cout << "Center" << endl;
    cout << "X: ";
    cin >> x1;
    cout << "Y: ";
    cin >> y1;
    Rectangle test(x, y);
    pair<double, double> point = make_pair(x1, y1);
    test.draw(point, true);
    cout << test.draw(point, false) << endl;
    return 0;
}