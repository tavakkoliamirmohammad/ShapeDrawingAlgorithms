#include "CameraTransform.h"
#include <vector>
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"

using namespace std;

glm::vec4 CameraTransform::rotateAroundPoint(glm::vec4 point, glm::vec3 pivot, float angle) {
    glm::mat4 T = glm::translate(glm::mat4(1.0), pivot);
    T = glm::rotate(T, angle * glm::pi<float>() / 180, glm::vec3(0, 0, 1));
    T = glm::translate(T, -pivot);
    return T * point;
}

glm::vec4 CameraTransform::scaleAlongVector(glm::vec4 point, glm::vec3 axisVector, glm::vec3 scaleVector) {
    float angle = acos(axisVector[2] / sqrt(pow(axisVector[0], 2) + pow(axisVector[1], 2) + pow(axisVector[2], 2)));
    glm::mat4 T = glm::rotate(glm::mat4(1.0), angle, glm::vec3(0, 0, 1));
    T = glm::scale(T, scaleVector);
    T = glm::rotate(T, -angle, glm::vec3(0, 0, 1));
    return T * point;
}

glm::vec4
CameraTransform::projectOnCamera(glm::vec4 point, glm::vec3 cameraPosition, glm::vec3 lookAtPoint, glm::vec3 upVector,
                                 float fov,
                                 float near, float far, float aspectRatio) {
    float f = 1 / tanf(fov * glm::pi<float>() / 360);
    glm::mat4x4 A = glm::mat4x4(glm::vec4(f / aspectRatio, 0, 0, 0),
                                glm::vec4(0, f, 0, 0),
                                glm::vec4(0, 0, (far + near) / (near - far), -1),
                                glm::vec4(0, 0, 2 * far * near / (near - far), 0));

    glm::vec3 d = lookAtPoint - cameraPosition;
    glm::vec3 az = glm::normalize(d);
    glm::vec3 vPrime = glm::normalize(upVector);
    glm::vec3 ax = glm::cross(vPrime, az);
    glm::vec3 ay = glm::cross(az, ax);

    glm::mat3x3 R = glm::mat3x3(ax, ay, az);
    glm::mat3x3 transposeR = glm::transpose(R);

    glm::vec3 translationPart = -glm::transpose(R) * cameraPosition;
    glm::mat4x4 inverseTCam = glm::mat4x4(glm::vec4(transposeR[0][0], transposeR[0][1], transposeR[0][2], 0),
                                          glm::vec4(transposeR[1][0], transposeR[1][1], transposeR[1][2], 0),
                                          glm::vec4(transposeR[2][0], transposeR[2][1], transposeR[2][2], 0),
                                          glm::vec4(translationPart[0], translationPart[1], translationPart[2], 1));
    return A * inverseTCam * point;
}

glm::vec4 CameraTransform::projectViewport(glm::vec4 point, float x, float y, int width, int height) {
    glm::mat4x4 A = glm::mat4x4(glm::vec4(width / 2.0, 0, 0, 0),
                                glm::vec4(0, height / 2.0, 0, 0),
                                glm::vec4(0, 0, 1.0 / 2.0, 0),
                                glm::vec4(x + width / 2.0, y + height / 2.0, 1.0 / 2.0, 1));
    return A * point;
}

int main() {
    std::vector<glm::vec4> vertices;

    vertices.emplace_back(0, 0, 1, 1);
    vertices.emplace_back(-1, 0, -1, 1);
    vertices.emplace_back(-1, -1, 1, 1);
    vertices.emplace_back(1, 1, 1, 1);
    vertices.emplace_back(0, -1, 0, 1);

    glm::vec4 p1 = glm::vec4(2, 2, 2, 1);
    glm::vec4 p2 = glm::vec4(5, 5, -5, 1);
    glm::vec4 v1 = glm::vec4(1, 2, 3, 0);
    float angle = 45.0;
    cout << "Rotation around point: " << glm::to_string(p1) << " by angle " << angle << endl;
    for (glm::vec4 vertex : vertices) {
        cout << glm::to_string(vertex) << " --> "
             << glm::to_string(CameraTransform::rotateAroundPoint(vertex, p1, angle)) << endl;
    }

    cout << endl;

    glm::vec3 scaleVector = glm::vec3(4, 4, 4);
    cout << "Scale along vector: " << glm::to_string(v1) << " by scale vector " <<  glm::to_string(scaleVector) << endl;
    for (glm::vec4 vertex : vertices) {
        cout << glm::to_string(vertex) << " --> "
             << glm::to_string(CameraTransform::scaleAlongVector(vertex, v1, scaleVector)) << endl;
    }
    cout << endl;

    glm::vec3 lookAt = glm::vec4(0, 0, 0, 1);
    glm::vec3 upVector = glm::vec4(0, 1, 0, 0);
    cout << "Project on  camera placed at: " << glm::to_string(p2) << " looking through " << glm::to_string(lookAt)
         << endl;
    for (glm::vec4 vertex : vertices) {
        cout << glm::to_string(vertex) << " --> "
             << glm::to_string(CameraTransform::projectOnCamera(vertex, p2, lookAt, upVector, 60, 0.1, 1000, 2))
             << endl;
    }
    cout << endl;

    cout << "Viewport position " << endl;

    for (glm::vec4 vertex: vertices) {
        cout << glm::to_string(vertex) << " --> "
             << glm::to_string(CameraTransform::projectViewport(vertex, 0, 0, 800, 600)) << endl;
    }

    return 0;

}