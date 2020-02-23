#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#include "Camera.h"

class Tema2 : public SimpleScene
{
public:
	Tema2();
	~Tema2();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix) override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

protected:
	Tema::Camera *camera;
	glm::mat4 projectionMatrix;
	glm::mat4 modelMatrix;

	float translatePlaneY;
	int personCamera = 3;

	int nrClouds;
	float distancesCloud[10];
	float translateCloud[10];
	float yCloud[10];

	float planeXmin, planeXmax, planeYmin, planeYmax;

	int nrObjects;
	int typeObject[10];//0 - obstacle, 1 -fuel
	int obstacleCreated[10];
	int hit[10][8];
	float distanceObjectX[10];
	float translateObjectX[10];
	float yObject[10];
	int nrFuels[10], decided_Nr[10], yDif[10][8];
	float yDifference[10][8];

	int tankFuel;

	int nrHearts;

	int speed;
	int timeSpeed;

	float angularStep_AirScrew, angularStep_Cloud1;
	float angularStep_Cloud2, angularStep_Objects;

	GLenum polygonMode;
};