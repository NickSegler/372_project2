#include "../src/shape.h"
#include <iostream>
using std::cout;
using std::endl;

int main(){
    Rectangle test(3, 4);
    test.draw(11.3, true);
    cout << test.draw(11.3, false) << endl;
    return 0;
}