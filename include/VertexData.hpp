#ifndef VERTEX_DATA_HPP
#define VERTEX_DATA_HPP

#include <iostream>
#include <vector>

#include "glad/glad.h"

namespace VertexData
{
    extern std::vector<GLfloat> mesh1_vertex_data;
    extern std::vector<GLfloat> mesh2_vertex_data;
    extern std::vector<GLfloat> mesh3_vertex_data;
    extern std::vector<GLfloat> textured_mesh_vertex_data;
    extern std::vector<GLfloat> vertices;
    extern std::vector<GLfloat> cube_vertex_data;
    extern std::vector<GLfloat> pyramid_vertex_data;
    
    extern std::vector<GLfloat> light_source_vertex_data;
    extern std::vector<GLfloat> light_receiver_vertex_data;

    extern std::vector<GLfloat> floor_vertex_data;
    extern std::vector<GLuint> floor_index_data;
}

#endif 
