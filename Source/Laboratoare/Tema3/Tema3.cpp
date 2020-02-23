#include "Tema3.h"
#include "Object3D_tema3.h"
#include "Transform3D.h"

#include <vector>
#include <string>
#include <iostream>


#include <Core/Engine.h>

using namespace std;

Tema3::Tema3()
{
}

Tema3::~Tema3()
{
}

void Tema3::Init()
{
	const string textureLoc = "Source/Laboratoare/Tema3/Textures/";
	sendProiectil = 0;
	angleProiectilX = 0;
	angleProiectilY = 0;
	cameraAngleX = 0;
	cameraAngleY = 0;
	deplasareProiectil = 0;

	camera = new Camera3::Camera();
	camera->Set(glm::vec3(-0.8f, 4.0f, 0.0f), glm::vec3(0.6f, 3.3f, 0), glm::vec3(0, 1, 0));
	projectionMatrix = glm::perspective(RADIANS(90), window->props.aspectRatio,
		0.01f, 100.0f);

	// Load textures

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "earth.jpg").c_str(), GL_REPEAT);
		mapTextures["earth"] = texture;

		heightmap = new Texture2D();
		heightmap->Load2D((textureLoc + "heightmap.png").c_str(), GL_REPEAT);
		mapTextures["heightmap"] = heightmap;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "skin.jpg").c_str(), GL_REPEAT);
		mapTextures["skin"] = texture;
	
		mapTextures["random"] = CreateRandomTexture(32, 32);
	}

	// Load meshes

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Create a simple quad
	Mesh* mesh = Object3D_tema3::CreateSquare("square", 40);
	AddMeshToList(mesh);

	mesh = Object3D_tema3::CreateWorm("worm_tail", glm::vec3(1.0f, 0.75f, 0.7f));
	AddMeshToList(mesh);

	mesh = Object3D_tema3::CreateBox("worm_body", glm::vec3(0, 0, 0), 0.2f,
		1.0f, 0.4f, glm::vec3(1.0f, 0.75f, 0.7f));
	AddMeshToList(mesh);

	mesh = Object3D_tema3::CreateBox("worm_gun", glm::vec3(0, 0, 0), 1.0f,
		0.4f, 0.4f, glm::vec3(0.2, 0.2, 0.2));
	AddMeshToList(mesh);

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader *shader = new Shader("ShaderTema3");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	//Light & material properties
	{
		lightPosition = glm::vec3(0, 5, 0);
		materialShininess = 30;
		materialKd = 3.5;
		materialKs = 3.5;
	}
}

void Tema3::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0.1f, 0.1f, 0.7f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);	
}

void Tema3::Update(float deltaTimeSeconds)
{

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 2.5f, 0.0f));
		modelMatrix *= Transform3D::RotateOZ(cameraAngleY);
		modelMatrix *= Transform3D::RotateOY(cameraAngleX);
		RenderSimpleMesh(meshes["worm_tail"], shaders["VertexColor"], modelMatrix);
		
		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 2.5f, 0.0f));
		modelMatrix *= Transform3D::RotateOZ(cameraAngleY);
		modelMatrix *= Transform3D::RotateOY(cameraAngleX);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.6f, 0.3f, -0.2f));
		RenderSimpleMesh(meshes["worm_body"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 2.5f, 0.0f));
		modelMatrix *= Transform3D::RotateOZ(cameraAngleY);
		modelMatrix *= Transform3D::RotateOY(cameraAngleX);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.6f, 0.8f, -0.6f));
		RenderSimpleMesh(meshes["worm_gun"], shaders["VertexColor"], modelMatrix);
	}
	if (sendProiectil == 1) {
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 2.5f, 0.0f));
		modelMatrix *= Transform3D::RotateOZ(angleProiectilY);
		modelMatrix *= Transform3D::RotateOY(angleProiectilX);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.7f + deplasareProiectil, 1.1f, -0.4f));
		modelMatrix *= Transform3D::Scale(0.2f, 0.2f, 0.2f);
		RenderSimpleMesh(meshes["sphere"], shaders["VertexColor"], modelMatrix);
		if (0.7f + deplasareProiectil > 10.0f) {
			sendProiectil = 0;
		}
		else {
			deplasareProiectil += 0.1f;
		}
	}
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(10.0f, 1.0f, 10.0f));
		RenderSimpleMesh(meshes["square"], shaders["ShaderTema3"], modelMatrix, mapTextures["earth"], mapTextures["earth"]);
	}
}

void Tema3::FrameEnd()
{
	//DrawCoordinatSystem();
}

void Tema3::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, Texture2D* texture1, Texture2D* texture2)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	//glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));

	// Bind projection matrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, heightmap->GetTextureID());
	glUniform1i(glGetUniformLocation(shader->program, "heightmap"), 0);

	GLint width, height;
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
	int loc_HeightMapWidth = glGetUniformLocation(shader->program, "HeightMapWidth");
	glUniform1i(loc_HeightMapWidth, width);
	int loc_HeightMapHeight = glGetUniformLocation(shader->program, "HeightMapHeight");
	glUniform1i(loc_HeightMapHeight, height);

	GLint loc_model_light = glGetUniformLocation(shader->program, "light_position");
	glUniform3fv(loc_model_light, 1, glm::value_ptr(lightPosition));

	glm::vec3 eyePosition = GetSceneCamera()->transform->GetWorldPosition();
	GLint loc_eye_position = glGetUniformLocation(shader->program, "eye_position");
	glUniform3fv(loc_eye_position, 1, glm::value_ptr(eyePosition));

	GLint loc_shininess = glGetUniformLocation(shader->program, "material_shininess");
	glUniform1i(loc_shininess, materialShininess);

	GLint loc_kd = glGetUniformLocation(shader->program, "material_kd");
	glUniform1f(loc_kd, materialKd);

	GLint loc_ks = glGetUniformLocation(shader->program, "material_ks");
	glUniform1f(loc_ks, materialKs);

	if (texture1)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
		glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);
	}

	if (texture2)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());
		glUniform1i(glGetUniformLocation(shader->program, "texture_2"), 1);
	}

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

Texture2D* Tema3::CreateRandomTexture(unsigned int width, unsigned int height)
{
	GLuint textureID = 0;
	unsigned int channels = 3;
	unsigned int size = width * height * channels;
	unsigned char* data = new unsigned char[size];

	for (int i = 0; i < size; i++) {
		data[i] = rand() % 255 - 128;
	}

	// Generate and bind the new texture ID
	glBindTexture(1, textureID);
	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, textureID);
	
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4);

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	CheckOpenGLError();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(GL_TEXTURE_2D);

	CheckOpenGLError();

	// Save the texture into a wrapper Texture2D class for using easier later during rendering phase
	Texture2D* texture = new Texture2D();
	texture->Init(textureID, width, height, channels);

	SAFE_FREE_ARRAY(data);
	return texture;
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Tema3::OnInputUpdate(float deltaTime, int mods)
{

	float cameraSpeed = 2.0f;

	if (window->KeyHold(GLFW_KEY_SPACE) && sendProiectil == 0) {
		sendProiectil = 1;
		angleProiectilX = cameraAngleX;
		angleProiectilY = cameraAngleY;
		deplasareProiectil = 0;
	}

	if (window->KeyHold(GLFW_KEY_W)) {
		camera->TranslateForward(deltaTime);
	}

	if (window->KeyHold(GLFW_KEY_A)) {
		camera->TranslateRight(-deltaTime);
	}

	if (window->KeyHold(GLFW_KEY_S)) {
		camera->TranslateForward(-deltaTime);
	}

	if (window->KeyHold(GLFW_KEY_D)) {
		camera->TranslateRight(deltaTime);
	}

	if (window->KeyHold(GLFW_KEY_Q)) {
		camera->TranslateUpword(-deltaTime);
	}

	if (window->KeyHold(GLFW_KEY_E)) {
		camera->TranslateUpword(deltaTime);
	}
}

void Tema3::OnKeyPress(int key, int mods)
{
}

void Tema3::OnKeyRelease(int key, int mods)
{
}

void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0) {
			cameraAngleY -= deltaY * sensivityOY;
			cameraAngleX -= deltaX * sensivityOX;
			camera->RotateThirdPerson_OX(-deltaY * sensivityOY);
			camera->RotateThirdPerson_OY(-deltaX * sensivityOX);
		}

	}
}

void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}

void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}

void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema3::OnWindowResize(int width, int height)
{
}