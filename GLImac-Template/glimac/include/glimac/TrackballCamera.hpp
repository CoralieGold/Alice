#pragma once

#include "common.hpp"

using namespace glimac;

class TrackballCamera {

private:
	float m_fDistance; // distance par rapport au centre de la scène
	float m_fAngleX; // angle effectué par la caméra autour de l'axe x de la scène
	float m_fAngleY; // angle effectué par la caméra autour de l'axe y de la scène
public:
	TrackballCamera();
	void moveFront(float delta);
	void rotateLeft(float degrees);
	void rotateUp(float degrees);
	glm::mat4 getViewMatrix() const;
};