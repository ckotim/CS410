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
            void transform(const math::Matrix& m);
		private:
			// data
            std::vector<math::Point> verticies;
            
            
			

	};
}

#endif // CS410_MODEL_H_

