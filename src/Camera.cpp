#include "../include/Camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glm/ext/matrix_transform.hpp>
#include <glm/matrix.hpp>

Camera::Camera()
{
    eye = glm::vec3(0.0f, 0.0f, 0.0f);
    view_direction = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 Camera::get_view_matrix()
{
    return glm::lookAt(eye, eye + view_direction, up);
}

void Camera::move_forward(float delta)
{
    eye += view_direction * delta;
}

void Camera::move_backward(float delta)
{
    eye -= view_direction * delta;
}

void Camera::move_left(float delta)
{
    // -> resta vector perpendicular a la direccion de la camara y el vector up
    eye -= glm::normalize(glm::cross(view_direction, up)) * delta;
}

void Camera::move_right(float delta)
{
    // -> suma vector perpendicular a la direccion de la camara y el vector up
    eye += glm::normalize(glm::cross(view_direction, up)) * delta;
}

void Camera::mouse_look(float x, float y)
{
    std::cout << x << " " << y << std::endl;

    // -> se crean matrices de rotacion en x e y (yaw y pitch)
    //    y luego se aplican a la direccion de la camara
    glm::mat4 rotation_matrix_x = glm::rotate(glm::mat4(1.0f), glm::radians(-x), up);
    glm::mat4 rotation_matrix_y = glm::rotate(glm::mat4(1.0f), glm::radians(-y), glm::cross(view_direction, up));

    view_direction = glm::vec3(rotation_matrix_x * rotation_matrix_y * glm::vec4(view_direction, 0.0f));
    view_direction = glm::normalize(view_direction);
}

Camera::~Camera()
{
    std::cout << "Camera destructor called" << std::endl;
}




