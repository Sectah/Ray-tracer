#ifndef SPHERE_H
#define SPHERE_H

#include <glm/glm.hpp>

#include "Shape.h"

using namespace glm;

class Sphere : public Shape {
public:
	float radius;

	Sphere(void);

	Sphere(vec3 _position, float _radius, vec3 _colour);

	bool Intersection(vec3 rayOrigin, vec3 rayDirection, float& u, float& v, float& w, float* t = NULL);

	vec3 CalculateNormal(vec3 p0, float& u, float& v, float& w, int* shininess = NULL, vec3* diffuseColour = NULL, vec3* specularColour = NULL);

	~Sphere();
};
#endif // !SPHERE_H
