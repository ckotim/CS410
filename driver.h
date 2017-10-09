//Christian Meyer
//CS410 Fall 2017


#ifndef CS410_DRIVER_H_
#define CS410_DRIVER_H_

#include "math.h"
#include <string>
#include <fstream>
#include <vector>

namespace cs410 {

    class Transformation {
    public:
        // ctors
        Transformation(float wx, float wy, float wz, float theta, float scale, float tx, float ty, float tz, std::string obj);
        // methods
        math::Matrix get_rotation_matrix() const;
        math::Matrix get_scale_matrix() const;
        math::Matrix get_translate_matrix() const;

        float wx, wy, wz, theta, scale, tx, ty, tz;
        std::string obj;
    private:
    };


    class Driver {
    public:
        // ctors
        Driver(std::string path);
        
        // methods
        void transform();
        
    private:
        std::vector<Transformation> tforms;
        std::ifstream reader;
        std::string driver_name;
    };
    

}

#endif // CS410_DRIVER_H_

