#include "Sphere.h"

#include <glm/glm.hpp>

using namespace glm;

Sphere::Sphere(void) {
	radius = 0.0f;
}

Sphere::Sphere(vec3 _position, float _radius, vec3 _colour) {
	position = _position;
	radius = _radius;
	colour = _colour;
}

bool Sphere::Intersection(vec3 rayOrigin, vec3 rayDirection, float& u, float& v, float& w, float* t) {
	vec3 L = position - rayOrigin;
	float tca = dot(L, rayDirection);

	if (tca < 0) {
		return false;
	}

	float s2 = (dot(L, L)) - (tca * tca);
	float s = sqrt(s2);

	if (s > radius) {
		return false;
	}

	float thc = sqrt((radius * radius) - s2);
	*t = tca - thc;

	return true;
}

vec3 Sphere::CalculateNormal(vec3 p0, float& u, float& v, float& w, int* shininess, vec3* diffuseColour, vec3* specularColour) {
	*shininess = 20;
	*diffuseColour = colour * vec3(0.5);
	*specularColour = vec3(0.7);
	return (p0 - position);
}

Sphere::~Sphere() {

}