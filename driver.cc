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
        driver_name = path.substr(0, path.size() - 4);
        std::system(("mkdir " + driver_name).c_str());
        
        reader.close();
    }
    
    // methods
    
    void Driver::transform() {
        for(auto tform : tforms){
            math::Matrix r = tform.get_rotation_matrix();
            math::Matrix s = tform.get_scale_matrix();
            math::Matrix t = tform.get_translate_matrix();
            
            //create writer
            
            int i = 0;
            int j = 0;
            std::string write_name = driver_name + "/" + tform.obj.substr(0, tform.obj.size() - 4) + "_mw" + std::to_string(i) + std::to_string(j) + ".obj";
            std::ifstream file_checker(write_name);
            while(file_checker.good()) {
                if(j == 9) {
                    i++;
                    j = 0;
                } else {
                    j++;
                }
                write_name = driver_name + "/" + tform.obj.substr(0, tform.obj.size() - 4) + "_mw" + std::to_string(i) + std::to_string(j) + ".obj";
                file_checker.close();
                file_checker.open(write_name);
            }
            std::ofstream obj_writer(write_name);          
            
            // read in object into model
            std::ifstream obj_file;
            std::string line;
            std::vector<std::string> lines;
            obj_file.open(tform.obj);
            //std::cout << "Opening object" << '\n';
            if(obj_file.is_open()){
                //std::cout << "Sucessfully Opened Object" << '\n';
                while(std::getline(obj_file,line)){
                    //std::cout << line << '\n';
                    lines.push_back(line);
                }  
            }
            // transform model
            obj_writer << "# This file was modified by Christian Meyer for CS410 Fall 2017" << '\n';
            for(std::string &cur_line : lines) {
                if(cur_line.substr(0,2) == "v "){
                    std::stringstream ss;
                    ss.str(cur_line);
                    std::string v;
                    float x, y, z;
                    ss >> v >> x >> y >> z;
                    std::vector<math::Point> point;
                    point.push_back(math::Point(x,y,z,1));
                    math::Matrix point_matrix(point);

                    point_matrix = t * (s * (r * point_matrix));
                    
                    std::stringstream ll;
                    
                    ll << v << " " << point_matrix.get_element(0, 0) << " " << point_matrix.get_element(1, 0) << " " << point_matrix.get_element(2, 0);
                    //std::cout << ll.str() << '\n';
                    cur_line = ll.str();
                    obj_writer << (cur_line) << '\n';
                } else if(cur_line.substr(0,2) != "vn" && cur_line.substr(0,2) != "s "){
                    obj_writer << (cur_line) << '\n';
                }
            }
            obj_writer.close();

        }
    }

}

