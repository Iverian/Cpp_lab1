#pragma once

#include <cstdint>
#include <vector>

using id_type = uint32_t;
using point = std::vector<double>;
using node_id_list = std::vector<id_type>;

template <class T>
using def_cont = std::vector<T>;

enum node_type {
    NIL,
    INTERIOR,
    VERTEX
};

namespace helper {
struct node {
    id_type id;
    node_type type;
    point coord;
	node(id_type p_id = 0, node_type p_type = NIL, point p_coord = point());
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
}
