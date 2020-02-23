#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object3D_tema2
{
	Mesh* CreatePlane(std::string name, glm::vec3 center_top, glm::vec3 center_bottom, 
		float r_top, float r_bottom, glm::vec3 color);
	Mesh* CreateSphere(std::string name, float radius, int sectors, 
		int stacks, glm::vec3 color);
	Mesh* CreateBox(std::string name, glm::vec3 leftBottomCorner, float width,
		float length, float z, glm::vec3 color);
	Mesh* Createtetrahedron(std::string name, float length, glm::vec3 color);
	Mesh* CreateRectangle(std::string name, float length, float width, glm::vec3 color);
	Mesh* CreateHeart(std::string name, float length, glm::vec3 color);
}