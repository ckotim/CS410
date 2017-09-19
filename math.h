//Christian Meyer
//CS410 Fall 2017

// Defines all math for 3D renderer


#ifndef CS410_MATH_H_
#define CS410_MATH_H_

#include <vector>
#include <iostream>

namespace cs410 {
    
    namespace math {
        
        // point (x,y,z) in 3D space
        struct Point {
            // data
            float data[4];
            
            // ctors
            Point();
            Point(float x, float y, float z, float h);
            
            // methods
            Point to_homogeneous() const;
            Point to_cartesian() const;
        };
        
        // vector [x,y,z] in 3D space
        class Vector  {
        public:
            // ctors
            Vector(Point p);
            
            // methods
            float magnitude() const;
            Vector unit() const;
            Vector scale(const float& f) const;
            Point add_point(const Point& p) const;
            Vector add_vector(const Vector& v) const;
            float dot(const Vector& v) const;
            Vector cross(const Vector& v) const;

            // x,y,z
            Point value;
            bool is_homogeneous;
        private:            
        };
        
        // matrix N * 4 
        class Matrix {
        public:
            // ctors
            Matrix(int num_cols);
            Matrix(std::vector<Point> data);
            void print() const;
            
            // methods
            int num_rows() const;
            int num_cols() const;
            void add_element(const int& row, const int& col, const float& val);
            float get_element(const int& row, const int& col) const;
            Matrix multiply(const Matrix& m) const;
            Matrix transpose() const;
            
            std::vector<Point> columns;
        private:
        };
        
        //overloads
        std::ostream& operator<<(std::ostream& os, const Point& p);
        std::ostream& operator<<(std::ostream& os, const Vector& v);     
        std::ostream& operator<<(std::ostream& os, const Matrix& m);         
        
        Point operator+(const Point& p, const Vector& v);
        Vector operator-(const Point& p1, const Point& p2);
        Vector operator*(float i, const Vector& v);
        Vector operator+(const Vector& v1, const Vector& v2);
        Matrix operator*(const Matrix& m1, const Matrix& m2);
        Matrix operator*(const Matrix& m, const Vector& v);
        
    }
}

#endif // CS410_MATH_MATRIX_H_

