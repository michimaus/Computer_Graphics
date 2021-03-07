#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

class Laborator3 : public SimpleScene
{
	public:
		Laborator3();
		~Laborator3();

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
		glm::ivec2 resolution;

		float translateX, translateY;
		float scaleX, scaleY;
		float angularStep;

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

		float centerX, centerY;

		float radius1;
		float radius2;

		float mySquareSide;
};
