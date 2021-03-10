#include "Camera.hpp"

namespace gps {

    //Camera constructor
    Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp) {

        this->cameraPosition = cameraPosition;
        this->cameraTarget = cameraTarget;
        this->cameraUpDirection = cameraUp;
        this->cameraFrontDirection = glm::normalize(cameraTarget - cameraPosition);
        this->cameraRightDirection = glm::cross(cameraFrontDirection, cameraUpDirection);
    }

    //return the view matrix, using the glm::lookAt() function
    glm::mat4 Camera::getViewMatrix() {

        return glm::lookAt(cameraPosition, cameraTarget, glm::vec3(0.0f, 1.0f, 0.0f));

    }

    //update the camera internal parameters following a camera move event
    void Camera::move(MOVE_DIRECTION direction, float speed) {

        if (direction == MOVE_FORWARD) {
            cameraPosition += cameraFrontDirection * speed;
        }
        else if (direction == MOVE_BACKWARD) {
            cameraPosition -= cameraFrontDirection * speed;
        }
        else if (direction == MOVE_LEFT) {
            cameraPosition -= cameraRightDirection * speed;
        }
        else if (direction == MOVE_RIGHT) {
            cameraPosition += cameraRightDirection * speed;
        }
        else if (direction == UP) {
            cameraPosition += cameraUpDirection * speed;
        }
        else if (direction == DOWN) {
            cameraPosition -= cameraUpDirection * speed;
        }
        cameraTarget = cameraPosition + cameraFrontDirection;
    }

    //update the camera internal parameters following a camera rotate event
    //yaw - camera rotation around the y axis
    //pitch - camera rotation around the x axis
    void Camera::rotate(float pitch, float yaw) {

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
        glm::vec3 front(0.0f, 0.0f, 0.0f);
        front.x = cos(pitch) * sin(yaw);
        front.y = sin(pitch);
        front.z = cos(pitch) * cos(yaw);
        cameraFrontDirection = normalize(front);
        cameraTarget = cameraPosition + cameraFrontDirection;
        cameraRightDirection = glm::normalize(glm::cross(cameraFrontDirection, glm::vec3(0.0f, 1.0f, 0.0f)));
    }
}