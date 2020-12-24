#ifndef COMPUTERGRAPHICSPRACTICE_CAMERATRANSFORM_H
#define COMPUTERGRAPHICSPRACTICE_CAMERATRANSFORM_H

#include "glm/glm.hpp"

namespace CameraTransform {
    glm::vec4 rotateAroundPoint(glm::vec4 point, glm::vec3 pivot, float angle);

    glm::vec4 scaleAlongVector(glm::vec4 point, glm::vec3 axisVector, glm::vec3 scaleVector);

    glm::vec4
    projectOnCamera(glm::vec4 point, glm::vec3 cameraPosition, glm::vec3 lookAtPoint, glm::vec3 upVector, float fov,
                    float near, float far, float aspectRatio);

    glm::vec4 projectViewport(glm::vec4 point, float x, float y, int width, int height);
}

#endif //COMPUTERGRAPHICSPRACTICE_CAMERATRANSFORM_H
