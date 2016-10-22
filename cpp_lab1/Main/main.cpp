#include "ANEU_mesh_loader.h"
#include "mesh.h"
#include "utility.h"

#include <iostream>

using namespace std;

#define INV cout << ">"

static constexpr auto help_msg =	"0 - exit\n"
									"1 - get finite elem by 3 nodes\n"
									"2 - get finite elem by edge\n"
									"3 - get surface finite elems by surface id\n"
									"4 - get surface finite element nodes by surface id\n"
									"5 - get neighbours of nodes";

enum actions
{
	EXIT = 0,
	GET_FE_BY_3_NODES = 1,
	GET_FE_BY_EDGE = 2,
	GET_SFE_BY_SURF_ID = 3,
	GET_SFE_NODES_BY_SURF_ID = 4,
	GET_CONT_NEIGH= 5
};

using namespace std;

int main()
{
    int selector;
    auto my_mesh = ANEU_mesh_loader().load_mesh("cone.aneu");
	cout << help_msg << endl;
	for (INV, cin >> selector; selector != EXIT; INV, cin >> selector) {
        switch (selector) {
        case GET_FE_BY_3_NODES: {
            std::array<id_type, 3> x;
            auto size = my_mesh.node_cont().size();
			cout << "\tInput 3 nodes id from 1 to " << size << " : ";
            for (auto& i : x)
                cin >> i;
            if (x[0] <= size && x[1] <= size && x[2] <= size)
                print_to_file("fe_by_three_nodes.txt", my_mesh.get_fe_by_three_nodes(x));
            break;
        }
        case GET_FE_BY_EDGE: {
			std::array<id_type, 2> x;
            auto size = my_mesh.node_cont().size();
			cout << "\tInput 2 nodes id from 1 to " << size << " : ";
			for (auto& i : x)
				cin >> i;
            if (x[0] <= size && x[1] <= size)
                print_to_file("fe_by_edge.txt", my_mesh.get_fe_by_edge(x));
            break;
        }
        case GET_SFE_BY_SURF_ID: {
            id_type id;
			cout << "\tInput sfe surface id : ";
            cin >> id;
            print_to_file("sfe_by_surface.txt", my_mesh.get_sfe_by_surface_id(id));
            break;
        }
        case GET_SFE_NODES_BY_SURF_ID: {
            id_type id;
			cout << "\tInput sfe surface id : ";
            cin >> id;
            print_to_file("sfe_nodes_by_surface.txt", my_mesh.get_sfe_nodes_by_surface_id(id));
            break;
        }
        case GET_CONT_NEIGH: {
            print_to_file("nodes_neigh.txt", my_mesh.get_cont_neighs());
        }
		default:
			break;
        }
    }
    return 0;
}