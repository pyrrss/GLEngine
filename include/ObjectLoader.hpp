#ifndef OBJECTLOADER_HPP
#define OBJECTLOADER_HPP

#include <iostream>
#include <memory>

#include "../include/Mesh3D.hpp"

class ObjectLoader
{
    public:
        static std::unique_ptr<Mesh3D> load_object(const std::string& filename);
};

#endif
