#ifndef AAB_H
#define AAB_H

#include <glm/glm.hpp>

using namespace glm;

class AAB {
public:
	vec3 position, size;

	AAB(void);

	AAB(vec3 position, vec3 size);

	~AAB();

};
#endif // !AAB_H
