#include "glimac/Functions2D.hpp"

glm::mat3 translate(float x, float y) {
    return glm::mat3(glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(x, y, 1));
}

glm::mat3 scale(float a) {
    return glm::mat3(glm::vec3(a, 0, 0), glm::vec3(0, a, 0), glm::vec3(0, 0, a));
}

glm::mat3 rotate(float a) {
    return glm::mat3(glm::vec3(cos(glm::radians(a)), sin(glm::radians(a)), 0), glm::vec3(-sin(glm::radians(a)), cos(glm::radians(a)), 0), glm::vec3(0, 0, 1));
}