#include "Camera.hpp"

namespace gps {
    float yaw = -90.0f;
    //Camera constructor
    Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp) {
        this->cameraPosition = cameraPosition;
        this->cameraTarget = cameraTarget;
        this->cameraUpDirection = cameraUp;
        this->cameraFrontDirection = glm::normalize(cameraTarget - cameraPosition);
        this->cameraRightDirection = glm::normalize(glm::cross(cameraFrontDirection, cameraUp));
    }

    //return the view matrix, using the glm::lookAt() function
    glm::mat4 Camera::getViewMatrix() {
        cameraTarget = cameraPosition + cameraFrontDirection;
        return glm::lookAt(cameraPosition, cameraTarget, cameraUpDirection);
    }

    //update the camera internal parameters following a camera move event
    void Camera::move(MOVE_DIRECTION direction, float speed) {
        switch (direction) {
        case gps::MOVE_FORWARD:
            cameraPosition += cameraFrontDirection * speed;
            break;
        case gps::MOVE_BACKWARD:
            cameraPosition -= cameraFrontDirection * speed;
            break;
        case gps::MOVE_RIGHT:
            cameraPosition += cameraRightDirection * speed;
            break;
        case gps::MOVE_LEFT:
            cameraPosition -= cameraRightDirection * speed;
            break;
        case gps::MOVE_UP:
            cameraPosition += cameraUpDirection * speed;
            break;
        case gps::MOVE_DOWN:
            cameraPosition -= cameraUpDirection * speed;
            break;
        }
    }
    //update the camera internal parameters following a camera rotate event
    //yaw - camera rotation around the y axis
    //pitch - camera rotation around the x axis
    void Camera::rotate(float pitch, float yaw) {
        // Update camera front, right, and up vectors
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFrontDirection = glm::normalize(front);
        cameraUpDirection = glm::normalize(glm::cross(cameraRightDirection, cameraFrontDirection));
        cameraRightDirection = glm::normalize(glm::cross(cameraFrontDirection, glm::vec3(0.0f, 1.0f, 0.0f)));
    }

    void Camera::setCameraPosition(glm::vec3 cameraPosition) {
        this->cameraPosition = cameraPosition;
    }

    void Camera::setCameraFrontDirection(glm::vec3 cameraFrontDirection) {
        this->cameraFrontDirection = cameraFrontDirection;
    }

    void Camera::setCameraRightDirection(glm::vec3 cameraRightDirection) {
        this->cameraRightDirection = cameraRightDirection;
    }

    void Camera::setCameraTarget(glm::vec3 cameraTarget) {
        this->cameraTarget = cameraTarget;
    }

    void Camera::setCameraUp(glm::vec3 cameraUp) {
        this->cameraUpDirection = cameraUp;
    }

    void Camera::cameraPresentation()
    {
        if (glfwGetTime() < 8.0f) 
        {
            this->rotate(0.0f, yaw);
            yaw += 0.25f;
        }
        if (glfwGetTime() >= 8.0f && glfwGetTime() < 10.0f)
            this->move(gps::MOVE_RIGHT, 0.025f);
        if (glfwGetTime() >= 10.0f && glfwGetTime() < 15.0f)
            this->move(gps::MOVE_FORWARD, 0.025f);
        if (glfwGetTime() >= 15.0f && glfwGetTime() < 16.0f) 
        {
            this->rotate(0.0f, yaw);
            yaw -= 0.25f;
        }
    }
}
