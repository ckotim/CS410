#include "math.h"
#include "driver.h"
#include <iostream>
#include <string>



int main(int argc, const char* argv[]){
 /*    cs410::math::Point p0(0,-3,.5,1);
    cs410::math::Point p1 = p0;
    cs410::math::Point p2;
    p2 = p1;
    cs410::math::Vector v(p2);
    cs410::math::Vector v2 = cs410::math::Vector(cs410::math::Point(1,1,1,0));
    
    
    std::cout << "Point: " << p2 << std::endl;
    std::cout << "Vector: " << v << std::endl;
    std::cout << "Magnitude: " << v.magnitude() << std::endl;
    std::cout << "Unit: " << v.unit() << std::endl;
    std::cout << "Scale: " << v.scale(2.5) << std::endl;
    std::cout << "Vector + Vector: " << v.add_vector(v2) << std::endl;
    std::cout << "Point + Vector: " << v.add_point(p2) << std::endl << std::endl;
    
    std::cout << "Scale: " << 2.5 * v << std::endl;
    std::cout << "Vector + Vector: " << v + v2 << std::endl;
    std::cout << "Point + Vector: " << p2 + v << std::endl << std::endl;
    
    std::cout << "Point - Point: " << p2 - (p2 + v) << std::endl;
    
    std::cout << "A * B: " << v.dot(v2) << std::endl;
    
    std::cout << "A X B: " << v.cross(v2) << std::endl;
    
    
    std::vector<cs410::math::Point> data1;
    data1.push_back(cs410::math::Point(1,0,0,0));
    data1.push_back(cs410::math::Point(0,1,0,0));
    data1.push_back(cs410::math::Point(0,0,1,0));
    data1.push_back(cs410::math::Point(1,1,1,1));
    
    std::vector<cs410::math::Point> data2;
    data2.push_back(cs410::math::Point(2,0,0,0));
    data2.push_back(cs410::math::Point(0,2,0,0));
    data2.push_back(cs410::math::Point(0,0,2,0));
    data2.push_back(cs410::math::Point(0,0,0,1));
    
    cs410::math::Matrix m1(data1);
    
    std::cout << m1 << std::endl;
    
    std::vector<cs410::math::Point> data3;
    data3.push_back(p2);
    data3.push_back(p2 + v);
    data3.push_back(p2);
    data3.push_back(cs410::math::Point(0,0,0,1));    
   
    
    cs410::math::Matrix m2(data2);
    
    //std::cout << m2 << std::endl;
    
    
    std::cout << m1.transpose() << std::endl; */
    
    
    //cs410::Driver(std::string(argv[1]));
    
    cs410::Transformation t1(0.0, 1.0, 0.0, 45, 2.0, 10.0, 0.0, 10.0, "cube.obj");
    cs410::math::Matrix r = t1.get_rotation_matrix();
    cs410::math::Matrix s = t1.get_scale_matrix();
    cs410::math::Matrix t = t1.get_translate_matrix();
    
    
    std::vector<cs410::math::Point> columns;
    columns.push_back(cs410::math::Point(0,0,0,1));
    columns.push_back(cs410::math::Point(4,0,0,1));
    columns.push_back(cs410::math::Point(4,4,0,1));
    columns.push_back(cs410::math::Point(0,4,0,1));
    columns.push_back(cs410::math::Point(0,0,4,1));
    columns.push_back(cs410::math::Point(4,0,4,1));
    columns.push_back(cs410::math::Point(4,4,4,1));
    columns.push_back(cs410::math::Point(0,4,4,1));
    
    cs410::math::Matrix points(columns);
    
/*     std::cout << points << '\n';
    std::cout << s * points << '\n';
    std::cout << t * points << '\n';
    std::cout << s * (t * points) << '\n';
    std::cout << t * (s * points) << '\n'; */

    
    
    
    std::cout << t * (s * (r * points));
    

    
    
    
    return 0;
}

