//Christian Meyer
//CS410 Fall 2017


#ifndef CS410_MODEL_H_
#define CS410_MODEL_H_

#include <string>
#include "math.h"

namespace cs410 {

	class Model {
		public:
			// ctors
            // methods
            void add_vertex(const math::Point& p);
            void translate(const float x, const float y, const float z);
            void scale(const float f);
            void rotate(const float theta, const float wx, const float wy, const float wz);
		private:
			// data
            std::vector<math::Point> verticies;
            
            
			

	};
}

#endif // CS410_MODEL_H_

