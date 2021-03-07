#pragma once
#include <Component/SimpleScene.h>

class Laborator4 : public SimpleScene {
   public:
    Laborator4();
    ~Laborator4();

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
    glm::mat4 modelMatrix;
    glm::mat4 modelMatrix2;
    float translateX, translateY, translateZ;
    float scaleX, scaleY, scaleZ;
    float angularStepOX, angularStepOY, angularStepOZ;
    GLenum polygonMode;

    float moveVal;

    float forwardReverse1;
    float limit1Up, limit1Down;

    float forwardReverse2;
    float limit2Up, limit2Down;

    float forwardReverse3;
    float limit3Up, limit3Down;

    float sq1X, sq1Y;
    float sq2X, sq2Y;
    float sq3X, sq3Y;

    float dim2X, dim2Y;
    float rotatoin2;

    float rotatoin3;

    float radius1;
    float radius2;


    float solarX;
    float solarY;
	float solarZ;

	float frogY;

	float speedFrogY;
	float acc;

	float scaleSun;

	float rotateEarth;
	float roateMoon;
};
