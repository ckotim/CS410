//Christian Meyer
//CS410 Fall 2017

#include "math.h"
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>

namespace cs410 {
    
    namespace math {
        
        /* POINT */
        
        // ctors
        Point::Point() : data{0, 0, 0, 0} {}
        Point::Point(float x, float y, float z, float h) : data{x, y, z, h} {}
        
        
        // print
        std::ostream& operator<<(std::ostream& os, const Point& p) {
            return os << '(' <<  p.data[0] << ',' << p.data[1] << ',' << p.data[2] << ',' << p.data[3] << ')';
        }    
        
        // to homogeneous
        Point Point::to_homogeneous() const {
            if(data[3] == 0)
                return(Point(data[0],data[1],data[2],data[3]));
            return *this;
        }
        
        // to cartesian
        Point Point::to_cartesian() const {
            if(data[3] != 0){
                return Point(data[0] * data[3], data[1] * data[3], data[2] * data[3], 0);
            }
            return *this;
        }
        
        /* VECTOR */
        
        // ctors
        Vector::Vector(Point p) : value(p), is_homogeneous(false) {}
        
        // print
        std::ostream& operator<<(std::ostream& os, const Vector& v){
            return os << '[' <<  v.value.data[0] << ',' << v.value.data[1] << ',' << v.value.data[2] << ',' << v.value.data[3] << ']';
        }  
       
        
        // magnitude
        float Vector::magnitude() const {
            return sqrt((value.data[0] * value.data[0]) + (value.data[1] * value.data[1]) + (value.data[2] * value.data[2]));
        }
        
        // unit vector
        Vector Vector::unit() const {
            float m = this->magnitude();
            return Vector(Point(value.data[0] / m, value.data[1] / m, value.data[2] / m, value.data[3]));
        }
        
        // scale
        Vector Vector::scale(const float& f) const {
            return Vector(Point(value.data[0] * f, value.data[1] * f, value.data[2] * f, value.data[3]));
        }
        
        // add point
        Point Vector::add_point(const Point& p) const {
            return Point(value.data[0] + p.data[0], value.data[1] + p.data[1], value.data[2] + p.data[2], value.data[3]);
        }
        
        // add vector
        Vector Vector::add_vector(const Vector& v) const {
            return Vector(Point(value.data[0] + v.value.data[0], value.data[1] + v.value.data[1], value.data[2] + v.value.data[2], value.data[3]));
        }
        
        // dot product
        float Vector::dot(const Vector& v) const {
            return (value.data[0] * v.value.data[0]) + (value.data[1] * v.value.data[1]) + (value.data[2] * v.value.data[2]) + (value.data[3] * v.value.data[3]);
        }
        
        // cross product
        Vector Vector::cross(const Vector& v) const {
            float cx = (value.data[1] * v.value.data[2]) - (value.data[2] * v.value.data[1]);
            float cy = (value.data[2] * v.value.data[0]) - (value.data[0] * v.value.data[2]);
            float cz = (value.data[0] * v.value.data[1]) - (value.data[1] * v.value.data[0]);            
            return Vector(Point(cx, cy, cz, value.data[3]));
        }
        
        /* MATRIX */    
        
        // ctors
        Matrix::Matrix(std::vector<Point> columns) : columns(columns) {}
        
        Matrix::Matrix(int num_cols) {
            columns = std::vector<Point>();
            for(int i = 0; i < num_cols; i++){
                columns.push_back(Point());
            }
        }
        
        // print
        std::ostream& operator<<(std::ostream& os, const Matrix& m) {
            std::stringstream ssx;
            std::stringstream ssy;            
            std::stringstream ssz;            
            std::stringstream ssh; 
            
            ssx << '|';
            ssy << '|';
            ssz << '|';
            ssh << '|';
            for(auto a : m.columns){
                ssx << a.data[0] << '\t';
                ssy << a.data[1] << '\t';
                ssz << a.data[2] << '\t';
                ssh << a.data[3] << '\t';
            }  
            ssx << "|\n";
            ssy << "|\n";
            ssz << "|\n";
            ssh << "|\n";            
            
            os << ssx.str() << ssy.str() << ssz.str() << ssh.str();
            return os;
        }     
        
        // number of rows
        int Matrix::num_rows() const {
            return 4;
        }
        
        // num of cols
        int Matrix::num_cols() const {
            return columns.size();
        }
        
        // add element
        void Matrix::add_element(const int& row, const int& col, const float& val) {
            columns[col].data[row] = val;
        }
        
        // get element
        float Matrix::get_element(const int& row, const int& col) const {
            return columns[col].data[row];
        }
        
        // M x M
        Matrix Matrix::multiply(const Matrix& m) const {
            // figure out how many colums new matrix will have
            Matrix result(m.columns.size());
            
            // for each entry in new matrix do the dot product 
            for(unsigned int col = 0; col < m.columns.size(); col++){
                for(int row = 0; row < 4; row++){
                    Vector v1(Point(columns[0].data[row], columns[1].data[row], columns[2].data[row], columns[3].data[row]));
                    Vector v2(m.columns[col]);
                    result.add_element(row, col, v1.dot(v2));                                        
                }
            }
            return result;
        }
        
        // transpose
        Matrix Matrix::transpose() const {
            Matrix result(columns.size());
            
            for(unsigned int col = 0; col < columns.size(); col++){
                for(int row = 0; row < 4; row++){
                    result.add_element(col, row, this->get_element(row, col));                                       
                }
            }
            
            return result;
        }
        
        /* Operators */

        Point operator+(const Point& p, const Vector& v) {
            return v.add_point(p);
        }  
        
        Vector operator-(const Point& p1, const Point& p2){
            return Vector(Point(p1.data[0] - p2.data[0], p1.data[1] - p2.data[1], p1.data[2] - p2.data[2], p1.data[3]));
        }
        
        Vector operator*(float i, const Vector& v){
            return v.scale(i);
        }
        
        Vector operator+(const Vector& v1, const Vector& v2){
            return v1.add_vector(v2);
        }
        
        Matrix operator*(const Matrix& m1, const Matrix& m2) {
            return m1.multiply(m2);
        }
        
    }
}
