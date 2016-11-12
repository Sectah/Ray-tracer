#ifndef PLANE_H
#define PLANE_H

#include <glm/glm.hpp>

#include "Shape.h"

using namespace glm;

class Plane : public Shape {
public:
	vec3 planeNormal;

	Plane(void);

	Plane(vec3 _position, vec3 _normal, vec3 _colour);

	bool Intersection(vec3 rayOrigin, vec3 rayDirection, float& u, float& v, float& w, float* t = NULL);

	vec3 CalculateNormal(vec3 p0, float& u, float& v, float& w, int* shininess = NULL, vec3* diffuseColour = NULL, vec3* specularColour = NULL);

	~Plane();
};
#endif // !SPHERE_H
