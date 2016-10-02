#include "mesh.h"

mesh::mesh()
    : m_node_container()
    , m_fe_container()
    , m_sfe_container()
{
}

default_container<node>& mesh::get_node_container()
{
    return m_node_container;
}

default_container<finite_elem>& mesh::get_fe_container()
{
    return m_fe_container;
}

default_container<surface_finite_elem>& mesh::get_sfe_container()
{
    return m_sfe_container;
}

node& mesh::get_node(const id_type& p_index)
{
	return m_node_container.at(p_index - 1);
}

finite_elem& mesh::get_fe(const id_type& p_index)
{
	return m_fe_container.at(p_index - 1);
}

surface_finite_elem& mesh::get_sfe(const id_type& p_index)
{
	return m_sfe_container.at(p_index - 1);
}
