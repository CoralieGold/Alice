#pragma once

#include <vector>

#include "common.hpp"

namespace glimac {

class Card {
public:
    /*Cube(GLfloat taille):m_nVertexCount(0) {
        build(taille);
    }*/

    Card(GLfloat taille);

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