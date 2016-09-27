#pragma once

#include <cstdint>
#include <vector>

using id_type = uint32_t;
enum node_type {INTERIOR, VERTEX};
using node_id_list = std::vector<id_type>;

struct Node
{
	id_type id;
	node_type type;
	double x;
	double y;
};

struct Finite_elem
{
	id_type id;
	id_type surface_id;
	node_id_list nodes;
};

struct Surface_finite_elem
{
	id_type id;
	id_type FE_type_id;
	id_type surface_id;
	node_id_list nodes;
};
