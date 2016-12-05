#pragma once

#include "helper_class.h"

#include <array>
#include <set>
#include <vector>

class mesh {
public:
    mesh();
    def_cont<helper::node>& node_cont();
    def_cont<helper::finite_elem>& fe_cont();
    def_cont<helper::surface_finite_elem>& sfe_cont();

    helper::node& node(const id_type& p_index);
    helper::finite_elem& fe(const id_type& p_index);
    helper::surface_finite_elem& sfe(const id_type& p_index);

    def_cont<id_type> get_fe_by_three_nodes(const std::array<id_type, 3>& p_nodes);
    def_cont<id_type> get_fe_by_edge(const std::array<id_type, 2>& p_edge);
    def_cont<id_type> get_sfe_by_surface_id(const id_type& p_id);
    def_cont<id_type> get_sfe_nodes_by_surface_id(const id_type& p_id);
    def_cont<std::set<id_type>> get_cont_neighs();
    mesh& convert_to_square_type();

private:
    def_cont<helper::node> m_node_cont;
    def_cont<helper::finite_elem> m_fe_cont;
    def_cont<helper::surface_finite_elem> m_sfe_cont;
};
