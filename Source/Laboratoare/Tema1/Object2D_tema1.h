#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object2D_tema1
{
	Mesh* CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
	Mesh* CreateCircle(std::string name, float cx, float cy, float r, glm::vec3 color);
	Mesh* CreatePasare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color);
	Mesh* CreatePasareBestiala(std::string name, float cx, float cy, float r, glm::vec3 color);
	Mesh* CreateTriangle(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color);
	Mesh* CreateLitera(std::string name, char litera, glm::vec3 leftBottomCorner, float length, glm::vec3 color);
	Mesh*CreateOrnament(std::string name, glm::vec3 leftBottomCorner,float length, glm::vec3 color);

}