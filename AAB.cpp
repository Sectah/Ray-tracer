#include "AAB.h"

#include <glm/glm.hpp>

using namespace glm;

AAB::AAB(void) {
	position = vec3(0, 0, 0);
	size = vec3(0, 0, 0);
}

AAB::AAB(vec3 _position, vec3 _size) {
	position = _position;
	size = _size;
}

AAB::~AAB() {

}