#pragma once

#include <GL/glew.h>
#include "glm.hpp"

namespace glimac {

struct ShapeVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;

    ShapeVertex(glm::vec3 _position, glm::vec3 _normal, glm::vec2 _texCoords){
		position = _position;
		normal = _normal;
		texCoords = _texCoords;
	}

	ShapeVertex(){}


};

}

