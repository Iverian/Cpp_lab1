#pragma once

#include "helper_class.h"

#include <list>
#include <vector>
#include <set>
#include <array>



class mesh {
public:
    mesh();
    def_cont<node>& get_node_container();
    def_cont<finite_elem>& get_fe_container();
    def_cont<surface_finite_elem>& get_sfe_container();

    node& get_node(const id_type& p_index);
    finite_elem& get_fe(const id_type& p_index);
    surface_finite_elem& get_sfe(const id_type& p_index);

    def_cont<id_type> get_fe_by_three_nodes(const std::array<const id_type&, 3>& p_nodes);
	def_cont<id_type> get_fe_by_edge(const std::array<const id_type&, 2>& p_edge);
	def_cont<id_type> get_sfe_by_surface_id(const id_type& p_id);
	def_cont<id_type> get_sfe_nodes_by_surface_id(const id_type &p_id);
	def_cont<std::set<id_type>> get_cont_neighs();
	mesh& convert_to_square_type();
private:
    def_cont<node> m_node_cont;
    def_cont<finite_elem> m_fe_cont;
    def_cont<surface_finite_elem> m_sfe_cont;
};
