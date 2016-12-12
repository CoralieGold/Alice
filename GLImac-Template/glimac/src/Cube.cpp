#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "glimac/Sphere.hpp"
#include "glimac/Cube.hpp"

namespace glimac {
	//void Cube::build(GLfloat taille) {
		//Sphere sphere(taille, 3, 2);

		//std::vector<ShapeVertex> verticesTmp(sphere.getDataPointer(), sphere.getDataPointer() + 36);
		//m_Vertices = verticesTmp;
		//m_nVertexCount = sphere.getVertexCount();

		// taille /2;
		// /*for(int i = 0; i < 108; i++) {
		// 	m_Vertices[i].position = verticesTmp[i];
		// 	m_Vertices[i].normal = ;
		// 	m_Vertices[i].texCoords = 
		// }*/

		// GLfloat rcpLat = 1.f / discLat, rcpLong = 1.f / discLong;
  //   	GLfloat dPhi = 2 * glm::pi<float>() * rcpLat, dTheta = glm::pi<float>() * rcpLong;

		// std::vector<ShapeVertex> data;
		// // ou i < 108
	 //    for(GLsizei i = 0; i < 36; ++i) {
	 //        ShapeVertex vertex;
	            
	 //        vertex.texCoords.x = i * rcpLat;
	 //        vertex.texCoords.y = 1.f - j * rcpLong;

	 //        vertex.normal.x = sin(i * dPhi) * cosTheta;
	 //        vertex.normal.y = sinTheta;
	 //        vertex.normal.z = cos(i * dPhi) * cosTheta;
	            
	 //        vertex.position = r * vertex.normal;
	            
	 //        data.push_back(vertex);
	 //    }

	 
	//}


	Cube::Cube(GLfloat taille) {
		// Division de la taille


	    taille /= 2;

	    // FACE 1
	    m_Vertices.push_back(ShapeVertex(glm::vec3(-taille, -taille, -taille), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.000059f, 1.0f-0.000004f)));
	    m_Vertices.push_back(ShapeVertex(glm::vec3(taille, -taille, -taille), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.000103f, 1.0f-0.336048f)));
	    m_Vertices.push_back(ShapeVertex(glm::vec3(taille, taille, -taille), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.335973f, 1.0f-0.335903f)));

	    m_Vertices.push_back(ShapeVertex(glm::vec3(-taille, -taille, -taille), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.000023f, 1.0f-0.000013f)));
	    m_Vertices.push_back(ShapeVertex(glm::vec3(-taille, taille, -taille), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.667979f, 1.0f-0.335851f)));
	    m_Vertices.push_back(ShapeVertex(glm::vec3(taille, taille, -taille), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.999958f, 1.0f-0.336064f)));

	   	// FACE 2
	    m_Vertices.push_back(ShapeVertex(glm::vec3(taille, -taille, taille), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.667979f, 1.0f-0.335851f)));
	    m_Vertices.push_back(ShapeVertex(glm::vec3(taille, -taille, -taille), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.336024f, 1.0f-0.671877f)));
	    m_Vertices.push_back(ShapeVertex(glm::vec3(taille, taille, -taille), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.667969f, 1.0f-0.671889f)));

		m_Vertices.push_back(ShapeVertex(glm::vec3(taille, -taille, taille), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.000023f, 1.0f-0.000013f)));
	    m_Vertices.push_back(ShapeVertex(glm::vec3(taille, taille, taille), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.668104f, 1.0f-0.000013f)));
	    m_Vertices.push_back(ShapeVertex(glm::vec3(taille, taille, -taille), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.667979f, 1.0f-0.335851f)));	

		// FACE 3
	    m_Vertices.push_back(ShapeVertex(glm::vec3(-taille, -taille, taille), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.000059f, 1.0f-0.000004f)));
	    m_Vertices.push_back(ShapeVertex(glm::vec3(taille, -taille, taille), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.335973f, 1.0f-0.335903f)));
	    m_Vertices.push_back(ShapeVertex(glm::vec3(taille, -taille, -taille), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.336098f, 1.0f-0.000071f)));

		m_Vertices.push_back(ShapeVertex(glm::vec3(-taille, -taille, taille), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.667979f, 1.0f-0.335851f)));
	    m_Vertices.push_back(ShapeVertex(glm::vec3(-taille, -taille, -taille), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.335973f, 1.0f-0.335903f)));
	    m_Vertices.push_back(ShapeVertex(glm::vec3(taille, -taille, -taille), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.336024f, 1.0f-0.671877f)));		        

		// FACE 4
	    m_Vertices.push_back(ShapeVertex(glm::vec3(-taille, -taille, taille), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.000004f, 1.0f-0.671847f)));
	    m_Vertices.push_back(ShapeVertex(glm::vec3(taille, -taille, taille), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.999958f, 1.0f-0.336064f)));
	    m_Vertices.push_back(ShapeVertex(glm::vec3(taille, taille, taille), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.667979f, 1.0f-0.335851f)));

		m_Vertices.push_back(ShapeVertex(glm::vec3(-taille, -taille, taille), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.668104f, 1.0f-0.000013f)));
	    m_Vertices.push_back(ShapeVertex(glm::vec3(-taille, taille, taille), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.335973f, 1.0f-0.335903f)));
	    m_Vertices.push_back(ShapeVertex(glm::vec3(taille, taille, taille), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.667979f, 1.0f-0.335851f)));	

	   	// FACE 5
	    m_Vertices.push_back(ShapeVertex(glm::vec3(-taille, -taille, -taille), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.335973f, 1.0f-0.335903f)));
	    m_Vertices.push_back(ShapeVertex(glm::vec3(-taille, -taille, taille), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.668104f, 1.0f-0.000013f)));
	    m_Vertices.push_back(ShapeVertex(glm::vec3(-taille, taille, taille), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.336098f, 1.0f-0.000071f)));

		m_Vertices.push_back(ShapeVertex(glm::vec3(-taille, -taille, -taille), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.000103f, 1.0f-0.336048f)));
	    m_Vertices.push_back(ShapeVertex(glm::vec3(-taille, taille, -taille), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.000004f, 1.0f-0.671870f)));
	    m_Vertices.push_back(ShapeVertex(glm::vec3(-taille, taille, taille), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.336024f, 1.0f-0.671877f)));	

	   	// FACE 6
	    m_Vertices.push_back(ShapeVertex(glm::vec3(-taille, taille, taille), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.000103f, 1.0f-0.336048f)));
	    m_Vertices.push_back(ShapeVertex(glm::vec3(taille, taille, taille), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.336024f, 1.0f-0.671877f)));
	    m_Vertices.push_back(ShapeVertex(glm::vec3(taille, taille, -taille), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.335973f, 1.0f-0.335903f)));

		m_Vertices.push_back(ShapeVertex(glm::vec3(-taille, taille, taille), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.667969f, 1.0f-0.671889f)));
	    m_Vertices.push_back(ShapeVertex(glm::vec3(-taille, taille, -taille), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.000004f, 1.0f-0.671847f)));
	    m_Vertices.push_back(ShapeVertex(glm::vec3(taille, taille, -taille), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.667979f, 1.0f-0.335851f)));	

	    m_nVertexCount = 36;

	}
}