#pragma once

#include <Core/GPU/Mesh.h>
#include <include/glm.h>

#include <string>
#include <unordered_map>

namespace Object3D {

void CreateMesh(const std::string& name, const std::vector<VertexFormat>& vertices,
                const std::vector<unsigned short>& indices,
                std::unordered_map<std::string, Mesh*>& meshes, bool fill = true);

// Create square with given bottom left corner, length and color
void CreateCube(std::string name, glm::vec3 figCenter,
                float length, glm::vec3 color,
                std::unordered_map<std::string, Mesh*>& meshes);

void CreateMyBalls(std::string name, glm::vec3 figCenter,
                   float length, glm::vec3 color,
                   std::unordered_map<std::string, Mesh*>& meshes);

void CreatePlatform(std::string name, glm::vec3 figCenter,
                    float length, glm::vec3 color,
                    std::unordered_map<std::string, Mesh*>& meshes);

void InterfaceCreateHeart(std::string name, glm::vec3 figCenter,
                          float length, glm::vec3 color,
                          std::unordered_map<std::string, Mesh*>& meshes);

void InterfaceCreateSquere(std::string name, glm::vec3 figCenter,
                           float length, glm::vec3 color,
                           std::unordered_map<std::string, Mesh*>& meshes, bool fill);

void SkyCreateSquere(std::string name, glm::vec3 figCenter,
                     float length, std::unordered_map<std::string, Mesh*>& meshes);

void CreateTexturedPlatform(std::string name, glm::vec3 figCenter,
                            float length, glm::vec3 color,
                            std::unordered_map<std::string, Mesh*>& meshes);

}  // namespace Object3D
