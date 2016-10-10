#include "mesh.h"

#include <algorithm>
#include <array>

using namespace std;

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

default_container<finite_elem&> mesh::get_fe_by_three_nodes(const std::array<const id_type&, 3>& p_nodes)
{
    default_container<finite_elem&> retval;
    for (auto i = m_fe_container.begin(); i != m_fe_container.end();) {
        auto j = find_if(i, m_fe_container.end(),
            [&p_nodes](const finite_elem& p_elem) -> auto {
                auto res = true;
                for (auto k = p_nodes.begin(); res && k != p_nodes.end(); ++k) {
                    auto l = find(p_elem.nodes.begin(), p_elem.nodes.end(), *k);
                    if (l == p_elem.nodes.end())
                        res = false;
                }
                return res;
            });
        if (j != m_fe_container.end()) {
            retval.push_back(*j);
            advance(j, 1);
        }
        i = j;
    }
    return move(retval);
}
