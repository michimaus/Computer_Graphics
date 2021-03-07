#include "Object2D.h"

#include <Core/Engine.h>

#define CIRCLE_SEGMENTS 12

Mesh* Object2D::CreateSquare(std::string name, glm::vec3 figCenter,
                             float length, glm::vec3 color, bool fill) {
    glm::vec3 corner = figCenter;

    std::vector<VertexFormat> vertices = {

        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)

    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned short> indices = {0, 1, 2, 3};

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* Object2D::CreateCircle(std::string name, glm::vec3 figCenter,
                             float length, glm::vec3 color) {
    glm::vec3 corner = figCenter;

    std::vector<VertexFormat> vertices;
    Mesh* semiCircle = new Mesh(name);
    std::vector<unsigned short> indices;

    vertices.push_back(VertexFormat(corner + glm::vec3(0, length, 0), glm::vec3(0, 0, 0)));

    indices.push_back(0);

    for (unsigned short i = 1; i < CIRCLE_SEGMENTS; ++i) {
        vertices.push_back(VertexFormat(corner + glm::vec3(length * 0.5 * sin(M_PI * i / CIRCLE_SEGMENTS),
                                                           length * cos(M_PI * i / CIRCLE_SEGMENTS),
                                                           0),
                                        color));
        indices.push_back(i);
    }

    vertices.push_back(VertexFormat(corner + glm::vec3(0, -length, 0), glm::vec3(0, 0, 0)));
    indices.push_back(CIRCLE_SEGMENTS);

    semiCircle->SetDrawMode(GL_LINE_LOOP);
    semiCircle->InitFromData(vertices, indices);

    return semiCircle;
}

Mesh* Object2D::CreateLine(std::string name, glm::vec3 figCenter,
                           float length, glm::vec3 color) {
    glm::vec3 corner = figCenter;

    std::vector<VertexFormat> vertices;
    Mesh* line = new Mesh(name);
    std::vector<unsigned short> indices;

    vertices.push_back(VertexFormat(corner, color));
    vertices.push_back(VertexFormat(corner + glm::vec3(0, length, 0), color));

    indices.push_back(0);
    indices.push_back(1);

    line->SetDrawMode(GL_LINE_LOOP);
    line->InitFromData(vertices, indices);

    return line;
}

Mesh* Object2D::CreateArrow(std::string name, glm::vec3 figCenter,
                            float length, glm::vec3 color) {
    glm::vec3 corner = figCenter;

    std::vector<VertexFormat> vertices;
    Mesh* arrow = new Mesh(name);
    std::vector<unsigned short> indices;

    vertices.push_back(VertexFormat(corner, color));
    vertices.push_back(VertexFormat(corner + glm::vec3(length, 0, 0), color));
    vertices.push_back(VertexFormat(corner + glm::vec3(length * 0.80, length * 0.05, 0), color));
    vertices.push_back(VertexFormat(corner + glm::vec3(length * 0.80, -length * 0.05, 0), color));

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(1);
    indices.push_back(3);
    indices.push_back(1);

    arrow->SetDrawMode(GL_LINE_LOOP);
    arrow->InitFromData(vertices, indices);

    return arrow;
}

Mesh* Object2D::CreateShuriken(std::string name, glm::vec3 figCenter,
                               float length, glm::vec3 color) {
    glm::vec3 corner = figCenter;

    std::vector<VertexFormat> vertices;
    Mesh* arrow = new Mesh(name);
    std::vector<unsigned short> indices;

    vertices.push_back(VertexFormat(corner, color));

    vertices.push_back(VertexFormat(corner + glm::vec3(length, 0, 0), color));
    vertices.push_back(VertexFormat(corner + glm::vec3(length * 0.75, length * 0.45, 0), color));

    vertices.push_back(VertexFormat(corner + glm::vec3(-length, 0, 0), color));
    vertices.push_back(VertexFormat(corner + glm::vec3(-length * 0.75, -length * 0.45, 0), color));

    vertices.push_back(VertexFormat(corner + glm::vec3(0, length, 0), color));
    vertices.push_back(VertexFormat(corner + glm::vec3(-length * 0.45, length * 0.75, 0), color));

    vertices.push_back(VertexFormat(corner + glm::vec3(0, -length, 0), color));
    vertices.push_back(VertexFormat(corner + glm::vec3(length * 0.45, -length * 0.75, 0), color));

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);

    indices.push_back(0);
    indices.push_back(3);
    indices.push_back(4);

    indices.push_back(0);
    indices.push_back(5);
    indices.push_back(6);

    indices.push_back(0);
    indices.push_back(7);
    indices.push_back(8);

    arrow->InitFromData(vertices, indices);

    return arrow;
}

Mesh* Object2D::CreateBalloon(std::string name, glm::vec3 figCenter,
                              float length, glm::vec3 color) {
    glm::vec3 corner = figCenter;

    std::vector<VertexFormat> vertices;
    Mesh* baloon = new Mesh(name);
    std::vector<unsigned short> indices;

    for (unsigned short i = 0; i < 2 * CIRCLE_SEGMENTS; ++i) {
        vertices.push_back(VertexFormat(corner + glm::vec3(length * 0.4 * sin(M_PI * i / CIRCLE_SEGMENTS),
                                                           length * 0.6 * cos(M_PI * i / CIRCLE_SEGMENTS),
                                                           0),
                                        color));

        indices.push_back(i);
        indices.push_back(2 * CIRCLE_SEGMENTS + 1);
        indices.push_back(i + 1);
    }

    vertices.push_back(VertexFormat(corner + glm::vec3(length * 0.4 * sin(M_PI * 2),
                                                       length * 0.6 * cos(M_PI * 2),
                                                       0),
                                    color));

    indices.push_back(2 * CIRCLE_SEGMENTS);
    indices.push_back(2 * CIRCLE_SEGMENTS + 1);
    indices.push_back(0);

    vertices.push_back(VertexFormat(corner, glm::vec3(1, 1, 1)));

    vertices.push_back(VertexFormat(corner + glm::vec3(0, -length * 0.6 * cos(M_PI * 2) + 10, 0),
                                    glm::vec3(1, 1, 1)));
    vertices.push_back(VertexFormat(corner + glm::vec3(-10, -length * 0.6 * cos(M_PI * 2) - 15, 0),
                                    glm::vec3(1, 1, 1)));
    vertices.push_back(VertexFormat(corner + glm::vec3(15, -length * 0.6 * cos(M_PI * 2) - 10, 0),
                                    glm::vec3(1, 1, 1)));

    indices.push_back(2 * CIRCLE_SEGMENTS + 2);
    indices.push_back(2 * CIRCLE_SEGMENTS + 3);
    indices.push_back(2 * CIRCLE_SEGMENTS + 4);

    baloon->InitFromData(vertices, indices);

    return baloon;
}

Mesh* Object2D::CreateBalloonPoping(std::string name, glm::vec3 figCenter,
                                    float length, glm::vec3 color) {
    glm::vec3 corner = figCenter;

    std::vector<VertexFormat> vertices;
    Mesh* baloon = new Mesh(name);
    std::vector<unsigned short> indices;

    for (unsigned short i = 0; i < 2 * CIRCLE_SEGMENTS; ++i) {
        vertices.push_back(VertexFormat(corner + glm::vec3(length * 0.4 * sin(M_PI * i / CIRCLE_SEGMENTS),
                                                           length * 0.6 * cos(M_PI * i / CIRCLE_SEGMENTS),
                                                           0),
                                        color));

        indices.push_back(i);
        if (i % 2) {
            indices.push_back(2 * CIRCLE_SEGMENTS + 1);
        }
    }

    vertices.push_back(VertexFormat(corner, color));

    vertices.push_back(VertexFormat(corner + glm::vec3(0, -length * 0.6 * cos(M_PI * 2) + 10, 0),
                                    glm::vec3(1, 1, 1)));
    vertices.push_back(VertexFormat(corner + glm::vec3(-10, -length * 0.6 * cos(M_PI * 2) - 15, 0),
                                    glm::vec3(1, 1, 1)));
    vertices.push_back(VertexFormat(corner + glm::vec3(15, -length * 0.6 * cos(M_PI * 2) - 10, 0),
                                    glm::vec3(1, 1, 1)));

    indices.push_back(2 * CIRCLE_SEGMENTS + 2);
    indices.push_back(2 * CIRCLE_SEGMENTS + 3);
    indices.push_back(2 * CIRCLE_SEGMENTS + 4);

    baloon->InitFromData(vertices, indices);

    return baloon;
}

Mesh* Object2D::CreateHeart(std::string name, glm::vec3 figCenter,
                            float length, glm::vec3 color) {
    glm::vec3 corner = figCenter;

    std::vector<VertexFormat> vertices;
    Mesh* heart = new Mesh(name);
    std::vector<unsigned short> indices;

    unsigned short step = 1;

    int myBounds = CIRCLE_SEGMENTS;

    vertices.push_back(VertexFormat(corner, glm::vec3(1, 1, 1)));

    for (int i = -myBounds; i <= myBounds; ++i) {
        float x = 2 * length * i / CIRCLE_SEGMENTS;

        float y1 = sqrt(1 - (abs(x / length) - 1) * (abs(x / length) - 1));
        float y2 = (acos(1 - abs(x / length)) - M_PI) * 0.75;

        vertices.push_back(VertexFormat(corner + glm::vec3(x, y1 * length, 0), color));
        vertices.push_back(VertexFormat(corner + glm::vec3(x, y2 * length, 0), color));

        indices.push_back(step);
        indices.push_back(step + 2);
        indices.push_back(0);

        indices.push_back(step + 1);
        indices.push_back(step + 3);
        indices.push_back(0);

        step += 2;
    }

    heart->InitFromData(vertices, indices);

    return heart;
}

Mesh* Object2D::CreateRope(std::string name, glm::vec3 figCenter,
                           float length, glm::vec3 color) {
    glm::vec3 corner = figCenter;

    std::vector<VertexFormat> vertices;
    Mesh* rope = new Mesh(name);
    std::vector<unsigned short> indices;

    vertices.push_back(VertexFormat(corner, color));
    vertices.push_back(VertexFormat(corner + glm::vec3(-2, -length * 0.8, 0), color));
    vertices.push_back(VertexFormat(corner + glm::vec3(15, -length * 1.25, 0), color));
    vertices.push_back(VertexFormat(corner + glm::vec3(-5, -length * 1.35, 0), color));
    vertices.push_back(VertexFormat(corner + glm::vec3(5, -length * 1.7, 0), color));

    indices = {0, 1, 2, 3, 4, 3, 2, 1};

    rope->SetDrawMode(GL_LINE_LOOP);
    rope->InitFromData(vertices, indices);

    return rope;
}