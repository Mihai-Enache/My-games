#include "Object2D_tema1.h"

#include <Core/Engine.h>

Mesh* Object2D_tema1::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Object2D_tema1::CreateCircle(std::string name, float cx, float cy, float r, glm::vec3 color)
{
	std::vector<VertexFormat> vertices;
	for (int i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);//get the current angle

		float x = r * cosf(theta);//calculate the x component
		float y = r * sinf(theta);//calculate the y component

		vertices.push_back(VertexFormat(glm::vec3(x + cx, y + cy, 0), color));//output vertex
	}

	Mesh* circle = new Mesh(name);
	std::vector<unsigned short> indices;
	for (int i = 0; i < 120; i++) {
		indices.push_back(i);
		indices.push_back(i + 120);
		indices.push_back(i + 240);
	}

	circle->InitFromData(vertices, indices);
	return circle;
}

Mesh* Object2D_tema1::CreatePasare(std::string name, glm::vec3 leftBottomCorner, 
	float length, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color),
		VertexFormat(corner + glm::vec3(length * 0.7, length * 0.7, 0), glm::vec3(1, 1, 1)),
		VertexFormat(corner + glm::vec3(length * 0.8, length * 0.7, 0), glm::vec3(1, 1, 1)),
		VertexFormat(corner + glm::vec3(length * 0.8, length * 0.8, 0), glm::vec3(1, 1, 1)),
		VertexFormat(corner + glm::vec3(length * 0.7, length * 0.8, 0), glm::vec3(1, 1, 1)),
		VertexFormat(corner + glm::vec3(length, length * 0.5, 0), glm::vec3(1, 0.7, 0)),
		VertexFormat(corner + glm::vec3(length * 1.2, length * 0.5, 0), glm::vec3(1, 0.7, 0)),
		VertexFormat(corner + glm::vec3(length, length * 0.7, 0), glm::vec3(1, 0.7, 0)),
		VertexFormat(corner + glm::vec3(0, length * 0.2, 0), color),
		VertexFormat(corner + glm::vec3(-length * 0.2, length * 0.2, 0), color),
		VertexFormat(corner + glm::vec3(0, length * 0.4, 0), color),

	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 
		4, 5, 6,
		4, 6, 7,
		0, 1, 2, 
		0, 2, 3,
		8, 9, 10,
		11, 12, 13
	};

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Object2D_tema1::CreatePasareBestiala(std::string name, float cx, float cy, float r, glm::vec3 color)
{
	double vf_coadaX, vf_coadaY;
	double vf_ciocX, vf_ciocY;
	std::vector<VertexFormat> vertices;
	for (int i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);//get the current angle

		float x = r * cosf(theta);//calculate the x component
		float y = r * sinf(theta);//calculate the y component

		vertices.push_back(VertexFormat(glm::vec3(x + cx, y + cy, 0), color));//output vertex
		if (i == 180)
		{
			vf_coadaX = x + cx - r * 0.3;
			vf_coadaY = y + cy;
		}
		if (i == 0)
		{
			vf_ciocX = x + cx + r * 0.3;
			vf_ciocY = y + cy;
		}
	}
	
	double cx_eye = cx + r * 0.4;
	double cy_eye = cy + r * 0.4;

	for (int i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);//get the current angle

		double x = (r * 0.15) * cosf(theta);//calculate the x component
		double y = (r * 0.15) * sinf(theta);//calculate the y component	
		vertices.push_back(VertexFormat(glm::vec3(x + cx_eye, y + cy_eye, 0), glm::vec3(0, 0, 1)));//output vertex
	}

	vertices.push_back(VertexFormat(glm::vec3(vf_coadaX, vf_coadaY, 0), color));
	vertices.push_back(VertexFormat(glm::vec3(vf_ciocX, vf_ciocY, 0), glm::vec3(1, 0.7, 0)));

	Mesh* pasare = new Mesh(name);
	std::vector<unsigned short> indices;
	for (int i = 360; i < 480; i++) {
		indices.push_back(i);
		indices.push_back(i + 120);
		indices.push_back(i + 240);
	}
	for (int i = 0; i < 120; i++) {
		indices.push_back(i);
		indices.push_back(i + 120);
		indices.push_back(i + 240);
	}
	//creare Coada
	indices.push_back(720);
	indices.push_back(170);
	indices.push_back(230);

	//creare Cioc
	float theta = 2.0f * 3.1415926f * float(15) / float(360);
	float x = r * cosf(theta);
	float y = r * sinf(theta);
	vertices.push_back(VertexFormat(glm::vec3(x + cx, y + cy, 0), glm::vec3(1, 0.7, 0)));

	theta = 2.0f * 3.1415926f * float(340) / float(360);
	x = r * cosf(theta);
	y = r * sinf(theta);
	vertices.push_back(VertexFormat(glm::vec3(x + cx, y + cy, 0), glm::vec3(1, 0.7, 0)));
	//punctele pentru crearea ciocului
	indices.push_back(721);
	indices.push_back(722);
	indices.push_back(723);
	

	pasare->InitFromData(vertices, indices);
	return pasare;
}

Mesh* Object2D_tema1::CreateTriangle(std::string name, glm::vec3 leftBottomCorner,
	float length, glm::vec3 color) 
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner + glm::vec3(-length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(0, -1.4 * length, 0), color)
	};

	Mesh* triangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2};

	triangle->InitFromData(vertices, indices);
	return triangle;
}

Mesh* Object2D_tema1::CreateOrnament(std::string name, glm::vec3 leftBottomCorner,
	float length, glm::vec3 color)
{	//ornament folosit la obstacole
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length * 1.1, -length * 0.1, 0), color),
		VertexFormat(corner + glm::vec3(-length * 0.1, -length * 0.1, 0), color)
	};

	Mesh* ornament = new Mesh(name);
	std::vector<unsigned short> indices = { 
		0, 1, 2,
		0, 2, 3
	};

	ornament->InitFromData(vertices, indices);
	return ornament;
}

Mesh* Object2D_tema1::CreateLitera(std::string name, char litera, glm::vec3 leftBottomCorner,
	float length, glm::vec3 color)
{	//creaza litera s
	glm::vec3 corner = leftBottomCorner;
	if (litera == 's')
	{
		Mesh* litera = new Mesh(name);

		std::vector<VertexFormat> vertices =
		{
			VertexFormat(corner, color),
			VertexFormat(corner + glm::vec3(length * 0.2, 0, 0), color),
			VertexFormat(corner + glm::vec3(length * 0.2, length * 0.3, 0), color),
			VertexFormat(corner + glm::vec3(0, length * 0.3, 0), color),

			VertexFormat(corner, color),
			VertexFormat(corner + glm::vec3(length, 0, 0), color),
			VertexFormat(corner + glm::vec3(length, length * 0.1, 0), color),
			VertexFormat(corner + glm::vec3(0, length * 0.1, 0), color),

			VertexFormat(corner + glm::vec3(length * 0.8, 0, 0), color),
			VertexFormat(corner + glm::vec3(length, 0, 0), color),
			VertexFormat(corner + glm::vec3(length, length * 0.5, 0), color),
			VertexFormat(corner + glm::vec3(length * 0.8, length * 0.5, 0), color),

			VertexFormat(corner + glm::vec3(0,  length * 0.4, 0), color),
			VertexFormat(corner + glm::vec3(length, length * 0.4, 0), color),
			VertexFormat(corner + glm::vec3(length, length * 0.5, 0), color),
			VertexFormat(corner + glm::vec3(0, length * 0.5, 0), color),

			VertexFormat(corner + glm::vec3(0,  length * 0.4, 0), color),
			VertexFormat(corner + glm::vec3(length * 0.2, length * 0.4, 0), color),
			VertexFormat(corner + glm::vec3(length * 0.2, length, 0), color),
			VertexFormat(corner + glm::vec3(0, length, 0), color),

			VertexFormat(corner + glm::vec3(0,  length * 0.9, 0), color),
			VertexFormat(corner + glm::vec3(length, length * 0.9, 0), color),
			VertexFormat(corner + glm::vec3(length, length, 0), color),
			VertexFormat(corner + glm::vec3(0, length, 0), color),

			VertexFormat(corner + glm::vec3(length * 0.8,  length * 0.7, 0), color),
			VertexFormat(corner + glm::vec3(length, length * 0.7, 0), color),
			VertexFormat(corner + glm::vec3(length, length, 0), color),
			VertexFormat(corner + glm::vec3(length * 0.8, length, 0), color),
		};

		std::vector<unsigned short> indices = {
			0, 1, 2,
			0, 2, 3,
			4, 5, 6,
			4, 6, 7,
			8, 9, 10,
			8, 10, 11,
			12, 13, 14,
			12, 14, 15,
			16, 17, 18,
			16, 18, 19,
			20, 21, 22,
			20, 22, 23,
			24, 25, 26,
			24, 26, 27
		};
		litera->InitFromData(vertices, indices);
		return litera;
	}

	return new Mesh(name);
}

