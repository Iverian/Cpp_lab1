#pragma once

#include "mesh.h"
#include "mesh_loader.h"

class ANEU_mesh_loader : public mesh_loader {
public:
    ANEU_mesh_loader();
	mesh load_mesh(const std::string& p_aneu_filename) override;
};
