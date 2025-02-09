#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <iostream>
#include <glm/glm.hpp>

class Camera
{
    private:
        glm::vec3 m_eye;
        glm::vec3 m_view_direction;
        glm::vec3 m_up;
 
        glm::mat4 m_projection_matrix;

    public:
        Camera();
        ~Camera();
        void set_projection_matrix(float fov, float aspect_ratio, float near, float far);
        glm::mat4 get_view_matrix();
        glm::mat4 get_projection_matrix();
        void move_forward(float delta);
        void move_backward(float delta);
        void move_left(float delta);
        void move_right(float delta);

        void mouse_look(float x, float y);

        glm::vec3 get_position();
};

#endif
















