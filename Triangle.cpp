#include "Triangle.h"

#include <glm/glm.hpp>

#include <iostream>

using namespace glm;
using namespace std;

Triangle::Triangle(void) {
	a = vec3(0);
	b = vec3(0);
	c = vec3(0);
	normA = vec3(0);
	normB = vec3(0);
	normC = vec3(0);
}

Triangle::Triangle(vec3 _a, vec3 _b, vec3 _c, vec3 _normA, vec3 _normB, vec3 _normC, vec3 _colour) {
	a = _a;
	b = _b;
	c = _c;
	normA = _normA;
	normB = _normB;
	normC = _normC;
	colour = _colour;
}

bool Triangle::Intersection(vec3 rayOrigin, vec3 rayDirection, float& u, float& v, float& w, float* t) {
	vec3 e1 = b - a;
	vec3 e2 = c - a;
	u = dot((rayOrigin - a), cross(rayDirection, e2)) / dot(e1, (cross(rayDirection, e2)));
	v = dot(rayDirection, (cross((rayOrigin - a), e1)) / dot(e1, cross(rayDirection, e2)));
	w = 1 - u - v;

	float t0 = dot(e2, cross((rayOrigin - a), e1)) / dot(e1, cross(rayDirection, e2));

	if ((u < 0) || (u > 1)) {
		return false;
	}
	else if ((v < 0) || (u + v > 1)) {
		return false;
	}
	else if (t0 <= 0) {
		return false;
	}
	else {
		*t = t0;
		return true;
	}
}

vec3 Triangle::CalculateNormal(vec3 p0, float& u, float& v, float& w, int* shininess, vec3* diffuseColour, vec3* specularColour) {
	*shininess = 100;
	*diffuseColour = colour;
	*specularColour = vec3(0.7);
	return (w * normA) + (u * normB) + (v * normC);
}

Triangle::~Triangle() {

}
