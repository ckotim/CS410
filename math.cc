//Christian Meyer
//CS410 Fall 2017

#include "math.h"
#include <iostream>

namespace cs410 {
    
    namespace math {
        
        // point ctor
        Point::Point() : x(0), y(0), z(0) {}
        Point::Point(int x, int y, int z) : x(x), y(y), z(z) {}
        Point& Point::operator=(const Point& p){
            this->x = p.x;
            this->y = p.y;
            this->z = p.z;
            return *this;
        }
        
        // point print
        void Point::print() const {
            std::cout << '(' << x << ',' << y << ',' << z << ')' << '\n';
        }
        
        // vector ctor
        Vector::Vector(Point p) {
            this->value = p;
        }
        
        // vector printtest
        void Vector::print() const {
            this->value.print();
        }
        
    }
}
