#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>

bool loadOBJ(const char * path, std::vector<glm::vec3> & out_vertices, std::vector<glm::vec3> & out_normals);

bool BB(const char * path, std::vector<glm::vec3> & out_vertices, glm::vec3 *minVec, glm::vec3 *maxVec);

#endif
