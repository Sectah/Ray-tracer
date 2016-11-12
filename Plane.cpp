#include "Plane.h"

#include <glm/glm.hpp>

using namespace glm;

Plane::Plane(void) {
	planeNormal = vec3(0);
}

Plane::Plane(vec3 _position, vec3 _normal, vec3 _colour) {
	position = _position;
	planeNormal = _normal;
	colour = _colour;
}

bool Plane::Intersection(vec3 rayOrigin, vec3 rayDirection, float& u, float& v, float& w, float* t)
{
	float denom = dot(rayDirection, planeNormal);

	if (abs(denom) < 1e-6) {
		return false;
	}
	else if (t <= 0) {
		return false;
	}
	else {
		*t = dot((position - rayOrigin), planeNormal) / denom;
		return *t >= 0;
	}
}

vec3 Plane::CalculateNormal(vec3 p0, float& u, float& v, float& w, int* shininess, vec3* diffuseColour, vec3* specularColour) {
	*shininess = 1;
	*diffuseColour = vec3(0.6, 0.5, 0.2);
	*specularColour = colour;
	return planeNormal;
}

Plane::~Plane() {

}
