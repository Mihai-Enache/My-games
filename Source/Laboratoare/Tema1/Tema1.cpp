#include "Tema1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D_tema1.h"
#include "Object2D_tema1.h"
#include <time.h>
#include <cmath>

using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = 100;

	float cx = corner.x + squareSide / 2;
	float cy = corner.y + squareSide / 2;

	// initiliazare pasi de translatie si culori pentru stalpi
	int i;
	for (i = 0; i <= 4; i++)
	{
		translateX[i] = (1280 + 100) / 4 * (float)i + 1000;
		culoare[i] = 1;
	}
	translateY = 0;

	// initializare factor de modificare pe Oy pentru pasare 
	pasareY = 0;
	sus = 0;

	// initializare scaleY (factor de scalare pentru Oy 
	//pentru a face aripa pasarii sa se miste)
	scaleY = 1;
	
	//initializare factori de scalare pe Oy pentru a face obstacole de
	//dimensiuni diferite
	srand(time(NULL));
	for (i = 0; i <= 6; i++)
	{
		scaleY_obstacol[i][0] = rand() % 4 + 0.01 * (rand() % 70);
		scaleY_obstacol[i][1] = 4.7 - scaleY_obstacol[i][0];
	}
	
	//creare obiecte
	Mesh* square1 = Object2D_tema1::CreateSquare("square1", corner, squareSide, glm::vec3(1, 0, 0), true);
	AddMeshToList(square1);

	Mesh* square2 = Object2D_tema1::CreateSquare("square2", corner, squareSide, glm::vec3(0, 0, 1), true);
	AddMeshToList(square2);

	Mesh* square3 = Object2D_tema1::CreateSquare("square3", corner, squareSide, glm::vec3(0, 1, 0), true);
	AddMeshToList(square3);

	Mesh* square4 = Object2D_tema1::CreateSquare("square4", corner, squareSide, glm::vec3(1, 1, 1));
	AddMeshToList(square4);

	Mesh* circle1 = Object2D_tema1::CreateCircle("circle1", 0, 0, 50, glm::vec3(1, 1, 0));
	AddMeshToList(circle1);

	Mesh* pasare1 = Object2D_tema1::CreatePasare("pasare1", corner, squareSide, glm::vec3(0, 0, 1));
	AddMeshToList(pasare1);

	Mesh* pasare2 = Object2D_tema1::CreatePasareBestiala("pasare2", 0, 0, 50, glm::vec3(1, 1, 0));
	AddMeshToList(pasare2);

	Mesh* triangle1 = Object2D_tema1::CreateTriangle("triangle1", corner, 25, glm::vec3(0.85, 0.85, 0));
	AddMeshToList(triangle1);

	Mesh* litera1 = Object2D_tema1::CreateLitera("s", 's', corner, 50, glm::vec3(1, 1, 1));
	AddMeshToList(litera1);

	Mesh* ornament1 = Object2D_tema1::CreateOrnament("ornament1", corner, 100, glm::vec3(0.4, 0.4, 0.4));
	AddMeshToList(ornament1);
}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor((GLclampf)0.7, (GLclampf)0.7, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
	if (coliziune == 1) {//cazul in care jocul s-a terminat
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(650, 340);
		RenderMesh2D(meshes["s"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(-25, -25);
		modelMatrix *= Transform2D::Translate(650, 340);
		RenderMesh2D(meshes["square4"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(-25, -25);
		modelMatrix *= Transform2D::Translate(650, 340);
		RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);
		return;
	}
	//modific factorul de scalare pentru aripa
	if (scaleY >= -1 && ok == 0)
		scaleY -= (float)0.04;
	else
	{
		ok = 1;
	}
	if (scaleY <= 1 && ok == 1)
		scaleY += (float)0.04;
	else
	{
		ok = 0;
	}

	//realizez miscarea pasarii
	if (sus > 0)
	{
		pasareY += 10;
		sus -= 10;
	}

	//creare aripa
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(300, 300 + pasareY);
	if (sus > 0)
		modelMatrix *= Transform2D::Rotate(0.52);
	else
		modelMatrix *= Transform2D::Rotate(-0.52);
	modelMatrix *= Transform2D::Scale(1, scaleY);
	RenderMesh2D(meshes["triangle1"], shaders["VertexColor"], modelMatrix);
	
	//creare pasare
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(300, 300 + pasareY);
	if (sus > 0)
		modelMatrix *= Transform2D::Rotate(0.52);
	else
		modelMatrix *= Transform2D::Rotate(-0.52);
	RenderMesh2D(meshes["pasare2"], shaders["VertexColor"], modelMatrix);

	//creare suprafata pentru pamant
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Scale(12.8, 0.1);
	RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);

	//verific coliziunile cu pamantul
	if ((300 - 50 + pasareY) <= 10)
	{
		coliziune = 1;
		cout << "YUPPPIII ai facut " << puncte << " puncte !\n";
		return;
	}

	int i;
	//crearea obstacolelor si verificarea coliziunilor cu ele
	//creez random valori pentru inaltimile si culorile obstacolelor 
	for (i = 1; i <= 4; i++) {
		if (translateX[i] >= 1279 && translateX[i] <= 1280)
			stalpi++;
		if (translateX[i] >= - 100)
			translateX[i] -= 2;
		else
		{
			translateX[i] = 1280;
			scaleY_obstacol[i][0] = rand() % 4 + 0.01 * (rand() % 70);
			scaleY_obstacol[i][1] = 4.7 - scaleY_obstacol[i][0];
			if (culoare[i] == 1)
				culoare[i] = 2;
			else
				culoare[i] = 1;
			float R, G, B;
			srand(time(NULL));
			R = rand() % 100 * 0.01;
			G = rand() % 100 * 0.01;
			B = rand() % 100 * 0.01
				;
			glm::vec3 corner = glm::vec3(0, 0, 0);
			float squareSide = 100;
			if (stalpi % 4 == 0) {
				if (culoare[i] == 1)
				{
					Mesh* square1 = Object2D_tema1::CreateSquare("square1", corner, squareSide,
						glm::vec3(R, G, B), true);
					AddMeshToList(square1);
				}
				else
				{
					Mesh* square2 = Object2D_tema1::CreateSquare("square2", corner, squareSide,
						glm::vec3(R, G, B), true);
					AddMeshToList(square2);
				}
			}
		}

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(translateX[i],
			(720 + 10 - 100 * scaleY_obstacol[i][0]));
		RenderMesh2D(meshes["ornament1"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Scale(1, scaleY_obstacol[i][0]);
		modelMatrix *= Transform2D::Translate(translateX[i], 
			(720 - 100 * scaleY_obstacol[i][0]) / scaleY_obstacol[i][0]);
		if(culoare[i] == 1)
			RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
		else
			RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Scale(1, -1);
		modelMatrix *= Transform2D::Translate(translateX[i], -(scaleY_obstacol[i][1] * 100));
		RenderMesh2D(meshes["ornament1"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Scale(1, scaleY_obstacol[i][1]);
		modelMatrix *= Transform2D::Translate(translateX[i], 0);
		if (culoare[i] == 1)
			RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
		else
			RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
		
		if (translateX[i] >= 150 && translateX[i] <= 350) {
			if ((300 - 50 + pasareY) <= scaleY_obstacol[i][1] * 100) {
				coliziune = 1;
				cout << "YUPPPIII ai facut " << puncte << " puncte !\n";
			}
			if ((300 + 50 + pasareY) >= (720 - scaleY_obstacol[i][0] * 100)) {
				coliziune = 1;
				cout << "YUPPPIII ai facut " << puncte << " puncte !\n";
			}
		}

		//calculul punctajului
		if (translateX[i] <= 150 && translateX[i] >= 149)
		{
			puncte++;
			printf("Puncte %d\n", puncte);
		}
	}
	
	//viteza de cadere a pasarii
	pasareY -= 4;
}

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{

}

void Tema1::OnKeyPress(int key, int mods)
{
	//dau comanda ca pasarea sa se ridice
	if (key == GLFW_KEY_SPACE) {
		sus = 150;
	}

	//dau comanda de restart pentru joc
	if(coliziune == 1)
		if (key == GLFW_KEY_S || key == GLFW_KEY_ENTER) {
			stalpi = 0;
			coliziune = 0;
			pasareY = 0;
			puncte = 0;
			sus = 0;
			ok = 0;
			scaleY = 1;
			int i;
			for (i = 0; i <= 4; i++) {
				translateX[i] = (1280 + 100) / 4 * (float)i + 1000;
				culoare[i] = 1;
			}
			srand(time(NULL));
			for (i = 0; i <= 6; i++) {
				scaleY_obstacol[i][0] = rand() % 4 + 0.01 * (rand() % 70);
				scaleY_obstacol[i][1] = 4.7 - scaleY_obstacol[i][0];
			}
		}
}

void Tema1::OnKeyRelease(int key, int mods)
{
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
