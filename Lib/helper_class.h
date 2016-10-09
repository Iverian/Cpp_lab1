#pragma once

#include <cstdint>
#include <vector>

using id_type = uint32_t;
using point = std::vector<double>;
using node_id_list = std::vector<id_type>;

enum node_type {
	NIL,
	INTERIOR, 
	VERTEX
};

struct node {
    id_type id;
    node_type type;
	point coord;
};

struct finite_elem {
    id_type id;
    id_type surface_id;
    node_id_list nodes;
};

struct surface_finite_elem {
    id_type id;
    id_type surface_id;
    node_id_list nodes;
};
