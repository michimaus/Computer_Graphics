#pragma once

#include <include/glm.h>

namespace Transform2D {
    // Translate matrix
    inline glm::mat3 Translate(float translateX, float translateY) {
        // TODO implement translate matrix

        return glm::mat3(1, 0, 0, 0, 1, 0, translateX, translateY, 1);
    }

    // Scale matrix
    inline glm::mat3 Scale(float scaleX, float scaleY) {
        // TODO implement scale matrix
        return glm::mat3(scaleX, 0, 0, 0, scaleY, 0, 0, 0, 1);
    }

    // Rotate matrix
    inline glm::mat3 Rotate(const float radians) {
        // TODO implement rotate matrix

        const auto my_cos = cos(radians);
        const auto my_sin = sin(radians);

        return glm::mat3(my_cos, my_sin, 0, -my_sin, my_cos, 0, 0, 0, 1);
    }
}
