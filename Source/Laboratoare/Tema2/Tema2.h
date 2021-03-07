#pragma once

#include <Component/SimpleScene.h>
#include <Core/Engine.h>

#include <iterator>
#include <list>
#include <unordered_map>

#include "Laboratoare/Laborator5/LabCamera.h"
#include "MyCamera.h"

struct platform {
    bool isPresent[7];
    bool gotEffect[7];

    glm::vec3 color[7];
    unsigned short int type[7];

    bool hasBlock[7];
    bool hasPrize[7];

    std::list<int> ligtPositions;

    float zPossition;
};

struct SideMemes {
    int memeId1;
    int memeId2;

    float rotation1;
    float rotation2;

    float rotSpeed1;
    float rotSpeed2;

    float zPossition;
};

struct BuffOverTime {
    float duration;
    glm::vec3 color;
};

class Tema2 : public SimpleScene {
   public:
    Tema2();
    ~Tema2();

    void Init() override;

   private:
    void FrameStart() override;
    void Update(float deltaTimeSeconds) override;
    void FrameEnd() override;

    glm::vec3 getColor(unsigned short int& type);

    void updatePlatforms(float deltaTimeSeconds);
    bool checkBallOnPlatform(int& rowIndexToCheck);
    void updateSphereSpeed(float deltaTimeSeconds);
    void updateStats(float deltaTimeSeconds);

    void updateSideMemes(float deltaTimeSeconds);

    void RenderMesh3D(Mesh* mesh, Shader* shader, const glm::vec3& position, const glm::vec3& scale, const glm::vec3& color);
    void RenderMesh3D(Mesh* mesh, Shader* shader, const glm::vec3& position, const glm::vec3& scale);

    void RenderSimpleMeshTexture(Mesh* mesh, Shader* shader, const glm::vec3& position,
                                 const glm::vec3& scale, Texture2D* texture1, float oyRotation = 0);

    void RenderMesh2D(Mesh* mesh, Shader* shader, const glm::mat3& modelMatrix, Texture2D* texture1 = NULL);
    void RenderMesh2D(Mesh* mesh, Shader* shader, const glm::mat3& modelMatrix, const glm::vec3& color, Texture2D* texture1 = NULL);

    void OnInputUpdate(float deltaTime, int mods) override;
    void OnKeyPress(int key, int mods) override;
    void OnKeyRelease(int key, int mods) override;
    void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
    void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
    void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
    void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
    void OnWindowResize(int width, int height) override;

   protected:
    Tema2Camera::Camera* camera;
    Tema2Camera::Camera* interfaceCamera;
    Tema2Camera::Camera* skyBoxVeiwCamera;

    glm::mat4 projectionMatrix;
    bool renderCameraTarget;

    bool myProjection;

    float bot;
    float top;
    float rgt;
    float lft;

    float farVal, nearVal;
    float fov;

    int lives;
    float lengthSphere;

    float yThridPersone, zThirdPersone;

    float levelRanderDistance;

    float cameraRotOfsetY;
    float cameraRotOfsetX;

    int scor;
    int collected;
    int platformFreq;

    float speedLateral;
    float gravity;
    float jumpBoost;

    float ySphereSpeed;
    bool isJumping;

    float delatSpeed;
    float gameSpeed;
    float gameSpeedMax, gameSpeedMin;
    float fuel, fuelMax;
    float fuelDrainRate;
    float platformLength;

    float xSphere, ySphere, zSphere;

    GLenum cullFace;
    GLenum polygonMode;

    std::list<platform> platforms;
    std::list<platform>::iterator platformIterator;

    std::list<SideMemes> memes;
    std::list<SideMemes>::iterator memeIterator;

    std::unordered_map<unsigned short int, BuffOverTime> buffs;
    std::unordered_map<std::string, Texture2D*> mapTextures;

    bool isFirstPersone;

    int isSpotLight;
    float rotOX, rotOY;
    float cutOffAngle;

    glm::vec3 lightPosition;
    glm::vec3 lightDirection;
    unsigned int materialShininess;
    float materialKd;
    float materialKs;
};
