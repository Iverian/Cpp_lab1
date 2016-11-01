#include "ANEU_mesh_loader.h"
#include "exceptions.h"

#include <fstream>

using namespace std;

unique_ptr<ANEU_mesh_loader> ANEU_mesh_loader::_instance(new ANEU_mesh_loader());

ANEU_mesh_loader::ANEU_mesh_loader()
{
}

ANEU_mesh_loader& ANEU_mesh_loader::instance()
{
	return *_instance;
}

mesh ANEU_mesh_loader::load_mesh(const std::string& p_aneu_filename)
{
    mesh retval;
    ifstream mesh_file(p_aneu_filename);
    check_if(!mesh_file.is_open(), "unable to open file: " + p_aneu_filename);
    uint32_t node_count, fe_count, sfe_count;
    uint32_t dots_in_node, nodes_in_fe, nodes_in_sfe;

    mesh_file >> node_count >> dots_in_node;
    for (id_type id = 1; id <= node_count; ++id) {
        helper::node input;
        input.coord.resize(dots_in_node);
        for (uint32_t i = 0; i < dots_in_node; ++i)
            mesh_file >> input.coord.at(i);
        input.id = id;
        input.type = VERTEX;
        retval.node_cont().push_back(input);
    }
    retval.node_cont().shrink_to_fit();

    mesh_file >> fe_count >> nodes_in_fe;
    for (id_type id = 1; id <= fe_count; ++id) {
        helper::finite_elem input;
        mesh_file >> input.surface_id;
        input.nodes.resize(nodes_in_fe);
        for (uint32_t i = 0; i < nodes_in_fe; ++i) {
            mesh_file >> input.nodes.at(i);
            retval.node(input.nodes.at(i)).type = INTERIOR;
        }
        input.id = id;
        retval.fe_cont().push_back(input);
    }
    retval.fe_cont().shrink_to_fit();

    mesh_file >> sfe_count >> nodes_in_sfe;
    for (id_type id = 1; id <= sfe_count; ++id) {
        helper::surface_finite_elem input;
        mesh_file >> input.surface_id;
        input.nodes.resize(nodes_in_sfe);
        for (uint32_t i = 0; i < nodes_in_sfe; ++i) {
            mesh_file >> input.nodes.at(i);
            retval.node(input.nodes.at(i)).type = VERTEX;
        }
        input.id = id;
    }
    retval.sfe_cont().shrink_to_fit();

    return move(retval);
}
