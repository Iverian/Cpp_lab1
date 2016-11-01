#pragma once

#include <memory>

#include "mesh.h"
#include "mesh_loader.h"

class ANEU_mesh_loader : public mesh_loader {
public:
	static ANEU_mesh_loader& instance();
	mesh load_mesh(const std::string& p_aneu_filename) override;
private:
    ANEU_mesh_loader();
	static std::unique_ptr<ANEU_mesh_loader> _instance;
};
