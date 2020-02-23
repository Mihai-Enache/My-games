#include "Object3D_tema2.h"

#include <Core/Engine.h>

const float PI = 3.14159f;

Mesh* Object3D_tema2::CreatePlane(std::string name, glm::vec3 center_base,
	glm::vec3 center_top, float r_base, float r_top, glm::vec3 color)
{
	std::vector<VertexFormat> vertices;

	//base
	for (int i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		float y = r_base * cosf(theta);
		float z = r_base * sinf(theta);
		vertices.push_back(VertexFormat(center_base + glm::vec3(0, y, z), color));
	}

	//top
	for (int i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		float y = r_top * cosf(theta);
		float z = r_top * sinf(theta);
		vertices.push_back(VertexFormat(center_top + glm::vec3(0, y, z), color));
	}

	Mesh* plane = new Mesh(name);
	std::vector<unsigned short> indices;
	for (int i = 0; i < 120; i++) {
		indices.push_back(i);
		indices.push_back(i + 120);
		indices.push_back(i + 240);
	}

	for (int i = 360; i < 480; i++) {
		indices.push_back(i);
		indices.push_back(i + 120);
		indices.push_back(i + 240);
	}

	for (int i = 0; i < 360; i++) {
		indices.push_back(i);
		indices.push_back(i + 360);
		if(i != 359)
			indices.push_back(i + 1);
		else
			indices.push_back(0);
		indices.push_back(i + 360);
		if (i != 359) {
			indices.push_back(i + 1);
			indices.push_back(i + 361);
		}
		else
		{
			indices.push_back(0);
			indices.push_back(360);
		}	
	}

	plane->InitFromData(vertices, indices);
	return plane;
}

Mesh * Object3D_tema2::CreateSphere(std::string name, float radius, int sectors, int stacks, glm::vec3 color)
{
	std::vector<VertexFormat> vertices;

	float x, y, z, xy;                              // vertex position

	float sectorStep = 2 * PI / sectors;
	float stackStep = PI / stacks;
	float sectorAngle, stackAngle;

	for (int i = 0; i <= stacks; ++i)
	{
		stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
		xy = radius * cosf(stackAngle);             // r * cos(u)
		z = radius * sinf(stackAngle);              // r * sin(u)

		for (int j = 0; j <= sectors; ++j)
		{
			sectorAngle = j * sectorStep;           // starting from 0 to 2pi

			// vertex position (x, y, z)
			x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
			y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
			vertices.push_back(VertexFormat(glm::vec3(x, y, z), color));
		}
	}

	Mesh* sphere = new Mesh(name);
	std::vector<unsigned short> indices;
	int k1, k2;
	for (int i = 0; i < stacks; ++i)
	{
		k1 = i * (sectors + 1);     // beginning of current stack
		k2 = k1 + sectors + 1;      // beginning of next stack

		for (int j = 0; j < sectors; ++j, ++k1, ++k2)
		{
			// 2 triangles per sector excluding first and last stacks
			// k1 => k2 => k1+1
			if (i != 0)
			{
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}

			// k1+1 => k2 => k2+1
			if (i != (stacks - 1))
			{
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
			}
		}
	}

	sphere->InitFromData(vertices, indices);
	return sphere;
}

Mesh * Object3D_tema2::CreateBox(std::string name, glm::vec3 leftBottomCorner, float width, float length, float z, glm::vec3 color)
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

Mesh * Object3D_tema2::Createtetrahedron(std::string name,float length, glm::vec3 color)
{
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0, length, 0), color),
		VertexFormat(glm::vec3(0, 0, length / 2), color),
		VertexFormat(glm::vec3(length/2, 0, -length/2), color),
		VertexFormat(glm::vec3(-length/2, 0, -length/2), color)
	};

	Mesh* mesh = new Mesh(name);
	std::vector<unsigned short> indices = {
		0, 1, 2,
		0, 2, 3,
		0, 1, 3,
		1, 2, 3 
	};

	mesh->InitFromData(vertices, indices);
	return mesh;
}

Mesh * Object3D_tema2::CreateRectangle(std::string name, float length, float width, glm::vec3 color)
{
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(length, 0, 0), color),
		VertexFormat(glm::vec3(length, width, 0), color),
		VertexFormat(glm::vec3(0, width, 0), color)
	};

	Mesh* mesh = new Mesh(name);
	std::vector<unsigned short> indices = {
		0, 1, 2,
		0, 2, 3
	};

	mesh->InitFromData(vertices, indices);
	return mesh;
}

Mesh * Object3D_tema2::CreateHeart(std::string name, float length, glm::vec3 color)
{
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(-length * 0.5f, length * 0.8f, 0), color),
		VertexFormat(glm::vec3(-length * 0.25f, length, 0), color),
		VertexFormat(glm::vec3(0, length * 0.8f, 0), color),
		VertexFormat(glm::vec3(length * 0.25f, length, 0), color),
		VertexFormat(glm::vec3(length * 0.5f, length * 0.8f, 0), color),
	};

	Mesh* mesh = new Mesh(name);
	std::vector<unsigned short> indices = {
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		0, 4, 5
	};

	mesh->InitFromData(vertices, indices);
	return mesh;
}

