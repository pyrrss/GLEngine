#include "../include/Camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


Camera::Camera()
{
    m_eye = glm::vec3(0.0f, 0.0f, 0.0f);
    m_view_direction = glm::vec3(0.0f, 0.0f, -1.0f);
    m_up = glm::vec3(0.0f, 1.0f, 0.0f);   
}

void Camera::set_projection_matrix(float fov, float aspect_ratio, float near, float far)
{
    m_projection_matrix = glm::perspective(glm::radians(fov), aspect_ratio, near, far);
}

glm::mat4 Camera::get_view_matrix()
{
    return glm::lookAt(m_eye, m_eye + m_view_direction, m_up);
}

glm::mat4 Camera::get_projection_matrix()
{
    return m_projection_matrix;
}

void Camera::move_forward(float delta)
{
    m_eye += m_view_direction * delta;
}

void Camera::move_backward(float delta)
{
    m_eye -= m_view_direction * delta;
}

void Camera::move_left(float delta)
{
    // -> resta vector perpendicular a la direccion de la camara y el vector m_up
    m_eye -= glm::normalize(glm::cross(m_view_direction, m_up)) * delta;
}

void Camera::move_right(float delta)
{
    // -> suma vector perpendicular a la direccion de la camara y el vector m_up
    m_eye += glm::normalize(glm::cross(m_view_direction, m_up)) * delta;
}

void Camera::mouse_look(float x, float y)
{
    // -> se crean matrices de rotacion en x e y (yaw y pitch)
    //    y luego se aplican a la direccion de la camara
    glm::mat4 rotation_matrix_x = glm::rotate(glm::mat4(1.0f), glm::radians(-x), m_up);
    glm::mat4 rotation_matrix_y = glm::rotate(glm::mat4(1.0f), glm::radians(-y), glm::cross(m_view_direction, m_up));

    m_view_direction = glm::vec3(rotation_matrix_x * rotation_matrix_y * glm::vec4(m_view_direction, 0.0f));
    m_view_direction = glm::normalize(m_view_direction);
}

glm::vec3 Camera::get_position()
{
    return m_eye;
}

Camera::~Camera()
{
    std::cout << "Liberando recursos de Camera" << std::endl;
}





