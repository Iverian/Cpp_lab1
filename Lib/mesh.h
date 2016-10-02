#pragma once

#include "helper_class.h"

#include <vector>

template <class T>
using default_container = std::vector<T>;

class mesh
{
public:
	mesh();
	default_container<node>& get_node_container();
	default_container<finite_elem>& get_fe_container();
	default_container<surface_finite_elem>& get_sfe_container();
	node& get_node(const id_type& p_index);
	finite_elem& get_fe(const id_type& p_index);
	surface_finite_elem& get_sfe(const id_type& p_index);
private:
	default_container<node> m_node_container;
	default_container<finite_elem> m_fe_container;
	default_container<surface_finite_elem> m_sfe_container;
};
