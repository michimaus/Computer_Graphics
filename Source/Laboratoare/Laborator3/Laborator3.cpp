#include "Laborator3.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

using namespace std;

Laborator3::Laborator3()
{
}

Laborator3::~Laborator3()
{
}

void Laborator3::Init()
{
	resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = 100;

	// compute coordinates of square center
	float cx = corner.x + squareSide / 2;
	float cy = corner.y + squareSide / 2;

	mySquareSide = 100;

	centerX = resolution.x / 2;
	centerY = resolution.y / 2;
	
	// initialize tx and ty (the translation steps)
	translateX = 0;
	translateY = 0;

	dim2X = dim2Y = 1;

	sq2X = sq1X = resolution.x / 2 - cx;
	
	sq1Y = resolution.y / 2 - cy;

	sq2Y = sq1Y - 100;

	forwardReverse1 = 1;
	limit1Up = sq1X + 25;
	limit1Down = sq1X - 25;

	limit2Down = dim2X - 0.7;
	limit2Up = dim2X - 0.4;
	forwardReverse2 = -1;

	rotatoin2 = rotatoin3 = 0;

	// initialize sx and sy (the scale factors)
	scaleX = 1;
	scaleY = 1;
	
	// initialize angularStep
	// angularStep = 0;
	angularStep = 30;

	radius1 = 130;
	radius2 = 40;
	

	Mesh* square1 = Object2D::CreateSquare("square1", corner, squareSide, glm::vec3(1, 0, 0), true);
	AddMeshToList(square1);
	
	Mesh* square2 = Object2D::CreateSquare("square2", corner, squareSide, glm::vec3(0, 1, 0));
	AddMeshToList(square2);

	Mesh* square3 = Object2D::CreateSquare("square3", corner, squareSide, glm::vec3(0, 0, 1));
	AddMeshToList(square3);
}

void Laborator3::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator3::Update(float deltaTimeSeconds)
{
	// TODO: update steps for translation, rotation, scale, in order to create animations
	

	// compute coordinates of square center
	// float cx = corner.x + mySquareSide / 2;
	// float cy = corner.y + mySquareSide / 2;

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(sq1X, sq1Y);
	// TODO: create animations by multiplying current transform matrix with matrices from Transform 2D

	if (sq1X >= limit1Up) {
		forwardReverse1 = -1;
	}

	if (sq1X <= limit1Down) {
		forwardReverse1 = 1;
	}

	sq1X += forwardReverse1 * angularStep * deltaTimeSeconds;
	sq1Y += forwardReverse1 * angularStep * deltaTimeSeconds;


	RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);


	modelMatrix = glm::mat3(1);

	modelMatrix *= Transform2D::Translate(centerX, centerY);
	modelMatrix *= Transform2D::Rotate(rotatoin2);
	modelMatrix *= Transform2D::Translate(radius1 + (1 - dim2X) * mySquareSide / 2,
										  radius1 + (1 - dim2Y) * mySquareSide / 2);
	// save matrix in order to efficiently compute position for next object
	glm::mat3 modelMatrix3 = modelMatrix;

	modelMatrix *= Transform2D::Scale(dim2X, dim2Y);
	// modelMatrix *= Transform2D::Rotate(-rotation2);



	//TODO create animations by multiplying current transform matrix with matrices from Transform 2D
	if (dim2X >= limit2Up) {
		forwardReverse2 = -1;
	}

	if (dim2X <= limit2Down) {
		forwardReverse2 = 1;
	}

	if (rotatoin2 >= 7) {
		rotatoin2 -= 6.2831853;
	}

	rotatoin2 += angularStep * deltaTimeSeconds * 0.015;
	dim2X += forwardReverse2 * angularStep * deltaTimeSeconds * 0.01;
	dim2Y += forwardReverse2 * angularStep * deltaTimeSeconds * 0.01;

	RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);


	// will use previous calculated matrix
	// modelMatrix = glm::mat3(1);

	modelMatrix3 *= Transform2D::Rotate(rotatoin3);
	modelMatrix3 *= Transform2D::Translate(radius2 + (1 - 0.25) * mySquareSide / 2,
										   radius2 + (1 - 0.25) * mySquareSide / 2);
	modelMatrix3 *= Transform2D::Scale(0.25, 0.25);
	modelMatrix3 *= Transform2D::Rotate(-rotatoin3);

	if (rotatoin3 >= 7) {
		rotatoin3 -= 6.2831853;
	}

	rotatoin3 += angularStep * deltaTimeSeconds * 0.035;


	//TODO create animations by multiplying current transform matrix with matrices from Transform 2D
	RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix3);
}

void Laborator3::FrameEnd()
{

}

void Laborator3::OnInputUpdate(float deltaTime, int mods)
{
	
}

void Laborator3::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Laborator3::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator3::OnWindowResize(int width, int height)
{
}
