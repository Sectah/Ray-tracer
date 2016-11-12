#ifndef AABB_H
#define AABB_H

#include <glm/glm.hpp>

using namespace glm;

class AABB {
public:
	vec3 pMin, pMax;

	AABB(void);

	AABB(vec3 pMin, vec3 pMax);

	bool Intersection(vec3 pMin, vec3 pMax, vec3 rayDirection, vec3 rayOrigin);

	~AABB();
};
#endif // !AABB_H
