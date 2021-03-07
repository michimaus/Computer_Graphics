#include "Laborator1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

#define ACCELERATION -0.2;

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp

Laborator1::Laborator1()
{

}



Laborator1::~Laborator1()
{
}

void Laborator1::Init()
{
	// Load a mesh from file into GPU memory
	
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;

		mesh = new Mesh("teapot");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[mesh->GetMeshID()] = mesh;

		mesh = new Mesh("biluta");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;

		this->a = 0;
		this->step = 0.1f;

		this->meshIt = this->meshes.end();
		--this->meshIt;

		this->px = -1;
		this->py = 0.5f;
		this->pz = 0;

		this->y_velocity = -5;
}

void Laborator1::FrameStart()
{

}

void Laborator1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->props.resolution;

	// sets the clear color for the color buffer
	glClearColor(0, a, 0, 1);

	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	// render the object
	RenderMesh(meshes[this->meshIt->first], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));

	// render the object again but with different properties
	RenderMesh(meshes["box"], glm::vec3(px, py, pz));


	RenderMesh(meshes["teapot"], glm::vec3(0, 0, 0.3f));
}

void Laborator1::FrameEnd()
{
	DrawCoordinatSystem();
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator1::OnInputUpdate(float deltaTime, int mods)
{
	// treat continuous update based on input		

	if (window->KeyHold(GLFW_KEY_W)) {
		pz -= 0.2f * deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_S)) {
		pz += 0.2f * deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_D)) {
		px += 0.2f * deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_A)) {
		px -= 0.2f * deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_E)) {
		py += 0.2f * deltaTime;
		y_prev_poz += 0.2f * deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_Q)) {
		py -= 0.2f * deltaTime;
		y_prev_poz -= 0.2f * deltaTime;
	}

	if (y_velocity > -4)
	{
		y_velocity += deltaTime * -5;
		py += deltaTime * y_velocity;
	}
	else
	{
		py = y_prev_poz;
	}
	

};

void Laborator1::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_F) {
		// do something
		if (a <= 0) {
			this->step = +0.1;
		}

		if (a >= 1) {
			this->step = -0.1;
		}

		a += step;
	}

	if (key == GLFW_KEY_G) {
		// do something
		if (this->meshIt == this->meshes.begin()) {
			this->meshIt = this->meshes.end();
		}
		--this->meshIt;
	}

	if (key == GLFW_KEY_SPACE && this->y_velocity <= -4) {
		this->y_velocity = 4;
		y_prev_poz = py;
	}
};

void Laborator1::OnKeyRelease(int key, int mods)
{
	// add key release event
};

void Laborator1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
};

void Laborator1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Laborator1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator1::OnWindowResize(int width, int height)
{
	// treat window resize event
}
