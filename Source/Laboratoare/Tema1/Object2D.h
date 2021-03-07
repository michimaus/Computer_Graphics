#pragma once

#include <Core/GPU/Mesh.h>
#include <include/glm.h>

#include <string>

namespace Object2D {

// Create square with given bottom left corner, length and color
Mesh* CreateSquare(std::string name, glm::vec3 leftBottomCorner,
                   float length, glm::vec3 color, bool fill = false);

Mesh* CreateCircle(std::string name, glm::vec3 leftBottomCorner,
                   float length, glm::vec3 color);

Mesh* CreateLine(std::string name, glm::vec3 leftBottomCorner,
                 float length, glm::vec3 color);

Mesh* CreateArrow(std::string name, glm::vec3 leftBottomCorner,
                  float length, glm::vec3 color);

Mesh* CreateShuriken(std::string name, glm::vec3 leftBottomCorner,
                     float length, glm::vec3 color);

Mesh* CreateBalloon(std::string name, glm::vec3 leftBottomCorner,
                    float length, glm::vec3 color);

Mesh* CreateBalloonPoping(std::string name, glm::vec3 leftBottomCorner,
                          float length, glm::vec3 color);

Mesh* CreateHeart(std::string name, glm::vec3 leftBottomCorner,
                  float length, glm::vec3 color);

Mesh* CreateRope(std::string name, glm::vec3 leftBottomCorner,
                  float length, glm::vec3 color);

}  // namespace Object2D
