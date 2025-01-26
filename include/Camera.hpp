#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <iostream>
#include <glm/glm.hpp>

class Camera
{
    private:
        glm::vec3 eye;
        glm::vec3 view_direction;
        glm::vec3 up;
        
    public:
        Camera();
        ~Camera();
        glm::mat4 get_view_matrix();
        void move_forward(float delta);
        void move_backward(float delta);
        void move_left(float delta);
        void move_right(float delta);

        void mouse_look(float x, float y);
};

#endif
















