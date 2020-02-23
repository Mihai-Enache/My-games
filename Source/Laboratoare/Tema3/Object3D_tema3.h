#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object3D_tema3
{
	Mesh* CreateSquare(std::string name, int NrVertices);
	Mesh* CreateWorm(std::string name, glm::vec3 color);
	Mesh* CreateBox(std::string name, glm::vec3 leftBottomCorner, float width,
		float length, float z, glm::vec3 color);
}