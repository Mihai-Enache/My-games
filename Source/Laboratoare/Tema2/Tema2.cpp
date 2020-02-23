#include "Tema2.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>
#include "Transform3D.h"
#include "Object3D_tema2.h"
#include <time.h>
#include <cmath>

using namespace std;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{
	
	personCamera = 3;
	camera = new Tema::Camera();
	camera->Set(glm::vec3(0, 0.0f, 7.2f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	projectionMatrix = glm::ortho(-12.8f, 12.8f, -7.2f, 7.2f, -12.0f, 12.0f);
	Mesh* mesh = Object3D_tema2::CreatePlane("back", 
		glm::vec3(0, 0, 0), glm::vec3(0.5, 0, 0), 0.1f, 0.1f, glm::vec3(1, 1, 0));
	AddMeshToList(mesh);

	mesh = Object3D_tema2::CreatePlane("connection",
		glm::vec3(0, 0, 0), glm::vec3(0.3, 0.1, 0), 0.1f, 0.2f, glm::vec3(1, 1, 0));
	AddMeshToList(mesh);

	mesh = Object3D_tema2::CreatePlane("body",
		glm::vec3(0, 0.1, 0), glm::vec3(0.5, 0.1, 0), 0.2f, 0.2f, glm::vec3(1, 1, 0));
	AddMeshToList(mesh);

	mesh = Object3D_tema2::CreatePlane("front",
		glm::vec3(0, 0.1, 0), glm::vec3(0.2, 0.1, 0), 0.2f, 0.2f, glm::vec3(1, 1, 0.8));
	AddMeshToList(mesh);

	mesh = Object3D_tema2::CreatePlane("airscrew",
		glm::vec3(0, 0.1, 0), glm::vec3(0.1, 0.1, 0), 0.1f, 0.1f, glm::vec3(0, 0, 1));
	AddMeshToList(mesh);

	mesh = Object3D_tema2::CreatePlane("sea",
		glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), 1.0f, 1.0f, glm::vec3(0.3, 0.3, 1));
	AddMeshToList(mesh);
	
	mesh = Object3D_tema2::CreateBox("tail", glm::vec3(0, 0, 0), 0.1f,
		0.4f, 0.1f, glm::vec3(0.8, 0.8, 0.1));
	AddMeshToList(mesh);

	mesh = Object3D_tema2::CreateBox("wing", glm::vec3(0, 0, 0), 0.4f,
		0.1f, 1.0f, glm::vec3(0.8, 0.8, 0.1));
	AddMeshToList(mesh);

	mesh = Object3D_tema2::CreateBox("blade", glm::vec3(0, 0, 0), 0.1f,
		0.02f, 0.4f, glm::vec3(0.8, 0.8, 0.8));
	AddMeshToList(mesh);

	mesh = Object3D_tema2::CreateBox("cloud1", glm::vec3(0, 0, 0), 1.0f,
		1.0f, 1.0f, glm::vec3(0.9, 0.9, 1));
	AddMeshToList(mesh);

	mesh = Object3D_tema2::CreateBox("cloud2", glm::vec3(0, 0, 0), 1.0f,
		1.0f, 1.0f, glm::vec3(0.95, 0.95, 1));
	AddMeshToList(mesh);

	mesh = Object3D_tema2::CreateBox("cloud3", glm::vec3(0, 0, 0), 1.0f,
		1.0f, 1.0f, glm::vec3(0.92, 0.92, 1));
	AddMeshToList(mesh);

	mesh = Object3D_tema2::Createtetrahedron("fuel", 0.3f, glm::vec3(0, 0.80, 0.81));
	AddMeshToList(mesh);

	mesh = Object3D_tema2::CreateSphere("obstacle", 0.3f, 8, 4, glm::vec3(0.45, 0, 0));
	AddMeshToList(mesh);

	mesh = Object3D_tema2::CreateRectangle("tankBack", 1.0f, 0.2f, glm::vec3(0, 0, 0));
	AddMeshToList(mesh);

	mesh = Object3D_tema2::CreateRectangle("tankFront", 1.0f, 0.2f, glm::vec3(1, 1, 1));
	AddMeshToList(mesh);

	mesh = Object3D_tema2::CreateHeart("heart", 1.0f, glm::vec3(0.8, 0, 0));
	AddMeshToList(mesh);

	//viteza
	speed = 1;
	timeSpeed = 0;

	// initialize angularSteps
	angularStep_AirScrew = 0;
	angularStep_Cloud1 = 0;
	angularStep_Cloud2 = 0;
	angularStep_Objects = 0;

	translatePlaneY = 3.6f;

	//initialize values for Clouds
	nrClouds = 4;
	for(int i = 0; i < nrClouds; i++)
		distancesCloud[i] = 23.0f;
	translateCloud[0] = 12.8f;
	for (int i = 1; i < nrClouds; i++)
		translateCloud[i] = translateCloud[i - 1] + 12.8f;
	srand(time(NULL));
	for (int i = 1; i < nrClouds; i++)
		yCloud[i] = rand() % 6 + 0.1f * (rand() % 10);

	//initialize values for objects
	nrObjects = 4;
	for (int i = 0; i < nrObjects; i++)
		distanceObjectX[i] = 25.0f;
	translateObjectX[0] = 4.0f;
	for (int i = 1; i < nrObjects; i++)
		translateObjectX[i] = translateObjectX[i - 1] + 12.8f;
	for (int i = 0; i < nrObjects; i++)
		yObject[i] = rand() % 5 + 0.1f * (rand() % 10);
	for (int i = 0; i < nrObjects; i++) {
		typeObject[i] = rand() % 2;
	}
	for (int i = 1; i < nrObjects; i++) {
		nrFuels[i] = 1;
		decided_Nr[i] = 0;
		for (int j = 0; j < 8; j++)
			yDif[i][j] = 0;
	}
	
	for(int i = 0; i < nrObjects; i++)
		for (int j = 0; j < 8; j++) {
			hit[i][j] = 0;
		}

	for (int i = 0; i < nrObjects; i++) {
		obstacleCreated[i] = 1;
	}

	tankFuel = 2000;

	nrHearts = 3;
}

void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor((GLclampf)0.7, (GLclampf)0.7, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->GetResolution();

	if (nrHearts > 0 && tankFuel > 0) {
		if (personCamera == 3) {
			camera->Set(glm::vec3(0, 0, 7.2f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
			projectionMatrix = glm::ortho(-12.8f, 12.8f, -7.2f, 7.2f, -12.0f, 12.0f);
		}
		else {
			camera->Set(glm::vec3(0, 0.5f + translatePlaneY, 0),
				glm::vec3(1.0f, 0.5f + translatePlaneY, 0), glm::vec3(0, 1, 0));
			projectionMatrix = glm::perspective(RADIANS(90), window->props.aspectRatio,
				0.01f, 100.0f);
		}

		//start create hearts for lives
		for (int i = 0; i < nrHearts; i++) {
			if (personCamera == 3) {
				modelMatrix = glm::mat4(1);
				modelMatrix *= Transform3D::Translate(-12.0f + i * 1.4f, 6.0f, 0.0f);
				RenderMesh(meshes["heart"], shaders["VertexColor"], modelMatrix);
			}
			else{
				modelMatrix = glm::mat4(1);
				modelMatrix *= Transform3D::Translate(7.2f, 6.5f + translatePlaneY,
					-12.0f + i * 1.4f);
				modelMatrix *= Transform3D::RotateOY(1.5707f);
				RenderMesh(meshes["heart"], shaders["VertexColor"], modelMatrix);
			}
		}
		//end create hearts

		//start create tank rectangle
		if (personCamera == 3) {
			modelMatrix = glm::mat4(1);
			modelMatrix *= Transform3D::Translate(12.5f, 6.8f, 0.0f);
			modelMatrix *= Transform3D::Scale(-5.0f, -3.0f, 1.0f);
			modelMatrix *= Transform3D::Scale(tankFuel * 0.0005f, 1.0f, 1.0f);
			RenderMesh(meshes["tankFront"], shaders["VertexColor"], modelMatrix);

			modelMatrix = glm::mat4(1);
			modelMatrix *= Transform3D::Translate(7.4f, 6.1f, 0.0f);
			modelMatrix *= Transform3D::Scale(5.2f, 4.0f, 1.0f);
			RenderMesh(meshes["tankBack"], shaders["VertexColor"], modelMatrix);
		}
		else {
			modelMatrix = glm::mat4(1);
			modelMatrix *= Transform3D::Translate(6.9f, 6.5f + translatePlaneY, 12.0f);
			modelMatrix *= Transform3D::RotateOY(1.5707f);
			modelMatrix *= Transform3D::Scale(5.0f, 3.0f, 1.0f);
			modelMatrix *= Transform3D::Scale(tankFuel * 0.0005f, 1.0f, 1.0f);
			RenderMesh(meshes["tankFront"], shaders["VertexColor"], modelMatrix);

			modelMatrix = glm::mat4(1);
			modelMatrix *= Transform3D::Translate(6.9f, 6.4f + translatePlaneY, 12.1f);
			modelMatrix *= Transform3D::RotateOY(1.5707f);
			modelMatrix *= Transform3D::Scale(5.2f, 4.0f, 1.0f);
			RenderMesh(meshes["tankBack"], shaders["VertexColor"], modelMatrix);
		}

		timeSpeed++;
		if (timeSpeed % 1000 == 0)
			speed += 1;
		if (tankFuel > 0)
			tankFuel -= 1;
		//end create tank

		//start create plane
		

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(0.01f, translatePlaneY - 0.05f, -0.05f);
		RenderMesh(meshes["tail"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(0.0f, translatePlaneY, 0.0f);
		RenderMesh(meshes["back"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(0.5f, translatePlaneY, 0.0f);
		RenderMesh(meshes["connection"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(0.8f, translatePlaneY, 0.0f);
		RenderMesh(meshes["body"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(1.3f, translatePlaneY, 0.0f);
		RenderMesh(meshes["front"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(1.5f, translatePlaneY, 0.0f);
		RenderMesh(meshes["airscrew"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(1.5f, translatePlaneY + 0.1f, 0.0f);
		modelMatrix *= Transform3D::RotateOX(-1.5707f + angularStep_AirScrew);
		RenderMesh(meshes["blade"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(1.5f, translatePlaneY + 0.1f, 0.0f);
		modelMatrix *= Transform3D::RotateOX(2.6179f + angularStep_AirScrew);
		RenderMesh(meshes["blade"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(1.5f, translatePlaneY + 0.1f, 0.0f);
		modelMatrix *= Transform3D::RotateOX(0.5235f + angularStep_AirScrew);
		RenderMesh(meshes["blade"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(0.8f, translatePlaneY, 0.0f);
		RenderMesh(meshes["wing"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(0.8f, translatePlaneY, -1.0f);
		RenderMesh(meshes["wing"], shaders["VertexColor"], modelMatrix);

		planeXmin = 0;
		planeXmax = 1.6f;
		planeYmin = translatePlaneY - 0.2f;
		planeYmax = translatePlaneY + 0.2f;
		//end create plane

		srand(time(NULL));
		for (int i = 0; i < nrObjects; i++) {
			if (typeObject[i] == 1) {
				//create fuel
				if (decided_Nr[i] == 0) {
					nrFuels[i] += rand() % 8;
					decided_Nr[i] = 1;
					for (int j = 0; j < nrFuels[i]; j++)
						hit[i][j] = 1;
				}
				for (int j = 0; j < nrFuels[i]; j++) {
					modelMatrix = glm::mat4(1);
					if (yDif[i][j] == 0) {
						yDif[i][j] = 1;
						int yNext = rand() % 3;
						if (j == 0)
							yDifference[i][j] = 0;
						else
							yDifference[i][j] = yDifference[i][j - 1];
						if (yNext == 0)
							yDifference[i][j] += 0;
						else {
							if (yNext == 1)
								yDifference[i][j] += 0.4f;
							else
								yDifference[i][j] += -0.4f;
						}
					}
					float xFuel = distanceObjectX[i] + translateObjectX[i] + 0.8f * j;
					float yFuel = yObject[i] + yDifference[i][j];
					if (yFuel >= planeYmin - 0.2 && yFuel <= planeYmax + 0.2 &&
						xFuel >= planeXmin && xFuel <= planeXmax && hit[i][j] == 1)
					{
						hit[i][j] = 0;
						tankFuel += 100;
						if (tankFuel > 2000)
							tankFuel = 2000;
					}
					if (hit[i][j] == 1) {
						modelMatrix *= Transform3D::Translate(xFuel, yFuel, 0.0f);
						modelMatrix *= Transform3D::RotateOX(angularStep_Objects);
						modelMatrix *= Transform3D::RotateOY(angularStep_Objects);
						RenderMesh(meshes["fuel"], shaders["VertexColor"], modelMatrix);
					}
				}
				if (translateObjectX[i] < (-25.6f - distanceObjectX[i])) {
					translateObjectX[i] = 0.0f;
					yObject[i] = rand() % 5 + 0.1f * (rand() % 10);
					typeObject[i] = rand() % 2;
					for (int j = 0; j < nrFuels[i]; j++) {
						yDif[i][j] = 0;
					}
					decided_Nr[i] = 0;
					nrFuels[i] = 1;

				}
				else
					translateObjectX[i] -= speed * 0.1f;
				//end create fuel
			}
			if (typeObject[i] == 0) {
				//create obstacle
				if (obstacleCreated[i] == 1)
				{
					hit[i][0] = 1;
					obstacleCreated[i] = 0;
				}
				modelMatrix = glm::mat4(1);
				float xObstacle = distanceObjectX[i] + translateObjectX[i];
				if (yObject[i] >= planeYmin - 0.3f && yObject[i] <= planeYmax + 0.3f &&
					xObstacle >= planeXmin && xObstacle <= planeXmax && hit[i][0] == 1)
				{
					hit[i][0] = 0;
					nrHearts -= 1;
				}
				if (hit[i][0] == 1) {
					modelMatrix *= Transform3D::Translate(xObstacle, yObject[i], 0.0f);
					modelMatrix *= Transform3D::RotateOX(angularStep_Objects);
					modelMatrix *= Transform3D::RotateOY(angularStep_Objects);
					RenderMesh(meshes["obstacle"], shaders["VertexColor"], modelMatrix);
				}
				if (translateObjectX[i] < (-25.6f - distanceObjectX[i])) {
					translateObjectX[i] = 0.0f;
					yObject[i] = rand() % 5 + 0.1f * (rand() % 10);
					typeObject[i] = rand() % 2;
					obstacleCreated[i] = 1;
				}
				else
					translateObjectX[i] -= speed * 0.1f;
				//end create obstacle
			}
		}

		//create sea
		modelMatrix = glm::mat4(1);
		if (personCamera == 3) {
			modelMatrix *= Transform3D::Translate(0.0f, -5.6f, 3.0f);
			modelMatrix *= Transform3D::Scale(20.0f, 4.0f, 7.0f);
		}
		else{
			modelMatrix *= Transform3D::Translate(0.0f, -5.6f, 25.0f);
			modelMatrix *= Transform3D::Scale(20.0f, 4.0f, 50.0f);
		}
		modelMatrix *= Transform3D::RotateOY(1.5707f);
		RenderMesh(meshes["sea"], shaders["VertexColor"], modelMatrix);
		//end sea

		//create clouds
		for (int i = 0; i < nrClouds; i++) {
			modelMatrix = glm::mat4(1);
			modelMatrix *= Transform3D::Translate(distancesCloud[i] + translateCloud[i],
				yCloud[i] + 0.75f, -3.25f);
			modelMatrix *= Transform3D::RotateOX(-0.5235f + angularStep_Cloud1);
			modelMatrix *= Transform3D::RotateOZ(-0.5707f);
			modelMatrix *= Transform3D::Translate(-1.0f, -0.75f, -0.75f);
			modelMatrix *= Transform3D::Scale(2.0f, 1.5f, 1.5f);
			RenderMesh(meshes["cloud2"], shaders["VertexColor"], modelMatrix);

			modelMatrix = glm::mat4(1);
			modelMatrix *= Transform3D::Translate(distancesCloud[i] + 2.0f + translateCloud[i],
				yCloud[i] + 1.0f, -3.0f);
			modelMatrix *= Transform3D::RotateOX(-1.9707f);
			modelMatrix *= Transform3D::RotateOZ(-1.9235f + angularStep_Cloud1);
			modelMatrix *= Transform3D::Translate(-1.0f, -1.0f, -1.0f);
			modelMatrix *= Transform3D::Scale(2.0f, 2.0f, 2.0f);
			RenderMesh(meshes["cloud3"], shaders["VertexColor"], modelMatrix);

			modelMatrix = glm::mat4(1);
			modelMatrix *= Transform3D::Translate(distancesCloud[i] + 2.0f + translateCloud[i],
				yCloud[i] - 0.25f, -3.25f);
			modelMatrix *= Transform3D::RotateOX(-1.7707f);
			modelMatrix *= Transform3D::RotateOZ(-1.7707f + angularStep_Cloud2);
			modelMatrix *= Transform3D::Translate(-1.0f, -0.75f, -0.75f);
			modelMatrix *= Transform3D::Scale(2.0f, 1.5f, 1.5f);
			RenderMesh(meshes["cloud3"], shaders["VertexColor"], modelMatrix);

			modelMatrix = glm::mat4(1);
			modelMatrix *= Transform3D::Translate(distancesCloud[i] + 4.0f + translateCloud[i],
				yCloud[i] + 1.5f, -3.0f);
			modelMatrix *= Transform3D::RotateOX(-0.9235f);
			modelMatrix *= Transform3D::RotateOZ(-0.9707f + angularStep_Cloud1);
			modelMatrix *= Transform3D::Translate(-1.0f, -1.0f, -1.0f);
			modelMatrix *= Transform3D::Scale(2.0f, 2.0f, 2.0f);
			RenderMesh(meshes["cloud2"], shaders["VertexColor"], modelMatrix);

			modelMatrix = glm::mat4(1);
			modelMatrix *= Transform3D::Translate(distancesCloud[i] + 5.75f + translateCloud[i],
				yCloud[i] + 0.75f, -3.25f);
			modelMatrix *= Transform3D::RotateOX(-0.5707f + angularStep_Cloud2);
			modelMatrix *= Transform3D::RotateOZ(-0.5707f);
			modelMatrix *= Transform3D::Translate(-0.75f, -0.75f, -0.75f);
			modelMatrix *= Transform3D::Scale(1.5f, 1.5f, 1.5f);
			RenderMesh(meshes["cloud1"], shaders["VertexColor"], modelMatrix);
			if (translateCloud[i] < (-30.6f - distancesCloud[i])) {
				translateCloud[i] = 0.0f;
				yCloud[i] = rand() % 6 + 0.1f * (rand() % 10);
			}
			else
				translateCloud[i] -= 0.1f;
		}
		//end create clouds

		angularStep_AirScrew += 0.2f;
		angularStep_Objects += 0.01f;
		angularStep_Cloud1 += 0.005f;
		angularStep_Cloud2 += 0.01f;
	}
}

void Tema2::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

void Tema2::FrameEnd()
{
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{

}

void Tema2::OnKeyPress(int key, int mods)
{
	if ((key == GLFW_KEY_SPACE || key == GLFW_KEY_ENTER) 
		&& (tankFuel == 0 || nrHearts == 0)) {
		// initialize angularSteps
		angularStep_AirScrew = 0;
		angularStep_Cloud1 = 0;
		angularStep_Cloud2 = 0;
		angularStep_Objects = 0;

		translatePlaneY = 3.6f;

		//viteza
		speed = 1;
		timeSpeed = 0;

		//initialize values for Clouds
		nrClouds = 4;
		for (int i = 0; i < nrClouds; i++)
			distancesCloud[i] = 23.0f;
		translateCloud[0] = 12.8f;
		for (int i = 1; i < nrClouds; i++)
			translateCloud[i] = translateCloud[i - 1] + 12.8f;
		srand(time(NULL));
		for (int i = 1; i < nrClouds; i++)
			yCloud[i] = rand() % 6 + 0.1f * (rand() % 10);

		//initialize values for objects
		nrObjects = 4;
		for (int i = 0; i < nrObjects; i++)
			distanceObjectX[i] = 25.0f;
		translateObjectX[0] = 4.0f;
		for (int i = 1; i < nrObjects; i++)
			translateObjectX[i] = translateObjectX[i - 1] + 12.8f;
		for (int i = 0; i < nrObjects; i++)
			yObject[i] = rand() % 5 + 0.1f * (rand() % 10);
		for (int i = 0; i < nrObjects; i++) {
			typeObject[i] = rand() % 2;
		}
		for (int i = 1; i < nrObjects; i++) {
			nrFuels[i] = 1;
			decided_Nr[i] = 0;
			for (int j = 0; j < 8; j++)
				yDif[i][j] = 0;
		}

		for (int i = 0; i < nrObjects; i++)
			for (int j = 0; j < 8; j++) {
				hit[i][j] = 0;
			}

		for (int i = 0; i < nrObjects; i++) {
			obstacleCreated[i] = 1;
		}

		tankFuel = 2000;
		nrHearts = 3;
	}

	if (key == GLFW_KEY_C)
		if (personCamera == 1)
			personCamera = 3;
		else
			personCamera = 1;
}

void Tema2::OnKeyRelease(int key, int mods)
{
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	glm::ivec2 resolution = window->GetResolution();
	float mouseY_bottom = (float)resolution.y - (float)mouseY;
	int value = resolution.y / 2.5f;
	if (mouseY_bottom > value) {
		mouseY_bottom -= resolution.y / 2;
		mouseY_bottom *= 720.0f / (resolution.y / 2);
		translatePlaneY = mouseY_bottom / 100;
	}
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}
