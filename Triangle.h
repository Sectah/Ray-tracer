#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <glm/glm.hpp>

#include "Shape.h"

using namespace glm;

class Triangle : public Shape {
public:
	vec3 a, b, c, normA, normB, normC;

	Triangle(void);

	Triangle(vec3 _a, vec3 _b, vec3 _c, vec3 _normA, vec3 _normB, vec3 _normC, vec3 _colour);

	bool Intersection(vec3 rayOrigin, vec3 rayDirection, float& u, float& v, float& w, float* t = NULL);

	vec3 CalculateNormal(vec3 p0, float& u, float& v, float& w, int* shininess = NULL, vec3* diffuseColour = NULL, vec3* specularColour = NULL);

	~Triangle();
};
#endif // !SPHERE_H
