//Christian Meyer
//CS410 Fall 2017

#include "model.h"
#include <iostream>

namespace cs410 {
    
    void Model::add_vertex(const math::Point& p){
        verticies.push_back(p.to_homogeneous());
    }
    
}
