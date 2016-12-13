#pragma once

#include "glm.hpp"
#include <string>
#include <vector>

using namespace std;
namespace glimac {


	bool loadObject(const char* filepath,
    std::vector < glm::vec3 > & out_vertices,
    std::vector < glm::vec2 > & out_uvs,
    std::vector < glm::vec3 > & out_normals);


}