#pragma once

#include <vector>

#include "common.hpp"

namespace glimac {

class Cube {
    void build(GLfloat taille);
public:
    /*Cube(GLfloat taille):m_nVertexCount(0) {
        build(taille);
    }*/

    Cube(GLfloat taille);

    const ShapeVertex* getDataPointer() const {
        return &m_Vertices[0];
    }

    GLsizei getVertexCount() const {
        return m_nVertexCount;
    }


private:
    std::vector<ShapeVertex> m_Vertices;
    GLsizei m_nVertexCount;
    /*GLfloat m_Vertices[108];
    GLfloat m_Colors[108];*/
};
    
}