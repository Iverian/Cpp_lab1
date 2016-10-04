#pragma once

#include "mesh.h"

#include <string>

class mesh_loader {
public:
    virtual mesh load_mesh(const std::string& p_filename) = 0;
    virtual ~mesh_loader() {}
};
