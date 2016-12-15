#pragma once

#include "glm.hpp"
#include <string>
#include <vector>
#include "common.hpp"

using namespace std;
namespace glimac {

class Object {

public:
    bool loadObject();
    Object(const char* filepath);

    const char* filepath;
    std::vector < ShapeVertex> vertex;
};



}