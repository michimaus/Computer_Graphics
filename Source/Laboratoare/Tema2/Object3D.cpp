#include "Object3D.h"

#include <Core/Engine.h>

#include <iostream>

#define CIRCLE_SEGMENTS 5
#define SPHERE_EXTENSION 5

void Object3D::CreateMesh(const std::string& name, const std::vector<VertexFormat>& vertices,
                          const std::vector<unsigned short>& indices,
                          std::unordered_map<std::string, Mesh*>& meshes, bool fill) {
    unsigned int VAO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO = 0;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    unsigned int IBO = 0;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));

    glBindVertexArray(0);

    CheckOpenGLError();

    meshes[name] = new Mesh(name);

    if (!fill) {
        meshes[name]->SetDrawMode(GL_LINE_LOOP);
    }

    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
}

void Object3D::CreatePlatform(std::string name, glm::vec3 figCenter,
                              float length, glm::vec3 color,
                              std::unordered_map<std::string, Mesh*>& meshes) {
    glm::vec3 whiteee = glm::vec3(1);

    std::vector<VertexFormat> myVertices{
        VertexFormat(glm::vec3(-1 * length, 0 * length, -1 * length), whiteee),

        VertexFormat(glm::vec3(0 * length, 0 * length, -1 * length), color),
        VertexFormat(glm::vec3(-1 * length, 0 * length, 0 * length), color),
        VertexFormat(glm::vec3(0 * length, 0 * length, 0 * length), whiteee),

        VertexFormat(glm::vec3(-1 * length, -1 * length, -1 * length), color),
        VertexFormat(glm::vec3(0 * length, -1 * length, -1 * length), whiteee),
        VertexFormat(glm::vec3(-1 * length, -1 * length, 0 * length), color),
        VertexFormat(glm::vec3(0 * length, -1 * length, 0 * length), whiteee),

    };

    std::vector<unsigned short> myIndices = {
        0, 2, 1,
        1, 2, 3,
        1, 3, 5,
        5, 3, 7,
        5, 7, 4,
        4, 7, 6,
        4, 6, 0,
        0, 6, 2,
        0, 1, 4,
        1, 5, 4,
        2, 6, 3,
        3, 6, 7};

    Object3D::CreateMesh(name, myVertices, myIndices, meshes);
}

void Object3D::InterfaceCreateHeart(std::string name, glm::vec3 figCenter,
                                    float length, glm::vec3 color,
                                    std::unordered_map<std::string, Mesh*>& meshes) {
    glm::vec3 corner = figCenter;

    std::vector<VertexFormat> myVertices;
    std::vector<unsigned short> myIndices;

    unsigned short step = 1;

    int segments = CIRCLE_SEGMENTS * 3;

    int myBounds = segments;

    myVertices.push_back(VertexFormat(corner, glm::vec3(1, 1, 1)));

    for (int i = -myBounds; i <= myBounds; ++i) {
        float x = 2 * length * i / segments;

        float y1 = sqrt(1 - (abs(x / length) - 1) * (abs(x / length) - 1));
        float y2 = (acos(1 - abs(x / length)) - M_PI) * 0.75;

        myVertices.push_back(VertexFormat(corner + glm::vec3(x, y1 * length, 0), color));
        myVertices.push_back(VertexFormat(corner + glm::vec3(x, y2 * length, 0), color));

        myIndices.push_back(step + 2);
        myIndices.push_back(step);
        myIndices.push_back(0);

        myIndices.push_back(step + 1);
        myIndices.push_back(step + 3);
        myIndices.push_back(0);

        step += 2;
    }

    Object3D::CreateMesh(name, myVertices, myIndices, meshes);
}

void Object3D::InterfaceCreateSquere(std::string name, glm::vec3 figCenter,
                                     float length, glm::vec3 color,
                                     std::unordered_map<std::string, Mesh*>& meshes, bool fill) {
    glm::vec3 corner = figCenter;

    std::vector<VertexFormat> vertices = {

        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)

    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned short> indices;

    if (!fill) {
        indices = {0, 1, 2, 3};
    } else {
        indices = {
            0, 1, 2,
            2, 3, 0};
    }

    Object3D::CreateMesh(name, vertices, indices, meshes, fill);
}

void Object3D::CreateCube(std::string name, glm::vec3 figCenter,
                          float length, glm::vec3 color,
                          std::unordered_map<std::string, Mesh*>& meshes) {
    std::vector<VertexFormat> myVertices{
        VertexFormat(glm::vec3(-1 * length, -1 * length, 1 * length), glm::vec3(0, 0.5, 1)),

        VertexFormat(glm::vec3(0 * length, -1 * length, 1 * length), glm::vec3(0, 0.25, 1)),
        VertexFormat(glm::vec3(-1 * length, -1 * length, 2 * length), glm::vec3(0, 1, 1)),
        VertexFormat(glm::vec3(0 * length, -1 * length, 2 * length), glm::vec3(0, 1, 1)),

        VertexFormat(glm::vec3(-1 * length, -2 * length, 1 * length), glm::vec3(1, 0, 1)),
        VertexFormat(glm::vec3(0 * length, -2 * length, 1 * length), glm::vec3(0.5, 1, 0.5)),
        VertexFormat(glm::vec3(-1 * length, -2 * length, 2 * length), glm::vec3(0.5, 0, 0.5)),
        VertexFormat(glm::vec3(0 * length, -2 * length, 2 * length), glm::vec3(0, 1, 0)),

    };

    std::vector<unsigned short> myIndices = {
        0,
        2,
        1,
        1,
        2,
        3,
        1,
        3,
        5,
        5,
        3,
        7,

        5,
        7,
        4,
        4,
        7,
        6,

        4,
        6,
        0,
        0,
        6,
        2,

        0,
        1,
        4,
        1,
        5,
        4,

        2,
        6,
        3,
        3,
        6,
        7,
    };

    Object3D::CreateMesh(name, myVertices, myIndices, meshes);
}

glm::vec3 computNewHalfPoint(const glm::vec3& p1, const glm::vec3& p2, const int& length) {
    glm::vec3 newP = p1 + p2;
    float scaleP = length / sqrt(newP.x * newP.x + newP.y * newP.y + newP.z * newP.z);
    newP *= scaleP;
    return newP;
}

void sphereRecursiveHelper(std::vector<VertexFormat>& myVertices, std::vector<unsigned short>& myIndices,
                           unsigned int depth, unsigned int p1, unsigned int p2, unsigned int p3,
                           unsigned int& maxSize, const int& length) {
    if (depth == CIRCLE_SEGMENTS) {
        myIndices.push_back(p1);
        myIndices.push_back(p2);
        myIndices.push_back(p3);
    } else {
        myVertices.push_back(VertexFormat(computNewHalfPoint(myVertices[p1].position, myVertices[p2].position, length), glm::vec3(0.975)));
        myVertices.push_back(VertexFormat(computNewHalfPoint(myVertices[p2].position, myVertices[p3].position, length), glm::vec3(0.975)));
        myVertices.push_back(VertexFormat(computNewHalfPoint(myVertices[p3].position, myVertices[p1].position, length), glm::vec3(0.975)));

        maxSize += 3;
        int mySizeHere = maxSize;

        sphereRecursiveHelper(myVertices, myIndices, depth + 1, p1, mySizeHere - 3, mySizeHere - 1, maxSize, length);
        sphereRecursiveHelper(myVertices, myIndices, depth + 1, p2, mySizeHere - 2, mySizeHere - 3, maxSize, length);
        sphereRecursiveHelper(myVertices, myIndices, depth + 1, p3, mySizeHere - 1, mySizeHere - 2, maxSize, length);
        sphereRecursiveHelper(myVertices, myIndices, depth + 1, mySizeHere - 1, mySizeHere - 3, mySizeHere - 2, maxSize, length);
    }
}

void Object3D::CreateMyBalls(std::string name, glm::vec3 figCenter,
                             float length, glm::vec3 color,
                             std::unordered_map<std::string, Mesh*>& meshes) {
    std::vector<VertexFormat> myVertices;
    std::vector<unsigned short> myIndices;

    myVertices.push_back(VertexFormat(figCenter + glm::vec3(0, 0, length), glm::vec3(0, 0.5, 1)));
    myVertices.push_back(VertexFormat(figCenter + glm::vec3(0, 0, -length), glm::vec3(0, 1, 0.5)));

    float horzAngle = M_PI / 180 * 72.0f;
    float vertAngle = atan(0.5f);

    float hAngle1 = -M_PI / 2 - horzAngle / 2;
    float hAngle2 = -M_PI / 2;

    for (int i = 0; i < 5; ++i) {
        int z = length * sin(vertAngle);
        int xyAngle = length * cos(vertAngle);
        float scaleP;

        glm::vec3 topP = glm::vec3(xyAngle * cos(hAngle1), xyAngle * sin(hAngle1), z);
        scaleP = length / sqrt(topP.x * topP.x + topP.y * topP.y + topP.z * topP.z);

        myVertices.push_back(VertexFormat(figCenter + topP * scaleP, glm::vec3(0.3, 0.8, 0.75)));

        glm::vec3 botP = glm::vec3(xyAngle * cos(hAngle2), xyAngle * sin(hAngle2), -z);
        scaleP = length / sqrt(botP.x * botP.x + botP.y * botP.y + botP.z * botP.z);

        myVertices.push_back(VertexFormat(figCenter + botP * scaleP, glm::vec3(1, 0.6, 0.2)));

        hAngle1 += horzAngle;
        hAngle2 += horzAngle;
    }

    unsigned int maxSize = 12;

    sphereRecursiveHelper(myVertices, myIndices, 1, 0, 2, 4, maxSize, length);
    sphereRecursiveHelper(myVertices, myIndices, 1, 0, 4, 6, maxSize, length);
    sphereRecursiveHelper(myVertices, myIndices, 1, 0, 6, 8, maxSize, length);
    sphereRecursiveHelper(myVertices, myIndices, 1, 0, 8, 10, maxSize, length);
    sphereRecursiveHelper(myVertices, myIndices, 1, 0, 10, 2, maxSize, length);

    sphereRecursiveHelper(myVertices, myIndices, 1, 3, 1, 5, maxSize, length);
    sphereRecursiveHelper(myVertices, myIndices, 1, 5, 1, 7, maxSize, length);
    sphereRecursiveHelper(myVertices, myIndices, 1, 7, 1, 9, maxSize, length);
    sphereRecursiveHelper(myVertices, myIndices, 1, 9, 1, 11, maxSize, length);
    sphereRecursiveHelper(myVertices, myIndices, 1, 11, 1, 3, maxSize, length);

    sphereRecursiveHelper(myVertices, myIndices, 1, 2, 3, 4, maxSize, length);
    sphereRecursiveHelper(myVertices, myIndices, 1, 3, 5, 4, maxSize, length);
    sphereRecursiveHelper(myVertices, myIndices, 1, 4, 5, 6, maxSize, length);
    sphereRecursiveHelper(myVertices, myIndices, 1, 5, 7, 6, maxSize, length);
    sphereRecursiveHelper(myVertices, myIndices, 1, 6, 7, 8, maxSize, length);
    sphereRecursiveHelper(myVertices, myIndices, 1, 7, 9, 8, maxSize, length);
    sphereRecursiveHelper(myVertices, myIndices, 1, 8, 9, 10, maxSize, length);
    sphereRecursiveHelper(myVertices, myIndices, 1, 9, 11, 10, maxSize, length);
    sphereRecursiveHelper(myVertices, myIndices, 1, 10, 11, 2, maxSize, length);
    sphereRecursiveHelper(myVertices, myIndices, 1, 11, 3, 2, maxSize, length);

    Object3D::CreateMesh(name, myVertices, myIndices, meshes);
}

void Object3D::SkyCreateSquere(std::string name, glm::vec3 figCenter,
                               float length, std::unordered_map<std::string, Mesh*>& meshes) {
    glm::vec3 corner = figCenter;

    std::vector<glm::vec3> vertices = {

        corner + glm::vec3(0, length, 0),
        corner,
        corner + glm::vec3(length, 0, 0),
        corner + glm::vec3(length, length, 0)

    };

    std::vector<glm::vec3> normals{
        glm::vec3(0, 1, 1),
        glm::vec3(1, 0, 1),
        glm::vec3(1, 0, 0),
        glm::vec3(0, 1, 0)};

    std::vector<glm::vec2> textureCoords{
        glm::vec2(0, 0),
        glm::vec2(0, length),
        glm::vec2(length, length),
        glm::vec2(length, 0)};

    std::vector<unsigned short> indices =
        {
            1, 3, 2,
            1, 0, 3};

    Mesh* mesh = new Mesh(name);
    mesh->InitFromData(vertices, normals, textureCoords, indices);
    meshes[name] = mesh;
}

void Object3D::CreateTexturedPlatform(std::string name, glm::vec3 figCenter,
                                      float length, glm::vec3 color,
                                      std::unordered_map<std::string, Mesh*>& meshes) {
    glm::vec3 whiteee = glm::vec3(1);

    std::vector<glm::vec3> vertices = {
        // front
        figCenter + glm::vec3(0, 0, 0),
        figCenter + glm::vec3(0, -length, 0),
        figCenter + glm::vec3(-length, -length, 0),
        figCenter + glm::vec3(-length, 0, 0),

        // back
        figCenter + glm::vec3(0, 0, -length),
        figCenter + glm::vec3(0, -length, -length),
        figCenter + glm::vec3(-length, -length, -length),
        figCenter + glm::vec3(-length, 0, -length),

        // right
        figCenter + glm::vec3(0, 0, 0),
        figCenter + glm::vec3(0, 0, -length),
        figCenter + glm::vec3(0, -length, -length),
        figCenter + glm::vec3(0, -length, 0),

        // left
        figCenter + glm::vec3(-length, 0, -length),
        figCenter + glm::vec3(-length, -length, -length),
        figCenter + glm::vec3(-length, -length, 0),
        figCenter + glm::vec3(-length, 0, 0),

        // up
        figCenter + glm::vec3(0, 0, 0),
        figCenter + glm::vec3(0, 0, -length),
        figCenter + glm::vec3(-length, 0, -length),
        figCenter + glm::vec3(-length, 0, 0),

        // down
        figCenter + glm::vec3(0, -length, 0),
        figCenter + glm::vec3(0, -length, -length),
        figCenter + glm::vec3(-length, -length, -length),
        figCenter + glm::vec3(-length, -length, 0),

    };

    std::vector<glm::vec3> normals = {
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 1),

        glm::vec3(0, 0, -1),
        glm::vec3(0, 0, -1),
        glm::vec3(0, 0, -1),
        glm::vec3(0, 0, -1),

        glm::vec3(1, 0, 0),
        glm::vec3(1, 0, 0),
        glm::vec3(1, 0, 0),
        glm::vec3(1, 0, 0),

        glm::vec3(-1, 0, 0),
        glm::vec3(-1, 0, 0),
        glm::vec3(-1, 0, 0),
        glm::vec3(-1, 0, 0),

        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 0),

        glm::vec3(0, -1, 0),
        glm::vec3(0, -1, 0),
        glm::vec3(0, -1, 0),
        glm::vec3(0, -1, 0),

    };

    std::vector<glm::vec2> textureCoords = {
        glm::vec2(0, -1),
        glm::vec2(0, 0),
        glm::vec2(-1, 0),
        glm::vec2(-1, -1),

        glm::vec2(-1, -1),
        glm::vec2(-1, 0),
        glm::vec2(0, 0),
        glm::vec2(0, -1),

        glm::vec2(0, 0),
        glm::vec2(0, -1),
        glm::vec2(-1, -1),
        glm::vec2(-1, 0),

        glm::vec2(0, 0),
        glm::vec2(0, -1),
        glm::vec2(-1, -1),
        glm::vec2(-1, 0),

        glm::vec2(0, 0),
        glm::vec2(0, -1),
        glm::vec2(-1, -1),
        glm::vec2(-1, 0),

        glm::vec2(0, 0),
        glm::vec2(0, -1),
        glm::vec2(-1, -1),
        glm::vec2(-1, 0)

    };

    std::vector<unsigned short> indices = {
        0, 3, 1,
        1, 3, 2,

        4, 5, 7,
        5, 6, 7,

        8, 11, 9,
        9, 11, 10,

        12, 13, 15,
        13, 14, 15,

        16, 17, 19,
        17, 18, 19,

        20, 23, 21,
        21, 23, 22

    };

    Mesh* mesh = new Mesh("square");
    mesh->InitFromData(vertices, normals, textureCoords, indices);
    meshes[name] = mesh;
}