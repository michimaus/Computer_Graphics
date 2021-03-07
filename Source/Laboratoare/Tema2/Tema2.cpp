#include "Tema2.h"

#include <Core/Engine.h>
#include <time.h>

#include <iostream>
#include <vector>

#include "Object3D.h"
#include "Transform2D.h"
#include "Transform3D.h"

using namespace std;

Tema2::Tema2() {
}

Tema2::~Tema2() {
}

void Tema2::Init() {
    renderCameraTarget = false;

    const string textureLoc = "Source/Laboratoare/Tema2/Textures/";

    Texture2D* texture = new Texture2D();
    texture->Load2D((textureLoc + "mind_blowing_scene.jpg").c_str(), GL_REPEAT);
    mapTextures["mind_blowing_scene"] = texture;

    texture = new Texture2D();
    texture->Load2D((textureLoc + "meme0.jpg").c_str(), GL_REPEAT);
    mapTextures["meme0"] = texture;

    texture = new Texture2D();
    texture->Load2D((textureLoc + "meme1.jpg").c_str(), GL_REPEAT);
    mapTextures["meme1"] = texture;

    texture = new Texture2D();
    texture->Load2D((textureLoc + "meme2.jpg").c_str(), GL_REPEAT);
    mapTextures["meme2"] = texture;

    texture = new Texture2D();
    texture->Load2D((textureLoc + "meme3.jpg").c_str(), GL_REPEAT);
    mapTextures["meme3"] = texture;

    texture = new Texture2D();
    texture->Load2D((textureLoc + "meme4.jpg").c_str(), GL_REPEAT);
    mapTextures["meme4"] = texture;

    texture = new Texture2D();
    texture->Load2D((textureLoc + "meme5.jpg").c_str(), GL_REPEAT);
    mapTextures["meme5"] = texture;

    texture = new Texture2D();
    texture->Load2D((textureLoc + "meme6.jpg").c_str(), GL_REPEAT);
    mapTextures["meme6"] = texture;

    texture = new Texture2D();
    texture->Load2D((textureLoc + "meme7.jpg").c_str(), GL_REPEAT);
    mapTextures["meme7"] = texture;

    texture = new Texture2D();
    texture->Load2D((textureLoc + "meme8.jpg").c_str(), GL_REPEAT);
    mapTextures["meme8"] = texture;

    texture = new Texture2D();
    texture->Load2D((textureLoc + "meme9.jpg").c_str(), GL_REPEAT);
    mapTextures["meme9"] = texture;

    texture = new Texture2D();
    texture->Load2D((textureLoc + "meme10.jpg").c_str(), GL_REPEAT);
    mapTextures["meme10"] = texture;

    texture = new Texture2D();
    texture->Load2D((textureLoc + "meme11.jpg").c_str(), GL_REPEAT);
    mapTextures["meme11"] = texture;

    lightPosition = glm::vec3(0, 1, 1);
    lightDirection = glm::vec3(0, -1, 0);
    materialShininess = 30;
    materialKd = 0.5;
    materialKs = 0.5;

    isSpotLight = 0;
    rotOX = 0.f;
    rotOY = 0.f;
    cutOffAngle = 30.f;

    srand((unsigned)time(NULL));

    cullFace = GL_BACK;
    polygonMode = GL_FILL;

    lives = 5;

    window->SetPointerPosition(window->GetResolution().x / 2, window->GetResolution().y / 2);

    cameraRotOfsetY = 0;
    cameraRotOfsetX = 0;

    glm::vec3 corner = glm::vec3(0, 0, 0);

    levelRanderDistance = 800;

    lengthSphere = 8;
    platformLength = 100;

    myProjection = true;

    xSphere = zSphere = 0;
    ySphere = lengthSphere;

    gameSpeedMin = 10;
    gameSpeedMax = 120;

    fuelMax = fuel = 1000;
    fuelDrainRate = 15;

    rgt = 10;
    lft = 0.1;
    bot = 0.1;
    top = 10;
    fov = 40;

    platformFreq = 310;

    speedLateral = 57.5;
    gravity = 225;
    jumpBoost = 125;

    ySphereSpeed = 0;
    gameSpeed = 70;

    delatSpeed = 100;

    nearVal = 1;
    farVal = 1500;

    collected = 0;

    scor = 0;

    isJumping = false;

    for (int i = 0; i < 5; ++i) {
        SideMemes sideMeme;
        sideMeme.zPossition = -levelRanderDistance + 2 * i * platformLength;

        sideMeme.memeId1 = rand() % 11;
        sideMeme.memeId2 = rand() % 11;

        sideMeme.rotation1 = 0;
        sideMeme.rotation2 = 0;

        sideMeme.rotSpeed1 = (float)((float)(rand() % 25) / 10.0) + 1;
        sideMeme.rotSpeed2 = (float)((float)(rand() % 25) / 10.0) + 1;

        memes.push_front(sideMeme);
    }

    for (int i = 0; i < 5; ++i) {
        platform aux;
        aux.zPossition = -levelRanderDistance + i * platformLength;

        int shortCount = 0;
        for (int j = 0; j < 7; ++j) {
            aux.color[j] = glm::vec3(0, 0, 1);
            aux.type[j] = 6;
            aux.gotEffect[j] = false;

            aux.hasBlock[j] = false;
            aux.hasPrize[j] = false;

            if (rand() % 2) {
                aux.isPresent[j] = true;
                shortCount = 0;

            } else {
                ++shortCount;

                if (shortCount > 2) {
                    aux.isPresent[j] = true;
                    shortCount = 0;
                } else {
                    aux.isPresent[j] = false;
                }
            }
        }

        platforms.push_front(aux);
    }

    for (int i = 5; i < 10; ++i) {
        platform aux;
        aux.zPossition = -levelRanderDistance + i * platformLength;

        for (int j = 0; j < 7; ++j) {
            aux.color[j] = glm::vec3(0, 0, 1);
            aux.type[j] = 6;
            aux.gotEffect[j] = false;
            aux.isPresent[j] = true;
            aux.hasBlock[j] = false;
            aux.hasPrize[j] = false;
        }

        platforms.push_front(aux);
    }

    yThridPersone = 60;
    zThirdPersone = 100;

    isFirstPersone = false;
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, nearVal, farVal);

    camera = new Tema2Camera::Camera();
    camera->setThirdPersone(glm::vec3(xSphere, yThridPersone, zThirdPersone), glm::vec3(xSphere, 0, -levelRanderDistance),
                            glm::vec3(0, 1, 0), glm::vec3(xSphere, ySphere, zSphere));

    interfaceCamera = new Tema2Camera::Camera();
    interfaceCamera->setFirtPersone(glm::vec3(0, 0, 1),
                                    glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

    skyBoxVeiwCamera = new Tema2Camera::Camera();
    skyBoxVeiwCamera->setFirtPersone(glm::vec3(0, 0, 1000),
                                     glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    buffs[1].color = glm::vec3(1, 1, 0.1);
    buffs[1].duration = 0;

    buffs[2].color = glm::vec3(0.9, 0.45, 0);
    buffs[2].duration = 0;

    buffs[3].color = glm::vec3(0, 1, 0);
    buffs[3].duration = 0;

    buffs[4].color = glm::vec3(1, 1, 1);
    buffs[4].duration = 0;

    Object3D::CreateCube("myCube", corner, 15, glm::vec3(0, 0.8, 0), meshes);

    Object3D::CreateMyBalls("myBalls", corner, lengthSphere, glm::vec3(0, 0.8, 0), meshes);

    Object3D::InterfaceCreateHeart("heart", corner, 0.015, glm::vec3(1, 0, 0), meshes);

    Object3D::InterfaceCreateSquere("empsq", corner, 0.03, glm::vec3(1, 1, 1), meshes, false);

    Object3D::InterfaceCreateSquere("speedSq", corner, 0.03, glm::vec3(0, 0.8, 0.2), meshes, true);

    Object3D::InterfaceCreateSquere("blackSq", corner, 0.03, glm::vec3(0, 0, 0), meshes, true);

    Object3D::CreatePlatform("platform", corner, 10, glm::vec3(0, 0, 0), meshes);

    Object3D::SkyCreateSquere("sky", corner, 10, meshes);

    Object3D::CreateTexturedPlatform("platformTex", corner, 10, glm::vec3(0, 0, 0), meshes);

    Shader* shader;

    {
        shader = new Shader("ChosenColor");
        shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShaderSimpleColor.glsl", GL_VERTEX_SHADER);
        shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    {
        shader = new Shader("Deformation");
        shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShaderDeformation.glsl", GL_VERTEX_SHADER);
        shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    {
        shader = new Shader("Texture");
        shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShaderTextures.glsl", GL_VERTEX_SHADER);
        shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShaderTextures.glsl", GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
}

glm::vec3 Tema2::getColor(unsigned short int& type) {
    int colorInd = rand() % platformFreq;

    if (colorInd < 15) {
        type = 0;
        return glm::vec3(1, 0, 0);
    } else if (colorInd < 40) {
        type = 1;
        return glm::vec3(1, 1, 0.1);
    } else if (colorInd < 75) {
        type = 2;
        return glm::vec3(0.9, 0.45, 0);
    } else if (colorInd < 90) {
        type = 3;
        return glm::vec3(0, 1, 0);
    } else if (colorInd < 92) {
        type = 4;
        return glm::vec3(1, 0, 1);
    } else if (colorInd < 117) {
        type = 5;
        return glm::vec3(0.5, 0.5, 0.5);
    }

    type = 6;
    return glm::vec3(0, 0, 1);
}

void Tema2::RenderMesh3D(Mesh* mesh, Shader* shader, const glm::vec3& position, const glm::vec3& scale, const glm::vec3& color) {
    if (!mesh || !shader || !shader->program)
        return;

    shader->Use();

    GLint modelLocation = glGetUniformLocation(shader->GetProgramID(), "Model");

    glm::mat4 modelMatrix(1);
    modelMatrix *= Transform3D::Translate(position.x, position.y, position.z);
    modelMatrix *= Transform3D::Scale(scale.x, scale.y, scale.z);
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    GLint viewLocation = glGetUniformLocation(shader->GetProgramID(), "View");
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));

    GLint projLocation = glGetUniformLocation(shader->GetProgramID(), "Projection");
    glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    glBindVertexArray(mesh->GetBuffers()->VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);

    GLint redLocation = glGetUniformLocation(shader->GetProgramID(), "ChanRed");
    glUniform1f(redLocation, color.x);

    GLint greenLocation = glGetUniformLocation(shader->GetProgramID(), "ChanGreen");
    glUniform1f(greenLocation, color.y);

    GLint blueLocation = glGetUniformLocation(shader->GetProgramID(), "ChanBlue");
    glUniform1f(blueLocation, color.z);

    mesh->Render();
}

void Tema2::RenderMesh3D(Mesh* mesh, Shader* shader, const glm::vec3& position, const glm::vec3& scale) {
    if (!mesh || !shader || !shader->program)
        return;

    shader->Use();

    GLint modelLocation = glGetUniformLocation(shader->GetProgramID(), "Model");

    glm::mat4 modelMatrix(1);
    modelMatrix *= Transform3D::Translate(position.x, position.y, position.z);
    modelMatrix *= Transform3D::Scale(scale.x, scale.y, scale.z);
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    GLint viewLocation = glGetUniformLocation(shader->GetProgramID(), "View");
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));

    GLint projLocation = glGetUniformLocation(shader->GetProgramID(), "Projection");
    glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    glBindVertexArray(mesh->GetBuffers()->VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);

    GLint timeLocation = glGetUniformLocation(shader->GetProgramID(), "Time");
    glUniform1f(timeLocation, (GLfloat)Engine::GetElapsedTime());

    mesh->Render();
}

void Tema2::RenderSimpleMeshTexture(Mesh* mesh, Shader* shader, const glm::vec3& position,
                                    const glm::vec3& scale, Texture2D* texture1, float oyRotation) {
    if (!mesh || !shader || !shader->GetProgramID()) {
        return;
    }

    shader->Use();

    int numberLighSources = 0;

    for (std::list<platform>::iterator it = platforms.begin(); it != platforms.end(); ++it) {
        for (std::list<int>::iterator itPositions = it->ligtPositions.begin(); itPositions != it->ligtPositions.end(); ++itPositions) {
            std::string fullName = "light_position[" + std::to_string(numberLighSources) + "]";
            glUniform3f(glGetUniformLocation(shader->program, fullName.c_str()),
                        -50 + *itPositions * 20 - 10, 20 + 5 * sin(4 * Engine::GetElapsedTime()), it->zPossition - platformLength / 2);

            ++numberLighSources;
        }
    }

    glUniform1i(glGetUniformLocation(shader->program, "number_ligh_sources"), numberLighSources);

    glUniform3f(glGetUniformLocation(shader->program, "spot_light_position"), xSphere, ySphere, 0);

    int light_direction = glGetUniformLocation(shader->program, "light_direction");
    glUniform3f(light_direction, lightDirection.x, lightDirection.y, lightDirection.z);

    glm::vec3 eyePosition = camera->GetTargetPosition();
    int eye_position = glGetUniformLocation(shader->program, "eye_position");
    glUniform3f(eye_position, eyePosition.x, eyePosition.y, eyePosition.z);

    int material_shininess = glGetUniformLocation(shader->program, "material_shininess");
    glUniform1i(material_shininess, materialShininess);

    int material_kd = glGetUniformLocation(shader->program, "material_kd");
    glUniform1f(material_kd, materialKd);

    int material_ks = glGetUniformLocation(shader->program, "material_ks");
    glUniform1f(material_ks, materialKs);

    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glm::mat4 modelMatrix(1);
    modelMatrix *= Transform3D::Translate(position.x, position.y, position.z);
    modelMatrix *= Transform3D::Scale(scale.x, scale.y, scale.z);

    if (oyRotation) {
        float factor = scale.x;
        modelMatrix *= Transform3D::RotateOY(oyRotation);
        modelMatrix *= Transform3D::Translate(factor, 0, factor);
    }

    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    GLint viewLocation = glGetUniformLocation(shader->GetProgramID(), "View");
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));

    GLint projLocation = glGetUniformLocation(shader->GetProgramID(), "Projection");
    glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
    glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);

    glBindVertexArray(mesh->GetBuffers()->VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Tema2::RenderMesh2D(Mesh* mesh, Shader* shader, const glm::mat3& modelMatrix, Texture2D* texture1) {
    if (!mesh || !shader || !shader->program)
        return;

    glm::mat3 mm = modelMatrix;
    glm::mat4 model = glm::mat4(
        mm[0][0], mm[0][1], mm[0][2], 0.f,
        mm[1][0], mm[1][1], mm[1][2], 0.f,
        0.f, 0.f, mm[2][2], 0.f,
        mm[2][0], mm[2][1], 0.f, 1.f);

    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(interfaceCamera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(model));

    if (texture1) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
        glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);

        glBindVertexArray(mesh->GetBuffers()->VAO);
        glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
    } else {
        mesh->Render();
    }
}

void Tema2::RenderMesh2D(Mesh* mesh, Shader* shader, const glm::mat3& modelMatrix, const glm::vec3& color, Texture2D* texture1) {
    if (!mesh || !shader || !shader->program)
        return;

    glm::mat3 mm = modelMatrix;
    glm::mat4 model = glm::mat4(
        mm[0][0], mm[0][1], mm[0][2], 0.f,
        mm[1][0], mm[1][1], mm[1][2], 0.f,
        0.f, 0.f, mm[2][2], 0.f,
        mm[2][0], mm[2][1], 0.f, 1.f);

    shader->Use();

    GLint modelLocation = glGetUniformLocation(shader->GetProgramID(), "Model");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

    GLint viewLocation = glGetUniformLocation(shader->GetProgramID(), "View");
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(interfaceCamera->GetViewMatrix()));

    GLint projLocation = glGetUniformLocation(shader->GetProgramID(), "Projection");
    glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    glBindVertexArray(mesh->GetBuffers()->VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);

    GLint redLocation = glGetUniformLocation(shader->GetProgramID(), "ChanRed");
    glUniform1f(redLocation, color.x);

    GLint greenLocation = glGetUniformLocation(shader->GetProgramID(), "ChanGreen");
    glUniform1f(greenLocation, color.y);

    GLint blueLocation = glGetUniformLocation(shader->GetProgramID(), "ChanBlue");
    glUniform1f(blueLocation, color.z);

    if (texture1) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
        glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);
    }

    mesh->Render();
}

void Tema2::FrameStart() {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}

bool Tema2::checkBallOnPlatform(int& rowIndexToCheck) {
    rowIndexToCheck = floor((xSphere + 70) / 20);

    if (rowIndexToCheck < 0 || rowIndexToCheck >= 7) {
        return false;
    }
    platformIterator = platforms.begin();
    if (platformIterator->zPossition > 100) {
        ++platformIterator;
    }

    return platformIterator->isPresent[rowIndexToCheck];
}

void Tema2::updateSphereSpeed(float deltaTimeSeconds) {
    int rowIndexToCheck;

    if (ySphere < -lengthSphere * 10 && buffs[4].duration <= 0) {
        ySphereSpeed = 0;
        isJumping = false;

        --lives;
        buffs[4].duration = 3;

        return;
    }

    if (isFirstPersone) {
        this->camera->RotateFirstPerson_OX(-cameraRotOfsetX);
        this->camera->RotateFirstPerson_OY(-cameraRotOfsetY);

        camera->TranslateUpword(ySphereSpeed * deltaTimeSeconds);

        this->camera->RotateFirstPerson_OX(cameraRotOfsetX);
        this->camera->RotateFirstPerson_OY(cameraRotOfsetY);
    }

    ySphere += ySphereSpeed * deltaTimeSeconds;
    ySphereSpeed += -gravity * deltaTimeSeconds;

    if (this->checkBallOnPlatform(rowIndexToCheck) && 0 <= rowIndexToCheck && rowIndexToCheck < 7 &&
        (platformIterator->hasBlock[rowIndexToCheck] || platformIterator->hasPrize[rowIndexToCheck]) &&
        ySphere <= lengthSphere * 2.5 && ySphere > -lengthSphere &&
        platformIterator->zPossition - platformLength / 2 < 20 && -20 < platformIterator->zPossition - platformLength / 2) {
        if (platformIterator->hasBlock[rowIndexToCheck]) {
            if (buffs[4].duration <= 0) {
                --lives;
            }
            buffs[4].duration += 1.5 + rand() % 3 + (rand() % 10) / 10;
            buffs[4].duration = fmin(buffs[4].duration, 5);

            platformIterator->hasBlock[rowIndexToCheck] = false;
        } else if (platformIterator->hasPrize[rowIndexToCheck]) {
            ++collected;
            platformIterator->hasPrize[rowIndexToCheck] = false;

            std::cout << "\n ~~~~~~~~~~~~ \n"
                      << "Collected: " << collected
                      << "\n ~~~~~~~~~~~~ \n";
        }
    }

    if ((this->checkBallOnPlatform(rowIndexToCheck) && ySphere <= lengthSphere && ySphere >= -lengthSphere / 2) ||
        (buffs[4].duration > 0 && ySphere <= lengthSphere)) {
        if (isFirstPersone) {
            this->camera->RotateFirstPerson_OX(-cameraRotOfsetX);
            this->camera->RotateFirstPerson_OY(-cameraRotOfsetY);

            camera->TranslateUpword(-(ySphere - lengthSphere));

            this->camera->RotateFirstPerson_OX(cameraRotOfsetX);
            this->camera->RotateFirstPerson_OY(cameraRotOfsetY);
        }

        ySphereSpeed = 0;
        isJumping = false;

        ySphere = lengthSphere;

        if (0 <= rowIndexToCheck && rowIndexToCheck < 7 && platformIterator->gotEffect[rowIndexToCheck] == false) {
            ++scor;

            std::cout << "\n ~~~~~~~~~~~~ \n"
                      << "Scor: " << scor
                      << "\n ~~~~~~~~~~~~ \n";

            if (platformFreq > 125 && scor % 10 == 0) {
                --platformFreq;
            }

            platformIterator->color[rowIndexToCheck] = glm::vec3(1, 0.6, 1);

            if (platformIterator->type[rowIndexToCheck] == 0 && buffs[4].duration <= 0) {
                --lives;
                buffs[4].duration = 3;
            } else if (platformIterator->type[rowIndexToCheck] == 1) {
                buffs[1].duration += 1 + rand() % 3 + (rand() % 10) / 10;
                buffs[1].duration = fmin(buffs[1].duration, 7);

            } else if (platformIterator->type[rowIndexToCheck] == 2) {
                buffs[2].duration += 1 + rand() % 3 + (rand() % 10) / 10;
                buffs[2].duration = fmin(buffs[2].duration, 7);

            } else if (platformIterator->type[rowIndexToCheck] == 3) {
                buffs[3].duration += 1 + rand() % 3 + (rand() % 10) / 10;
                buffs[3].duration = fmin(buffs[3].duration, 7);

            } else if (platformIterator->type[rowIndexToCheck] == 4) {
                ++lives;
                buffs[4].duration += 1 + rand() % 3 + (rand() % 10) / 10;
                buffs[4].duration = fmin(buffs[4].duration, 5);

            } else if (platformIterator->type[rowIndexToCheck] == 5) {
                platformIterator->isPresent[rowIndexToCheck] = false;

                isJumping = true;
                ySphereSpeed = jumpBoost * 1.75;
            }

            platformIterator->gotEffect[rowIndexToCheck] = true;
        }
    }

    if (!isFirstPersone) {
        int invDuration = floor(buffs[4].duration * 9);

        if (buffs[4].duration > 0 && invDuration % 2) {
            return;
        }

        if (buffs[1].duration > 0 || buffs[2].duration > 0 || buffs[3].duration > 0) {
            RenderMesh3D(meshes["myBalls"], shaders["Deformation"], glm::vec3(xSphere, ySphere, zSphere), glm::vec3(1));
        } else {
            RenderMesh3D(meshes["myBalls"], shaders["VertexColor"], glm::vec3(xSphere, ySphere, zSphere), glm::vec3(1));
        }
    }
}

void Tema2::updateSideMemes(float deltaTimeSeconds) {
    for (memeIterator = memes.begin(); memeIterator != memes.end(); ++memeIterator) {
        if (buffs[2].duration > 0) {
            memeIterator->zPossition += gameSpeedMax * deltaTimeSeconds * 1.5;
        } else {
            memeIterator->zPossition += gameSpeed * deltaTimeSeconds;
        }

        memeIterator->rotation1 += deltaTimeSeconds * memeIterator->rotSpeed1;
        memeIterator->rotation2 -= deltaTimeSeconds * memeIterator->rotSpeed2;

        if (memeIterator->rotation1 > M_PI * 8) memeIterator->rotation1 -= M_PI * 8;
        if (memeIterator->rotation2 < -M_PI * 8) memeIterator->rotation2 += M_PI * 8;

        RenderSimpleMeshTexture(meshes["platformTex"], shaders["Texture"],
                                glm::vec3(150, 65, memeIterator->zPossition),
                                glm::vec3(6), mapTextures["meme" + to_string(memeIterator->memeId1)],
                                memeIterator->rotation1);

        RenderSimpleMeshTexture(meshes["platformTex"], shaders["Texture"],
                                glm::vec3(-150, 65, memeIterator->zPossition),
                                glm::vec3(6), mapTextures["meme" + to_string(memeIterator->memeId2)],
                                memeIterator->rotation2);
    }

    if (memes.begin()->zPossition > 150) {
        memes.pop_front();

        SideMemes sideMeme;
        sideMeme.zPossition = memes.back().zPossition - 2 * platformLength;

        sideMeme.memeId1 = rand() % 11;
        sideMeme.memeId2 = rand() % 11;

        sideMeme.rotation1 = 0;
        sideMeme.rotation2 = 0;

        sideMeme.rotSpeed1 = (float)((float)(rand() % 25) / 10.0) + 1;
        sideMeme.rotSpeed2 = (float)((float)(rand() % 25) / 10.0) + 1;

        memes.push_back(sideMeme);
    }
}

void Tema2::updatePlatforms(float deltaTimeSeconds) {
    for (platformIterator = platforms.begin(); platformIterator != platforms.end(); ++platformIterator) {
        if (buffs[2].duration > 0) {
            platformIterator->zPossition += gameSpeedMax * deltaTimeSeconds * 1.5;
        } else {
            platformIterator->zPossition += gameSpeed * deltaTimeSeconds;
        }

        for (int i = 0; i < 7; ++i) {
            if (platformIterator->isPresent[i]) {
                RenderSimpleMeshTexture(meshes["platformTex"], shaders["Texture"],
                                        glm::vec3(-50 + i * 20, 0, platformIterator->zPossition),
                                        glm::vec3(2, 0.1, 9.5), mapTextures["meme" + to_string(platformIterator->type[i])]);

                if (platformIterator->hasPrize[i]) {
                    RenderSimpleMeshTexture(meshes["platformTex"], shaders["Texture"],
                                            glm::vec3(-50 + i * 20 - 5, 20 + 5 * sin(4 * Engine::GetElapsedTime()),
                                                      platformIterator->zPossition - platformLength / 2 + 10),
                                            glm::vec3(1), mapTextures["meme11"]);

                } else if (platformIterator->hasBlock[i]) {
                    RenderSimpleMeshTexture(meshes["platformTex"], shaders["Texture"],
                                            glm::vec3(-50 + i * 20, 20, platformIterator->zPossition - platformLength / 2 + 20),
                                            glm::vec3(2), mapTextures["meme" + to_string(platformIterator->type[i])]);
                }
            }
        }
    }

    if (platforms.begin()->zPossition > 150) {
        platforms.pop_front();

        platform aux;
        aux.zPossition = platforms.back().zPossition - platformLength;

        int shortCount = 0;
        for (int j = 0; j < 7; ++j) {
            if (rand() % 2) {
                aux.isPresent[j] = true;
                shortCount = 0;

                aux.gotEffect[j] = false;
                aux.color[j] = this->getColor(aux.type[j]);

                if (rand() % 100 < 10) {
                    aux.hasPrize[j] = true;
                    aux.hasBlock[j] = false;

                    aux.ligtPositions.push_back(j);
                } else {
                    aux.hasPrize[j] = false;

                    if (rand() % 100 < 10) {
                        aux.hasBlock[j] = true;
                    } else {
                        aux.hasBlock[j] = false;
                    }
                }
            } else {
                ++shortCount;

                if (shortCount > 2) {
                    aux.isPresent[j] = true;
                    shortCount = 0;

                    aux.gotEffect[j] = false;
                    aux.color[j] = this->getColor(aux.type[j]);

                    if (rand() % 100 < 10) {
                        aux.hasPrize[j] = true;
                        aux.hasBlock[j] = false;

                        aux.ligtPositions.push_back(j);
                    } else {
                        aux.hasPrize[j] = false;

                        if (rand() % 100 < 10) {
                            aux.hasBlock[j] = true;
                        } else {
                            aux.hasBlock[j] = false;
                        }
                    }
                } else {
                    aux.isPresent[j] = false;
                }
            }
        }

        platforms.push_back(aux);
    }
}

void Tema2::updateStats(float deltaTimeSeconds) {
    glm::mat3 matHearts = glm::mat3(1) * Transform2D::Translate(-0.95, 0.525);
    glm::mat3 matBorder = matHearts;

    for (int i = 0; i < lives; ++i) {
        RenderMesh2D(meshes["heart"], shaders["VertexColor"], matHearts);
        matHearts *= Transform2D::Translate(0.1, 0);
    }
    matBorder *= Transform2D::Scale(10, 1);

    matBorder *= Transform2D::Translate(-0.005, -0.09);

    if (gameSpeed > gameSpeedMax) {
        gameSpeed = gameSpeedMax;
    }

    glm::mat3 matBorderIndicate;

    RenderMesh2D(meshes["empsq"], shaders["VertexColor"], matBorder);

    if (buffs[2].duration > 0) {
        RenderMesh2D(meshes["blackSq"], shaders["ChosenColor"], matBorder, glm::vec3(0.9, 0.2, 0.2));
    } else {
        matBorderIndicate = matBorder * Transform2D::Scale(gameSpeed / gameSpeedMax, 1);
        RenderMesh2D(meshes["speedSq"], shaders["VertexColor"], matBorderIndicate);
    }

    if (fuel > 0) {
        fuel -= (fuelDrainRate + fuelDrainRate * (gameSpeedMax - gameSpeed) / gameSpeedMax) * deltaTimeSeconds;
        fuel = min(fuel, fuelMax);
    } else {
        --lives;
        buffs[4].duration = 3;
        fuel = fuelMax / 2;
    }

    float fuelCoef = fuel / fuelMax;

    matBorder *= Transform2D::Translate(0, -0.065);
    matBorderIndicate = matBorder * Transform2D::Scale(fuelCoef, 1);

    RenderMesh2D(meshes["empsq"], shaders["VertexColor"], matBorder);
    RenderMesh2D(meshes["blackSq"], shaders["ChosenColor"], matBorderIndicate, glm::vec3(1 - fuelCoef, fuelCoef, 0.25));

    matBorder *= Transform2D::Scale(0.2, 0.5);

    if (buffs[1].duration > 0) {
        matBorder *= Transform2D::Translate(0, -0.0475);
        matBorderIndicate = matBorder * Transform2D::Scale(buffs[1].duration, 1);
        RenderMesh2D(meshes["blackSq"], shaders["ChosenColor"], matBorderIndicate, buffs[1].color);

        fuel -= 2 * fuelDrainRate * deltaTimeSeconds;

        buffs[1].duration -= deltaTimeSeconds * 0.75;
    }

    if (buffs[2].duration > 0) {
        matBorder *= Transform2D::Translate(0, -0.0475);
        matBorderIndicate = matBorder * Transform2D::Scale(buffs[2].duration, 1);
        RenderMesh2D(meshes["blackSq"], shaders["ChosenColor"], matBorderIndicate, buffs[2].color);

        buffs[2].duration -= deltaTimeSeconds * 0.75;
    }

    if (buffs[3].duration > 0) {
        matBorder *= Transform2D::Translate(0, -0.0475);
        matBorderIndicate = matBorder * Transform2D::Scale(buffs[3].duration, 1);
        RenderMesh2D(meshes["blackSq"], shaders["ChosenColor"], matBorderIndicate, buffs[3].color);

        fuel += 3 * fuelDrainRate * deltaTimeSeconds;

        buffs[3].duration -= deltaTimeSeconds * 0.75;
    }

    if (buffs[4].duration > 0) {
        matBorder *= Transform2D::Translate(0, -0.0475);
        matBorderIndicate = matBorder * Transform2D::Scale(buffs[4].duration, 1);
        RenderMesh2D(meshes["blackSq"], shaders["ChosenColor"], matBorderIndicate, buffs[4].color);

        buffs[4].duration -= deltaTimeSeconds * 0.75;
    }
}

void Tema2::Update(float deltaTimeSeconds) {
    glLineWidth(3);
    glPointSize(5);
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

    if (lives <= 0) {
        return;
    }

    glEnable(GL_CULL_FACE);
    glCullFace(cullFace);

    this->updateSphereSpeed(deltaTimeSeconds);
    this->updatePlatforms(deltaTimeSeconds);
    this->updateStats(deltaTimeSeconds);

    this->updateSideMemes(deltaTimeSeconds);

    glDisable(GL_CULL_FACE);
}

void Tema2::FrameEnd() {
    Tema2Camera::Camera* auxCamera = interfaceCamera;
    interfaceCamera = skyBoxVeiwCamera;

    glm::mat3 matRenderSky = glm::mat3(1) * Transform2D::Translate(-1100, -600);
    matRenderSky *= Transform2D::Scale(2265, 1275);
    RenderMesh2D(meshes["sky"], shaders["Texture"], matRenderSky, mapTextures["mind_blowing_scene"]);

    skyBoxVeiwCamera = interfaceCamera;
    interfaceCamera = auxCamera;
}

void Tema2::OnInputUpdate(float deltaTime, int mods) {
    if (isFirstPersone) {
        this->camera->RotateFirstPerson_OX(-cameraRotOfsetX);
        this->camera->RotateFirstPerson_OY(-cameraRotOfsetY);
    } else {
        this->camera->RotateThirdPerson_OX(-cameraRotOfsetX);
        this->camera->RotateThirdPerson_OY(-cameraRotOfsetY);
    }

    if (window->KeyHold(GLFW_KEY_A)) {
        xSphere -= speedLateral * deltaTime;
        camera->TranslateRight(-speedLateral * deltaTime);
    }

    if (window->KeyHold(GLFW_KEY_D)) {
        xSphere += speedLateral * deltaTime;
        camera->TranslateRight(speedLateral * deltaTime);
    }

    if (window->KeyHold(GLFW_KEY_SPACE) && !isJumping && ySphere > lengthSphere / 4) {
        isJumping = true;
        ySphereSpeed = jumpBoost;
    }

    if (window->KeyHold(GLFW_KEY_W) && gameSpeed < gameSpeedMax) {
        gameSpeed += deltaTime * delatSpeed;
    }

    if (window->KeyHold(GLFW_KEY_S) && gameSpeed > gameSpeedMin) {
        gameSpeed -= deltaTime * delatSpeed;
    }

    if (isFirstPersone) {
        this->camera->RotateFirstPerson_OX(cameraRotOfsetX);
        this->camera->RotateFirstPerson_OY(cameraRotOfsetY);
    } else {
        this->camera->RotateThirdPerson_OX(cameraRotOfsetX);
        this->camera->RotateThirdPerson_OY(cameraRotOfsetY);
    }
}

void Tema2::OnKeyPress(int key, int mods) {
    if (key == GLFW_KEY_F2) {
        if (cullFace == GL_BACK) {
            cullFace = GL_FRONT;
        } else {
            cullFace = GL_BACK;
        }
    }

    if (key == GLFW_KEY_C) {
        window->SetPointerPosition(window->GetResolution().x / 2, window->GetResolution().y / 2);

        cameraRotOfsetY = 0;
        cameraRotOfsetX = 0;

        if (isFirstPersone) {
            camera->setThirdPersone(glm::vec3(xSphere, yThridPersone, zThirdPersone), glm::vec3(xSphere, 0, -levelRanderDistance),
                                    glm::vec3(0, 1, 0), glm::vec3(xSphere, ySphere, zSphere));
        } else {
            camera->setFirtPersone(glm::vec3(xSphere, ySphere * 1.8, zSphere), glm::vec3(xSphere, 0, -levelRanderDistance), glm::vec3(0, 1, 0));
        }

        isFirstPersone = !isFirstPersone;
    }
}

void Tema2::OnKeyRelease(int key, int mods) {
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
    float sensivityOX;
    float sensivityOY;

    if (isFirstPersone) {
        sensivityOX = 0.00075;
        sensivityOY = 0.00075;

        this->camera->RotateFirstPerson_OX(sensivityOX * -deltaY);
        this->camera->RotateFirstPerson_OY(sensivityOY * -deltaX);

    } else {
        sensivityOX = 0.00055;
        sensivityOY = 0.00055;

        this->camera->RotateThirdPerson_OX(sensivityOX * -deltaY);
        this->camera->RotateThirdPerson_OY(sensivityOY * -deltaX);
    }

    cameraRotOfsetX += sensivityOX * -deltaY;
    cameraRotOfsetY += sensivityOY * -deltaX;
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {
}

void Tema2::OnWindowResize(int width, int height) {
}
