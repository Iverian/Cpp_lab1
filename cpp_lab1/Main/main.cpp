#include <iostream>
#include "mesh_loader.h"
#include "utility.h"
#include "exceptions.h"
#include "mesh.h"
#include "ANEU_mesh_loader.h"
#include <fstream>

int main(int argc, char* argv[]) {
	std::cout << "hi"<<std::endl;
	int c;
	ANEU_mesh_loader my_mesh_loader;
	auto my_mesh = my_mesh_loader.load_mesh("cone.aneu");
	std::cin >> c;
	while (c)
	{
		switch (c)
		{
		case 1:
		{
			int a, b, c;
			int size = my_mesh.get_node_container().size();
			std::cin >> a, b, c;
			if (a <= size && b <= size &&c <= size)
			{
				print_to_file("fe_by_three_nodes.txt", my_mesh.get_fe_by_three_nodes({ a, b, c }));
			}
			break;
		}
		case 2:
		{
			int a, b;
			int size = my_mesh.get_node_container().size();
			std::cin >> a, b;
			if (a <= size && b <= size)
			{
				print_to_file("fe_by_edge.txt", my_mesh.get_fe_by_edge({ a, b }));
			}
				break;
		}
		case 3:
		{
			int id;
			std::cin >> id;
			print_to_file("sfe_by_surface.txt", my_mesh.get_sfe_by_surface_id(id));
			break;
		}
		case 4:
		{
			int id;
			std::cin >> id;
			print_to_file("sfe_nodes_by_surface.txt", my_mesh.get_sfe_nodes_by_surface_id(id));
			break;
		}
		case 5:
		{
			my_mesh.get_cont_neighs();
		}
		}
		std::cin >> c;

	}
	return 0;
}