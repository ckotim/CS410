//Christian Meyer
//CS410 Fall 2017

#include "model.h"
#include <iostream>

namespace cs410 {
	Model::Model() : s("Hello, World!\n") {}
	
	void Model::printtest() {
		std::cout << this->s;
	}
}