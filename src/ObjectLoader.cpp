#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

#include <vector>
#include <glm/glm.hpp>

#include "../include/ObjectLoader.hpp"
#include "../include/glad/glad.h"
#include "../include/Mesh3D.hpp"

std::unique_ptr<Mesh3D> ObjectLoader::load_object(const std::string& filename)
{
    std::vector<GLfloat> vertex_data;
    std::vector<GLuint> index_data;

    std::cout << "Cargando modelo 3D: " << filename << std::endl;

    std::ifstream file(filename);

    if(!file.is_open())
    {
        std::cerr << "Error al abrir el archivo: " << filename << std::endl;
        return nullptr;
    }

    std::string line;
    while(std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string prefix;

        ss >> prefix;

        if(prefix == "v")
        {
            float x, y, z;
            ss >> x >> y >> z;
            vertex_data.push_back(x);
            vertex_data.push_back(y);
            vertex_data.push_back(z);
        }
        else if(prefix == "f")
        {
            std::string vertex;
            GLuint idx1, idx2, idx3;

            // Leemos los tres vértices de la cara
            ss >> vertex;
            idx1 = std::stoi(vertex.substr(0, vertex.find('/'))) - 1;  // Índice del primer vértice

            ss >> vertex;
            idx2 = std::stoi(vertex.substr(0, vertex.find('/'))) - 1;  // Índice del segundo vértice

            ss >> vertex;
            idx3 = std::stoi(vertex.substr(0, vertex.find('/'))) - 1;  // Índice del tercer vértice

            // Guardamos los índices en el vector de índices
            index_data.push_back(idx1);
            index_data.push_back(idx2);
            index_data.push_back(idx3);
        }


    }

    std::unique_ptr<Mesh3D> mesh = std::make_unique<Mesh3D>();
    mesh->create_mesh(vertex_data, index_data);
    mesh->translate(0.0f, 0.0f, -5.0f);

    std::cout << "Modelo cargado exitosamente" << std::endl;

    return mesh;
}
