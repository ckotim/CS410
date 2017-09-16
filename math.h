//Christian Meyer
//CS410 Fall 2017

// Defines all math for 3D renderer


#ifndef CS410_MATH_H_
#define CS410_MATH_H_

#include <vector>

namespace cs410 {
    
    namespace math {
        
        // point (x,y,z) in 3D space
        struct Point {
            // data
            int x, y, z;
            
            // ctors
            Point();
            Point(int x, int y, int z);
            Point& operator=(const Point&);
            
            //methods
            void print() const;
        };
        
        // vector [x,y,z] in 3D space
        class Vector  {
        public:
            // ctors
            Vector(Point p);
            void print() const;
            
            // methods
            
            int magnitude();
            Vector scale(const float& f) const;
            Vector add(const Vector& v) const;
            Vector dot(const Vector& v) const;
            Vector cross(const Vector& v) const;
        private:
            // magnitude and direction of point
            Point value;
            
        };
        
        // matrix N * 4 
        class Matrix {
        public:
            // ctors
            Matrix();
            void print() const;
            
            // methods
            Matrix multiply(const Matrix& m) const;
            Matrix multiply(const Vector& v) const;
        private:
            std::vector<Point> data;
        };
        
        //overloads
        
        // float * vector for scalar vector multipliation
        Vector operator*(float i, const Vector& v);
        Vector operator+(const Vector& v1, const Vector& v2);
        Point operator+(const Point& p, const Vector& v);
        Matrix operator*(const Matrix& m1, const Matrix& m2);
        Matrix operator*(const Matrix& m, const Vector& v);
        
    }
}

#endif // CS410_MATH_MATRIX_H_

