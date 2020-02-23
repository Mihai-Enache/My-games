#include "Object3D_tema3.h"

#include <Core/Engine.h>

Mesh * Object3D_tema3::CreateSquare(std::string name, int NrVertices)
{
	std::vector<glm::vec3> vertices;
	int i, j;
	float margine = -0.1f * NrVertices / 2;
	for (i = 0; i < NrVertices; i++)
		for (j = 0; j < NrVertices; j++)
		{
			vertices.push_back(glm::vec3(margine + i * 0.1f, 0, margine + j * 0.1f));
		}

	std::vector<glm::vec3> normals;
	for (i = 0; i < NrVertices; i++)
		for (j = 0; j < NrVertices; j++)
		{
			normals.push_back(glm::vec3(0, 1, 1));
		}

	std::vector<glm::vec2> textureCoords;
	float maxim = (float)NrVertices - 1.0f;
	for (i = 0; i < NrVertices; i++)
		for (j = 0; j < NrVertices; j++)
		{
			textureCoords.push_back(glm::vec2((float)i / maxim, (float)j / maxim));
		}

	std::vector<unsigned short> indices;
	for (i = 0; i < NrVertices - 1; i++)
		for (j = 0; j < NrVertices - 1; j++)
		{
			indices.push_back(i * NrVertices + j);
			indices.push_back((i + 1) * NrVertices + j);
			indices.push_back((i + 1) * NrVertices + j + 1);
			indices.push_back((i + 1) * NrVertices + j + 1);
			indices.push_back(i * NrVertices + j + 1);
			indices.push_back(i * NrVertices + j);
		}

	Mesh* mesh = new Mesh(name);
	mesh->InitFromData(vertices, normals, textureCoords, indices);
	return mesh;
}

Mesh * Object3D_tema3::CreateWorm(std::string name, glm::vec3 color)
{
	std::vector<VertexFormat> vertices;
	{
		vertices.push_back(VertexFormat(glm::vec3(0, 0.2f, 0), color));
		vertices.push_back(VertexFormat(glm::vec3(0.2f, 0.3f, 0.2f), color));
		vertices.push_back(VertexFormat(glm::vec3(0.2f, 0.3f, -0.2f), color));
		vertices.push_back(VertexFormat(glm::vec3(0.2f, 0, 0), color));
		vertices.push_back(VertexFormat(glm::vec3(0.8f, 0.3f, 0.2f), color));
		vertices.push_back(VertexFormat(glm::vec3(0.8f, 0.3f, -0.2f), color));
		vertices.push_back(VertexFormat(glm::vec3(0.8f, 0, 0), color));
	}

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		0, 1, 3,
		0, 2, 3,
		1, 2, 3,
		1, 4, 5,
		1, 2, 5,
		1, 4, 6,
		1, 3, 6,
		2, 5, 6,
		2, 3, 6
	};

	Mesh* mesh = new Mesh(name);
	mesh->InitFromData(vertices, indices);
	return mesh;
}

Mesh * Object3D_tema3::CreateBox(std::string name, glm::vec3 leftBottomCorner, float width, float length, float z, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(width, 0, 0), color),
		VertexFormat(corner + glm::vec3(width, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color),
		VertexFormat(corner + glm::vec3(0, 0, z), color),
		VertexFormat(corner + glm::vec3(width, 0, z), color),
		VertexFormat(corner + glm::vec3(width, length, z), color),
		VertexFormat(corner + glm::vec3(0, length, z), color)
	};

	Mesh* box = new Mesh(name);
	std::vector<unsigned short> indices = {
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		3, 4, 7,
		4, 5, 7,
		5, 6, 7,
		2, 3, 6,
		3, 6, 7,
		1, 2, 5,
		2, 5, 6,
		0, 1, 4,
		1, 4, 5
	};

	box->InitFromData(vertices, indices);
	return box;
}
