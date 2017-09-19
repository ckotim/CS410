//Christian Meyer
//CS410 Fall 2017

#include "driver.h"
#include <math.h>
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#define PI 3.14159265

namespace cs410 {
    
    
    /* TRANSFORMATION */
    Transformation::Transformation(float wx, float wy, float wz, float theta, float scale, float tx, float ty, float tz, std::string obj) 
    : wx(wx), wy(wy), wz(wz), theta(theta), scale(scale), tx(tx), ty(ty), tz(tz), obj(obj) {}
    
    math::Matrix Transformation::get_rotation_matrix() const {
        // axis angle
        // normalize the axis of rotation
        math::Vector w(math::Point(wx, wy, wz, 0));
        w = w.unit();
        
        //pick a random vector not parallel to w and set it to 1 and renormalize
        math::Vector m = w;      
        float min = std::min(std::min(m.value.data[0], m.value.data[1]), m.value.data[2]);
        for(int i = 0; i < 3; i++){
            if(m.value.data[i] == min){
                m.value.data[i] = 1;
                break;
            }
        }
        m = m.unit();
        
        // create U = W X M
        math::Vector u = w.cross(m);
        u = u.unit();
        // creat V = W X U
        math::Vector v = w.cross(u);
        
        // build R_w / R_w^T
        
        std::vector<math::Point> columns;
        columns.push_back(u.value);
        columns.push_back(v.value);
        columns.push_back(w.value);
        columns.push_back(math::Point(0,0,0,1));
        
        math::Matrix RwT(columns);
        math::Matrix Rw = RwT.transpose();
        
        // build R_z
        std::vector<math::Point> columns2;
        columns2.push_back(math::Point(std::cos(theta * PI / 180), std::sin(theta * PI / 180), 0, 0));
        columns2.push_back(math::Point(-(std::sin(theta * PI / 180)), std::cos(theta * PI / 180), 0, 0));
        columns2.push_back(math::Point(0,0,1,0));
        columns2.push_back(math::Point(0,0,0,1));
        
        math::Matrix Rz(columns2);
        
        std::cout << Rw << '\n' << Rz << '\n' << RwT << '\n';
        
        return ((RwT * Rz) * Rw);
    }
    
    math::Matrix Transformation::get_scale_matrix() const {
        std::vector<math::Point> columns;
        columns.push_back(math::Point(scale, 0, 0, 0));
        columns.push_back(math::Point(0, scale, 0, 0));
        columns.push_back(math::Point(0, 0, scale, 0));
        columns.push_back(math::Point(0, 0, 0, 1));
        return math::Matrix(columns);
    }
    
    math::Matrix Transformation::get_translate_matrix() const {
        std::vector<math::Point> columns;
        columns.push_back(math::Point(1, 0, 0, 0));
        columns.push_back(math::Point(0, 1, 0, 0));
        columns.push_back(math::Point(0, 0, 1, 0));
        columns.push_back(math::Point(tx, ty, tz, 1));
        return math::Matrix(columns);
    }
    
    /* DRIVER */
    
    // ctors
    Driver::Driver(std::string path){
        // try to open file
        reader.open(path);
        // if open
        if(reader.is_open()) {
            // initalize tforms
            tforms = std::vector<Transformation>();
            // string for line
            std::string line;
            
            // vars for tform object
            float wx, wy, wz, theta, scale, tx, ty, tz;
            std::string name, obj;
            
            while(std::getline(reader,line)){
                std::stringstream ss;
                ss.str(line);
                ss >> name >> wx >> wy >> wz >> theta >> scale >> tx >> ty >> tz >> obj;
                tforms.push_back(Transformation(wx, wy, wz, theta, scale, tx, ty, tz, obj));
            }
        }
        reader.close();
    }
    
    // methods
    
    void Driver::Transform() {
        for(auto tform : tforms){
            // read in object into model
            std::ifstream obj_file;
            std::string line;
            std::vector<std::string> lines;
            obj_file.open("objects/" + tform.obj);
            if(obj_file.is_open()){
                while(std::getline(obj_file,line)){
                    lines.push_back(line);
                }  
            }
            // transform model
            // write model back
        }
    }

}

