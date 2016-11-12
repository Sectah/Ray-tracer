#include "Shape.h"

#include <glm/glm.hpp>

using namespace glm;

Shape::Shape(void) {
	position = vec3(0);
	colour = vec3(0);
	normal = vec3(0);
}

Shape::Shape(vec3 _position, vec3 _colour, vec3 _normal) {
	position = _position;
	colour = _colour;
	normal = _normal;
}

bool Shape::Intersection(vec3 rayOrigin, vec3 rayDirection, float& u, float& v, float& w, float* t) {
	return false;
}

vec3 Shape::CalculateNormal(vec3 p0, float& u, float& v, float& w, int* shininess, vec3* diffuseColour, vec3* specularColour) {
	return normal;
}

Shape::~Shape() {

}