#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "glimac/Card.hpp"

namespace glimac {

Card::Card(GLfloat taille) {
        // Division de la taille








        taille /= 2;
        GLfloat width = taille * 0.8;
        GLfloat height = taille * 1.2;
        GLfloat depth = taille * 0.01;






        // FACE 1
        m_Vertices.push_back(ShapeVertex(glm::vec3(-width, -height, -depth), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0, 0)));
        m_Vertices.push_back(ShapeVertex(glm::vec3(width, -height, -depth), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1, 0)));
        m_Vertices.push_back(ShapeVertex(glm::vec3(width, height, -depth), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1, 1)));




        m_Vertices.push_back(ShapeVertex(glm::vec3(-width, -height, -depth), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0, 0)));
        m_Vertices.push_back(ShapeVertex(glm::vec3(-width, height, -depth), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0, 1)));
        m_Vertices.push_back(ShapeVertex(glm::vec3(width, height, -depth), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1, 1)));




           // FACE 2
        m_Vertices.push_back(ShapeVertex(glm::vec3(width, -height, taille), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0, 0)));
        m_Vertices.push_back(ShapeVertex(glm::vec3(width, -height, -taille), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1, 0)));
        m_Vertices.push_back(ShapeVertex(glm::vec3(width, height, -taille), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1, 1)));




        m_Vertices.push_back(ShapeVertex(glm::vec3(width, -height, depth), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0, 0)));
        m_Vertices.push_back(ShapeVertex(glm::vec3(width, height, depth), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0, 1)));
        m_Vertices.push_back(ShapeVertex(glm::vec3(width, height, -depth), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1, 1)));    




        // FACE 3
        m_Vertices.push_back(ShapeVertex(glm::vec3(-width, -height, depth), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0, 0)));
        m_Vertices.push_back(ShapeVertex(glm::vec3(width, -height, depth), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1, 0)));
        m_Vertices.push_back(ShapeVertex(glm::vec3(width, -height, -depth), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1, 1)));




        m_Vertices.push_back(ShapeVertex(glm::vec3(-width, -height, depth), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0, 0)));
        m_Vertices.push_back(ShapeVertex(glm::vec3(-width, -height, -depth), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0, 1)));
        m_Vertices.push_back(ShapeVertex(glm::vec3(width, -height, -depth), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1, 1)));                




        // FACE 4
        m_Vertices.push_back(ShapeVertex(glm::vec3(-width, -height, depth), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0, 0)));
        m_Vertices.push_back(ShapeVertex(glm::vec3(width, -height, depth), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1, 0)));
        m_Vertices.push_back(ShapeVertex(glm::vec3(width, height, depth), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1, 1)));




        m_Vertices.push_back(ShapeVertex(glm::vec3(-width, -height, depth), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0, 0)));
        m_Vertices.push_back(ShapeVertex(glm::vec3(-width, height, depth), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0, 1)));
        m_Vertices.push_back(ShapeVertex(glm::vec3(width, height, depth), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1, 1)));    




           // FACE 5
        m_Vertices.push_back(ShapeVertex(glm::vec3(-width, -height, -depth), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0, 0)));
        m_Vertices.push_back(ShapeVertex(glm::vec3(-width, -height, depth), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1, 0)));
        m_Vertices.push_back(ShapeVertex(glm::vec3(-width, height, depth), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1, 1)));




        m_Vertices.push_back(ShapeVertex(glm::vec3(-width, -height, -depth), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0, 0)));
        m_Vertices.push_back(ShapeVertex(glm::vec3(-width, height, -depth), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0, 1)));
        m_Vertices.push_back(ShapeVertex(glm::vec3(-width, height, depth), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1, 1)));    




           // FACE 6
        m_Vertices.push_back(ShapeVertex(glm::vec3(-width, height, depth), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0, 0)));
        m_Vertices.push_back(ShapeVertex(glm::vec3(width, height, depth), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1, 0)));
        m_Vertices.push_back(ShapeVertex(glm::vec3(width, height, -depth), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1, 1)));




        m_Vertices.push_back(ShapeVertex(glm::vec3(-width, height, depth), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0, 0)));
        m_Vertices.push_back(ShapeVertex(glm::vec3(-width, height, -depth), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0, 1)));
        m_Vertices.push_back(ShapeVertex(glm::vec3(width, height, -depth), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1, 1)));    




        m_nVertexCount = 36;




    }
}
