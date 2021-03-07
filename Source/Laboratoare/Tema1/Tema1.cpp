#include "Tema1.h"

#include <Core/Engine.h>
#include <time.h>

#include <iostream>

#include "Object2D.h"
#include "Transform2D.h"

using namespace std;

Tema1::Tema1() {
}

Tema1::~Tema1() {
}

void Tema1::Init() {
    resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);

    mySquareSide = 80;

    centerX = resolution.x / 2;
    centerY = resolution.y / 2;

    translateX = 0;
    translateY = 0;

    mouseX = mouseY = 0;

    bowY = centerY;
    bowX = resolution.x / 20;

    moveVal = 150;

    liftBalloon = 0.25;

    addPower = 75;

    bowReload = -1;
    timeBalloon = -1;
    timeShuriken = -1;
    timeShuriken = -1;

    arrowGravity = 0.25;
    arrowBaseSpeed = 22.5;

    bowRealodDecrease = 10;
    timeBalloonDecrease = 5;
    timeShurikenDecrease = 10;
    timeNewLifeDecrease = 5;

    balloonSpawnFactor = 16;

    scaleX = 1;
    scaleY = 1;

    bowPower = 0;
    collisionDistanceSquared = 2000;
    lives = 3;

    balloonInitSpeed = 0;
    shurikenSpawnTime = 40;
    shurikenInitSpeed = 250;

    heartSize = 10;
    arrowSize = 130;
    shurikenSize = 30;

    scor = 0;
    currentLevel = 1;
    std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~ \n       "
              << "level " << currentLevel
              << "       \n ~~~~~~~~~~~~~~~~~~~~~~ \n";

    std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~ \n       "
              << scor << " points"
              << "       \n ~~~~~~~~~~~~~~~~~~~~~~ \n";

    srand((unsigned)time(NULL));

    angularStep = 30;

    Mesh* square1 = Object2D::CreateSquare("square1", corner, heartSize, glm::vec3(0.75, 0, 0), true);
    AddMeshToList(square1);

    Mesh* square2 = Object2D::CreateSquare("square2", corner, heartSize, glm::vec3(0, 0, 0.75), true);
    AddMeshToList(square2);

    Mesh* circle = Object2D::CreateCircle("semiCircle", corner, mySquareSide, glm::vec3(1, 0, 0));
    AddMeshToList(circle);

    Mesh* line = Object2D::CreateLine("line", corner, mySquareSide, glm::vec3(1, 0, 0));
    AddMeshToList(line);

    Mesh* arrow = Object2D::CreateArrow("arrow", corner, arrowSize, glm::vec3(1, 0, 0));
    AddMeshToList(arrow);

    Mesh* shuriken = Object2D::CreateShuriken("shuriken", corner, shurikenSize, glm::vec3(1, 1, 1));
    AddMeshToList(shuriken);

    Mesh* redBalloon = Object2D::CreateBalloon("redBalloon", corner, mySquareSide, glm::vec3(1, 0, 0));
    AddMeshToList(redBalloon);

    Mesh* yellowBalloon = Object2D::CreateBalloon("yellowBalloon", corner, mySquareSide, glm::vec3(1, 1, 0));
    AddMeshToList(yellowBalloon);

    Mesh* redBalloonPop = Object2D::CreateBalloonPoping("redBalloonPop", corner, mySquareSide, glm::vec3(1, 0, 0));
    AddMeshToList(redBalloonPop);

    Mesh* yellowBalloonPop = Object2D::CreateBalloonPoping("yellowBalloonPop", corner, mySquareSide, glm::vec3(1, 1, 0));
    AddMeshToList(yellowBalloonPop);

    Mesh* heart = Object2D::CreateHeart("heart", corner, heartSize, glm::vec3(1, 0, 0));
    AddMeshToList(heart);

    Mesh* rope = Object2D::CreateRope("rope", corner, mySquareSide, glm::vec3(0.8, 0.8, 0.8));
    AddMeshToList(rope);
}

void Tema1::FrameStart() {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::drawFlyingArrows(float deltaTimeSeconds) {
    arrowsIt = arrows.begin();

    while (arrowsIt != arrows.end()) {
        if (arrowsIt->loaded == false) {
            glm::mat3 myMatrix = glm::mat3(1);

            arrowsIt->x += deltaTimeSeconds * arrowsIt->arrowSpeed * 15 * cos(arrowsIt->tanSteepVal);
            arrowsIt->y += deltaTimeSeconds * arrowsIt->arrowSpeed * 15 * sin(arrowsIt->tanSteepVal);

            myMatrix *= Transform2D::Translate(arrowsIt->x, arrowsIt->y);

            if (arrowsIt->tanSteepVal > -M_PI_4 - M_PI_4 / 2) {
                arrowsIt->tanSteepVal -= deltaTimeSeconds * arrowGravity * M_PI;
            }
            myMatrix *= Transform2D::Rotate(arrowsIt->tanSteepVal);

            RenderMesh2D(meshes["arrow"], shaders["VertexColor"], myMatrix);
        }

        if (arrowsIt->x > 1300 || arrowsIt->y < -50) {
            arrowsIt = arrows.erase(arrowsIt);
        } else {
            arrowsIt++;
        }
    }
}

void Tema1::drawShurikens(float deltaTimeSeconds) {
    shurikenIt = shurikens.begin();

    while (shurikenIt != shurikens.end()) {
        glm::mat3 myMatrix = glm::mat3(1);

        shurikenIt->rotation += shurikenIt->speed / 50 * deltaTimeSeconds;

        if (shurikenIt->gotHit == true) {
            shurikenIt->y -= shurikenIt->speed * deltaTimeSeconds;
        } else {
            shurikenIt->x -= shurikenIt->speed * deltaTimeSeconds;
        }

        myMatrix *= Transform2D::Translate(shurikenIt->x, shurikenIt->y);
        myMatrix *= Transform2D::Rotate(shurikenIt->rotation);
        RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], myMatrix);

        if (shurikenIt->rotation > M_PI) {
            shurikenIt->rotation -= M_PI;
        }

        float diffX = shurikenIt->x - bowX;
        float diffY = shurikenIt->y - bowY;

        if (shurikenIt->x < -100 || shurikenIt->y < -100) {
            shurikenIt = shurikens.erase(shurikenIt);
        } else if (diffX * diffX + diffY * diffY < (mySquareSide + shurikenSize) *
                                                       (mySquareSide + shurikenSize) &&
                                                       shurikenIt->gotHit == false) {
            shurikenIt = shurikens.erase(shurikenIt);
            --lives;
        } else {
            shurikenIt++;
        }
    }
}

void Tema1::drawNewLives(float deltaTimeSeconds) {
    newLifeIt = newLifes.begin();

    while (newLifeIt != newLifes.end()) {
        glm::mat3 myMatrix = glm::mat3(1);

        newLifeIt->x -= newLifeIt->speed * deltaTimeSeconds;

        myMatrix *= Transform2D::Translate(newLifeIt->x, newLifeIt->y);
        myMatrix *= Transform2D::Scale(2, 2);
        RenderMesh2D(meshes["heart"], shaders["VertexColor"], myMatrix);

        float diffX = newLifeIt->x - bowX;
        float diffY = newLifeIt->y - bowY;

        if (newLifeIt->x < -100) {
            newLifeIt = newLifes.erase(newLifeIt);
        } else if (diffX * diffX + diffY * diffY < (mySquareSide + heartSize * M_SQRT2) * (mySquareSide + heartSize * M_SQRT2)) {
            newLifeIt = newLifes.erase(newLifeIt);
            ++lives;
        } else {
            newLifeIt++;
        }
    }
}

void Tema1::drawBalloons(float deltaTimeSeconds) {
    balloonIt = balloons.begin();

    while (balloonIt != balloons.end()) {
        glm::mat3 myMatrix = glm::mat3(1);

        balloonIt->upSpeed += liftBalloon * deltaTimeSeconds;
        balloonIt->y += balloonIt->upSpeed;

        glm::mat3 myMatrixRope = myMatrix *= Transform2D::Translate(balloonIt->x, balloonIt->y);

        myMatrix *= Transform2D::Scale(balloonIt->scaleFactor, balloonIt->scaleFactor);

        if (balloonIt->color) {
            if (balloonIt->gotHit) {
                RenderMesh2D(meshes["redBalloonPop"], shaders["VertexColor"], myMatrix);
                balloonIt->scaleFactor -= deltaTimeSeconds;
            } else {
                RenderMesh2D(meshes["redBalloon"], shaders["VertexColor"], myMatrix);
            }
        } else {
            if (balloonIt->gotHit) {
                RenderMesh2D(meshes["yellowBalloonPop"], shaders["VertexColor"], myMatrix);
                balloonIt->scaleFactor -= deltaTimeSeconds;
            } else {
                RenderMesh2D(meshes["yellowBalloon"], shaders["VertexColor"], myMatrix);
            }
        }
        RenderMesh2D(meshes["rope"], shaders["VertexColor"], myMatrixRope);

        if (balloonIt->y > 900 || balloonIt->scaleFactor < 0.2) {
            balloonIt = balloons.erase(balloonIt);
        } else {
            balloonIt++;
        }
    }
}

void Tema1::drawArrowOnBow(glm::mat3 modelArrow, float x, float y) {
    RenderMesh2D(meshes["arrow"], shaders["VertexColor"], modelArrow);
    arrows.begin()->x = x;
    arrows.begin()->y = y;
}

void Tema1::drawBow() {
    mouseX = window->GetCursorPosition().x;
    mouseY = resolution.y - window->GetCursorPosition().y;

    modelBow = glm::mat3(1);
    modelBow *= Transform2D::Translate(bowX, bowY);

    tanVal = atan((mouseY - bowY) / (mouseX - bowX));
    modelBow *= Transform2D::Rotate(tanVal);

    modelFlexBowDown = modelBow * Transform2D::Translate(-bowPower, 0);

    if (!arrows.empty() && arrows.begin()->loaded == true) {
        arrows.begin()->tanSteepVal = tanVal;
        drawArrowOnBow(modelFlexBowDown, bowX, bowY);
    }

    bowHypotenuse = sqrt(mySquareSide * mySquareSide + bowPower * bowPower);
    modelFlexBowUp = modelFlexBowDown *= Transform2D::Scale(1, (bowHypotenuse / mySquareSide));

    modelFlexBowDown *= Transform2D::Rotate(-acos(mySquareSide / bowHypotenuse));
    RenderMesh2D(meshes["line"], shaders["VertexColor"], modelFlexBowDown);
    modelFlexBowUp *= Transform2D::Rotate(-acos(-mySquareSide / bowHypotenuse));
    RenderMesh2D(meshes["line"], shaders["VertexColor"], modelFlexBowUp);

    modelBow *= Transform2D::Scale(1 + (bowPower / 400), 1);
    RenderMesh2D(meshes["semiCircle"], shaders["VertexColor"], modelBow);
}

bool Tema1::checkArrowCollision() {
    bool rez = false;

    arrowsIt = arrows.begin();

    while (arrowsIt != arrows.end()) {
        if (arrowsIt->loaded == false) {
            int sharpX = arrowsIt->x + arrowSize * cos(arrowsIt->tanSteepVal);
            int sharpY = arrowsIt->y + arrowSize * sin(arrowsIt->tanSteepVal);

            balloonIt = balloons.begin();
            while (balloonIt != balloons.end()) {
                if ((balloonIt->y - sharpY) * (balloonIt->y - sharpY) +
                            (balloonIt->x - sharpX) * (balloonIt->x - sharpX) <
                        collisionDistanceSquared &&
                    balloonIt->gotHit == false) {
                    rez = true;

                    if (balloonIt->color) {
                        std::cout << "Hit red ballon: +10 points!!";
                        scor += 10;
                    } else {
                        std::cout << "Hit yellow ballon: -15 points!!";
                        scor -= 15;
                    }

                    balloonIt->gotHit = true;
                } else {
                    balloonIt++;
                }
            }

            shurikenIt = shurikens.begin();
            while (shurikenIt != shurikens.end()) {
                if ((shurikenIt->y - sharpY) * (shurikenIt->y - sharpY) +
                            (shurikenIt->x - sharpX) * (shurikenIt->x - sharpX) <
                        collisionDistanceSquared &&
                    shurikenIt->gotHit == false) {
                    rez = true;
                    std::cout << "Hit shuriken: +5 points!!";
                    scor += 5;

                    shurikenIt->gotHit = true;
                } else {
                    shurikenIt++;
                }
            }
        }

        arrowsIt++;
    }

    return rez;
}

void Tema1::Update(float deltaTimeSeconds) {
    if (lives <= 0) {
        return;
    } else {
        glm::mat3 mathere = Transform2D::Translate(50, 670);
        for (int i = 0; i < lives; ++i) {
            RenderMesh2D(meshes["heart"], shaders["VertexColor"], mathere);
            mathere *= Transform2D::Translate(50, 0);
        }
    }

    if (timeBalloon > 0) {
        timeBalloon -= timeBalloonDecrease * deltaTimeSeconds;

        if (timeBalloon <= 0) {
            balloons.push_back({(float)380 + rand() % 800, -100, rand() % 2, balloonInitSpeed + (float)(rand() % 3), false, 1});
        }
    } else {
        timeBalloon = rand() % balloonSpawnFactor;
    }

    if (timeNewLife > 0) {
        timeNewLife -= timeNewLifeDecrease * deltaTimeSeconds;

        if (timeNewLife <= 0) {
            newLifes.push_back({1400, (float)100 + rand() % 520, (float)shurikenInitSpeed + rand() % 250});
        }
    } else {
        timeNewLife = rand() % 175 + 175;
    }

    if (timeShuriken > 0) {
        timeShuriken -= timeShurikenDecrease * deltaTimeSeconds;

        if (timeShuriken <= 0) {
            shurikens.push_back({1400, (float)100 + rand() % 520, (float)shurikenInitSpeed + rand() % 250});
        }
    } else {
        timeShuriken = rand() % (shurikenSpawnTime + 60) + shurikenSpawnTime;
    }

    if (bowReload > 0) {
        bowReload -= bowRealodDecrease * deltaTimeSeconds;

        RenderMesh2D(meshes["square2"], shaders["VertexColor"], Transform2D::Translate(10, 10) * Transform2D::Scale(bowReload / 4, 1));

        if (bowReload <= 0) {
            arrows.push_front({0, 0, true, 0, 0});
        }
    } else {
        if (arrows.empty() || arrows.begin()->loaded == false) {
            bowReload = rand() % 30 + 10;
        }
    }

    if (bowPower > 0) {
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], Transform2D::Translate(10, 10) * Transform2D::Scale(bowPower / 5, 1));
    }

    this->drawBow();
    this->drawFlyingArrows(deltaTimeSeconds);
    this->drawBalloons(deltaTimeSeconds);
    this->drawShurikens(deltaTimeSeconds);
    this->drawNewLives(deltaTimeSeconds);

    if (scor > currentLevel * 20) {
        ++currentLevel;

        shurikenSpawnTime = (shurikenSpawnTime * 4) / 7;
        ++balloonInitSpeed;

        shurikenInitSpeed += 30;

        --balloonSpawnFactor;
        balloonSpawnFactor = max(balloonSpawnFactor, 3);

        std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~ \n       "
                  << "level " << currentLevel
                  << "       \n ~~~~~~~~~~~~~~~~~~~~~~ \n";
    }

    if (this->checkArrowCollision()) {
        std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~ \n     "
                  << scor << " points"
                  << "     \n ~~~~~~~~~~~~~~~~~~~~~~ \n";
    }
}

void Tema1::FrameEnd() {
}

void Tema1::OnInputUpdate(float deltaTime, int mods) {
    if (window->KeyHold(GLFW_KEY_W) && bowY < (resolution.y - 35)) {
        bowY += deltaTime * moveVal;
    }

    if (window->KeyHold(GLFW_KEY_S) && bowY > 35) {
        bowY -= deltaTime * moveVal;
    }

    if (window->KeyHold(GLFW_KEY_SPACE) && (!arrows.empty() && arrows.begin()->loaded == true)) {
        if (bowPower < 50 && bowReload <= 0) {
            bowPower += deltaTime * addPower;
        }
    }
}

void Tema1::OnKeyPress(int key, int mods) {
    // add key press event
}

void Tema1::OnKeyRelease(int key, int mods) {
    if (key == GLFW_KEY_SPACE) {
        if (!arrows.empty() && arrows.begin()->loaded == true) {
            arrows.begin()->loaded = false;
            arrows.begin()->arrowSpeed = bowPower + arrowBaseSpeed;
        }

        bowPower = 0;
    }
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
    // add mouse move event
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
    // add mouse button press event
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
    // add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {
}

void Tema1::OnWindowResize(int width, int height) {
}
