#include "AABB.h"

#include <glm/glm.hpp>

using namespace glm;

AABB::AABB(void) {
	pMin = vec3(0);
	pMax = vec3(0);
}

AABB::AABB(vec3 _pMin, vec3 _pMax) {
	pMin = _pMin;
	pMax = _pMax;
}

bool AABB::Intersection(vec3 pMin, vec3 pMax, vec3 rayDirection, vec3 rayOrigin) {

	float t1, t2, t3, t4, t5, t6;
	float epsilon = 1e-4f;

	if (rayDirection.x) {
		t1 = pMin.x - rayOrigin.x / rayDirection.x;
		t2 = pMax.x - rayOrigin.x / rayDirection.x;
	}
	if (rayDirection.y) {
		t3 = pMin.y - rayOrigin.y / rayDirection.y;
		t4 = pMax.y - rayOrigin.y / rayDirection.y;
	}

	if (rayDirection.z) {
		t5 = pMin.z - rayOrigin.z / rayDirection.z;
		t6 = pMax.z - rayOrigin.z / rayDirection.z;
	}

	vec3 p1 = rayOrigin + rayDirection * t1;
	vec3 p2 = rayOrigin + rayDirection * t2;
	vec3 p3 = rayOrigin + rayDirection * t3;
	vec3 p4 = rayOrigin + rayDirection * t4;
	vec3 p5 = rayOrigin + rayDirection * t5;
	vec3 p6 = rayOrigin + rayDirection * t6;

	if (p1.x > pMin.x - epsilon && p1.x < pMax.x + epsilon &&
		p1.y > pMin.y - epsilon && p1.y < pMax.y + epsilon &&
		p1.z > pMin.z - epsilon && p1.z < pMax.z + epsilon) {
		return true;
	}
	if (p2.x > pMin.x - epsilon && p2.x < pMax.x + epsilon &&
		p2.y > pMin.y - epsilon && p2.y < pMax.y + epsilon &&
		p2.z > pMin.z - epsilon && p2.z < pMax.z + epsilon) {
		return true;
	}
	if (p3.x > pMin.x - epsilon && p3.x < pMax.x + epsilon &&
		p3.y > pMin.y - epsilon && p3.y < pMax.y + epsilon &&
		p3.z > pMin.z - epsilon && p3.z < pMax.z + epsilon) {
		return true;
	}
	if (p4.x > pMin.x - epsilon && p4.x < pMax.x + epsilon &&
		p4.y > pMin.y - epsilon && p4.y < pMax.y + epsilon &&
		p4.z > pMin.z - epsilon && p4.z < pMax.z + epsilon) {
		return true;
	}
	if (p5.x > pMin.x - epsilon && p5.x < pMax.x + epsilon &&
		p5.y > pMin.y - epsilon && p5.y < pMax.y + epsilon &&
		p5.z > pMin.z - epsilon && p5.z < pMax.z + epsilon) {
		return true;
	}
	if (p6.x > pMin.x - epsilon && p6.x < pMax.x + epsilon &&
		p6.y > pMin.y - epsilon && p6.y < pMax.y + epsilon &&
		p6.z > pMin.z - epsilon && p6.z < pMax.z + epsilon) {
		return true;
	}

	return false;
}

AABB::~AABB() {

}
