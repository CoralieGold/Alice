#ifndef DEF_VERTEX2DUV
#define DEF_VERTEX2DUV

struct Vertex2DUV {
    glm::vec2 positionXY;
    glm::vec2 coordTextUV;

    Vertex2DUV() {}
    Vertex2DUV(glm::vec2 n_positionXY, glm::vec2 n_coordTextUV) : positionXY(n_positionXY), coordTextUV(n_coordTextUV) {}
};

#endif