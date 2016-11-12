#ifndef SHAPE_H
#define SHAPE_H

#include <glm/glm.hpp>

using namespace glm;

class Shape {
public:
	vec3 position;
	vec3 colour;
	vec3 normal;

	Shape(void);

	Shape(vec3 _position, vec3 _colour, vec3 _normal);

	virtual bool Intersection(vec3 rayOrigin, vec3 rayDirection, float& u, float& v, float& w, float* t = NULL);

	virtual vec3 CalculateNormal(vec3 p0, float& u, float& v, float& w, int* shininess = NULL, vec3* diffuseColour = NULL, vec3* specularColour = NULL);

	~Shape();

};
#endif // !SPHERE_H
