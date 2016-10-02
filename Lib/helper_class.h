#pragma once

#include <cstdint>
#include <vector>

using id_type = uint32_t;
enum node_type {INTERIOR, VERTEX};
using node_id_list = std::vector<id_type>;

struct node
{
	id_type id;
	node_type type;
	double x;
	double y;
};

struct finite_elem
{
	id_type id;
	id_type surface_id;
	node_id_list nodes;
};

struct surface_finite_elem
{
	id_type id;
	id_type fe_type_id;
	id_type surface_id;
	node_id_list nodes;
};
