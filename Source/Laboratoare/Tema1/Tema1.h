#pragma once

#include <Component/SimpleScene.h>
#include <Core/Engine.h>

#include <list>
#include <string>
#include <vector>

struct arrowPoz {
    float x;
    float y;

    bool loaded;
    float tanSteepVal;
    float arrowSpeed;
};

struct balloonPoz {
    float x;
    float y;

    int color;
    float upSpeed;

    bool gotHit;
    float scaleFactor;
};

struct shurikenPoz {
    float x;
    float y;

    float speed;
    float rotation;

    bool gotHit;
};

struct newLife {
    float x;
    float y;

    float speed;
};

class Tema1 : public SimpleScene {
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

    void drawBow();
    void drawFlyingArrows(float deltaTimeSeconds);
    void drawArrowOnBow(glm::mat3 modelArrow, float x, float y);

    void drawShurikens(float deltaTimeSeconds);
    void drawBalloons(float deltaTimeSeconds);
    void drawNewLives(float deltaTimeSeconds);

    bool checkArrowCollision();

   protected:
    glm::mat3 modelBow;
    glm::mat3 modelFlexBowDown;
    glm::mat3 modelFlexBowUp;

    glm::ivec2 resolution;

    float translateX, translateY;
    float scaleX, scaleY;
    float angularStep;

    float centerX, centerY;

    float mySquareSide;

    float mouseX, mouseY;
    float bowToCursorDistance;

    float bowY;
    float bowX;
    float bowPower;
    float bowHypotenuse;
    float tanVal;

    short int lives;

    float arrowGravity;
    float arrowBaseSpeed;

    float moveVal;
    float liftBalloon;
    float addPower;

    float bowReload;
    float bowRealodDecrease;

    float timeBalloon;
    float timeBalloonDecrease;

    float timeShuriken;
    float timeShurikenDecrease;

    float timeNewLife;
    float timeNewLifeDecrease;

    float collisionDistanceSquared;

    int balloonInitSpeed;
    int shurikenInitSpeed;
    int shurikenSpawnTime;
    int balloonSpawnFactor;

    int scor;
    int currentLevel;

    float heartSize;
    float arrowSize;
    float shurikenSize;

    std::list<arrowPoz> arrows;
    std::list<arrowPoz>::iterator arrowsIt;

    std::list<balloonPoz> balloons;
    std::list<balloonPoz>::iterator balloonIt;

    std::list<shurikenPoz> shurikens;
    std::list<shurikenPoz>::iterator shurikenIt;

    std::list<newLife> newLifes;
    std::list<newLife>::iterator newLifeIt;
};
