#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

class Tema1 : public SimpleScene
{
public:
	Tema1();
	~Tema1();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

protected:
	glm::mat3 modelMatrix;
	float translateX[10], translateY;//factori de translatie pentru obstacole
	float scaleY;
	int ok = 0;//variabila care contorizeaza daca aripa trebuie sa se miste in sus
	//sau in jos
	float scaleY_obstacol[10][2]; //factor de scalare pentru obstacolele din scena
								//pentru a le oferi inaltimi diferite
	float pasareY; //cu cat s-a deplasat pasarea fata de pozitia initiala pe Oy
	float sus; // variabila folosita pentru a face pasarea sa se ridice cand dau comanda SPACE
	int coliziune = 0; // verificarea coliziunilor 0 - nu exista coliziuni; 1 -exista
	int puncte = 0; //numarul de puncte acumulat de jucator
	int culoare[10]; // culoarea obstacolelor
	int stalpi = 0; //variabila prin care decid cand modific culoarea obstacolelor;
					//culoarea o modific din 4 in 4
};

