#include "Laborator4.h"

#include <Core/Engine.h>

#include <iostream>
#include <string>
#include <vector>

#include "Transform3D.h"

using namespace std;

Laborator4::Laborator4() {
}

Laborator4::~Laborator4() {
}

void Laborator4::Init() {
    polygonMode = GL_FILL;

    Mesh* mesh = new Mesh("box");
    mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
    meshes[mesh->GetMeshID()] = mesh;

    // initialize tx, ty and tz (the translation steps)
    translateX = 0;
    translateY = 0;
    translateZ = 0;

    // initialize sx, sy and sz (the scale factors)
    scaleX = 1;
    scaleY = 1;
    scaleZ = 1;

    // initialize angularSteps
    angularStepOX = 0;
    angularStepOY = 0;
    angularStepOZ = 0;

    moveVal = 2;

    forwardReverse1 = 1;
    forwardReverse2 = -1;

    scaleSun = 0.9;

	frogY = 0.5;
	acc = 0.933;

    solarX = 0;
    solarY = 0;
    solarZ = 0;

    rotateEarth = 1;
    roateMoon = 2;

    rotatoin2 = 0;
}

void Laborator4::FrameStart() {
    // clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator4::Update(float deltaTimeSeconds) {
    glLineWidth(3);
    glPointSize(5);
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

    modelMatrix = glm::mat4(1);
    modelMatrix *= Transform3D::Translate(-2.5f, 0.5f, -1.5f);
    modelMatrix *= Transform3D::Translate(translateX, translateY, translateZ);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= Transform3D::Translate(0.0f, 0.5f, -1.5f);
    modelMatrix *= Transform3D::Scale(scaleX, scaleY * 1.3, scaleZ * 0.7);
    RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= Transform3D::Translate(2.5f, 0.5f, -1.5f);
    modelMatrix *= Transform3D::RotateOX(angularStepOX);
    modelMatrix *= Transform3D::RotateOY(angularStepOY);
    modelMatrix *= Transform3D::RotateOZ(angularStepOZ);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);



    // frog the cube
    modelMatrix = glm::mat4(1);
    modelMatrix *= Transform3D::Translate(solarX, frogY, 0);
	modelMatrix *= Transform3D::RotateOZ(-rotatoin2);
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);


	if (rotatoin2 < (M_PI / 2)) {
		frogY += speedFrogY * deltaTimeSeconds;
		speedFrogY *= acc;
	} else {
		speedFrogY /= acc;
		frogY -= speedFrogY * deltaTimeSeconds;
	}

    rotatoin2 += moveVal * deltaTimeSeconds * 0.8;


	if (rotatoin2 >= M_PI) {
		rotatoin2 -= M_PI;
		speedFrogY = 8;
		frogY = 0.5;
	}
	

    // Solar System
    modelMatrix = glm::mat4(1);
    modelMatrix *= Transform3D::Translate(solarX, solarY, solarZ);
    modelMatrix2 = modelMatrix;
    modelMatrix2 *= Transform3D::Scale(scaleSun, scaleSun, scaleSun);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix2);

    modelMatrix *= Transform3D::RotateOY(rotateEarth);
    modelMatrix *= Transform3D::Translate(0, 0, 3.5);
    modelMatrix *= Transform3D::Scale(0.7, 0.7, 0.7);
    modelMatrix *= Transform3D::RotateOY(rotateEarth * -4);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

    modelMatrix *= Transform3D::RotateOY(roateMoon);
    modelMatrix *= Transform3D::Translate(0, 0, 2);
    modelMatrix *= Transform3D::Scale(0.5, 0.5, 0.5);
    modelMatrix *= Transform3D::RotateOY(roateMoon * 0.5);
    RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);

    if (solarX > 500) {
        forwardReverse1 = -1;
    }

    if (solarX < -500) {
        forwardReverse1 = 1;
    }

    if (rotateEarth >= 7) {
        rotateEarth -= 6.2831853;
    }

    if (roateMoon >= 7) {
        roateMoon -= 6.2831853;
    }

    if (scaleSun < 0.8) {
        forwardReverse2 = 1;
    }

    if (scaleSun > 1.35) {
        forwardReverse2 = -1;
    }

    solarX += forwardReverse1 * moveVal * deltaTimeSeconds * 0.25;
    solarZ += -forwardReverse1 * moveVal * deltaTimeSeconds * 0.2;
    solarY += forwardReverse1 * moveVal * deltaTimeSeconds * 0.3;

    scaleSun += forwardReverse2 * moveVal * deltaTimeSeconds * 0.5;

    rotateEarth += moveVal * deltaTimeSeconds * 0.4;
    roateMoon += moveVal * deltaTimeSeconds * 3;

	
}

void Laborator4::FrameEnd() {
    DrawCoordinatSystem();
}

void Laborator4::OnInputUpdate(float deltaTime, int mods) {
    // TODO

    if (!window->KeyHold(GLFW_MOUSE_BUTTON_RIGHT)) {
        if (window->KeyHold(GLFW_KEY_S)) {
            translateZ += deltaTime * moveVal;
        }

        if (window->KeyHold(GLFW_KEY_W)) {
            translateZ -= deltaTime * moveVal;
        }

        if (window->KeyHold(GLFW_KEY_A)) {
            translateX -= deltaTime * moveVal;
        }

        if (window->KeyHold(GLFW_KEY_D)) {
            translateX += deltaTime * moveVal;
        }

        if (window->KeyHold(GLFW_KEY_R)) {
            translateY += deltaTime * moveVal;
        }

        if (window->KeyHold(GLFW_KEY_F)) {
            translateY -= deltaTime * moveVal;
        }
    }

    if (window->KeyHold(GLFW_KEY_1)) {
        scaleX += deltaTime * moveVal;
        scaleY += deltaTime * moveVal;
        scaleZ += deltaTime * moveVal;
    }

    if (window->KeyHold(GLFW_KEY_2)) {
        scaleX -= deltaTime * moveVal;
        scaleY -= deltaTime * moveVal;
        scaleZ -= deltaTime * moveVal;
    }

    if (window->KeyHold(GLFW_KEY_3)) {
        angularStepOX += deltaTime * moveVal;
    }

    if (window->KeyHold(GLFW_KEY_4)) {
        angularStepOX -= deltaTime * moveVal;
    }

    if (window->KeyHold(GLFW_KEY_5)) {
        angularStepOY += deltaTime * moveVal;
    }

    if (window->KeyHold(GLFW_KEY_6)) {
        angularStepOY -= deltaTime * moveVal;
    }

    if (window->KeyHold(GLFW_KEY_7)) {
        angularStepOZ += deltaTime * moveVal;
    }

    if (window->KeyHold(GLFW_KEY_8)) {
        angularStepOZ -= deltaTime * moveVal;
    }
}

void Laborator4::OnKeyPress(int key, int mods) {
    // add key press event
    if (key == GLFW_KEY_SPACE) {
        switch (polygonMode) {
            case GL_POINT:
                polygonMode = GL_FILL;
                break;
            case GL_LINE:
                polygonMode = GL_POINT;
                break;
            default:
                polygonMode = GL_LINE;
                break;
        }
    }
}

void Laborator4::OnKeyRelease(int key, int mods) {
    // add key release event
}

void Laborator4::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
    // add mouse move event
}

void Laborator4::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
    // add mouse button press event
}

void Laborator4::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
    // add mouse button release event
}

void Laborator4::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {
}

void Laborator4::OnWindowResize(int width, int height) {
}
