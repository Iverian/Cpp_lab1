#include "mesh.h"

#include <algorithm>
#include <array>

using namespace std;

template <class Function, class Node_type>
def_cont<id_type> find_temp(def_cont<Node_type>& cont, Function&& lambda);

mesh::mesh()
    : m_node_cont()
    , m_fe_cont()
    , m_sfe_cont()
{
}

def_cont<node>& mesh::get_node_container()
{
    return m_node_cont;
}

def_cont<finite_elem>& mesh::get_fe_container()
{
    return m_fe_cont;
}

def_cont<surface_finite_elem>& mesh::get_sfe_container()
{
    return m_sfe_cont;
}

node& mesh::get_node(const id_type& p_index)
{
    return m_node_cont.at(p_index - 1);
}

finite_elem& mesh::get_fe(const id_type& p_index)
{
    return m_fe_cont.at(p_index - 1);
}

surface_finite_elem& mesh::get_sfe(const id_type& p_index)
{
    return m_sfe_cont.at(p_index - 1);
}

template <class Function, class Node_type>
def_cont<id_type> find_temp(def_cont<Node_type>& cont, Function&& lambda)
{
    def_cont<id_type> retval;
    for (auto i = cont.begin(); i != cont.end();) {
        auto j = find_if(i, cont.end(), lambda);
        if (j != cont.end()) {
            retval.push_back(j->id);
            ++j;
        }
        i = j;
    }
    return move(retval);
}

def_cont<id_type> mesh::get_fe_by_three_nodes(const std::array<const id_type&, 3>& p_nodes)
{
    return find_temp(m_fe_cont,
        [&p_nodes](const finite_elem& p_elem) -> auto {
            auto res = true;
            for (auto k = p_nodes.begin(); res && k != p_nodes.end(); ++k) {
                auto l = find(p_elem.nodes.begin(), p_elem.nodes.end(), *k);
                if (l == p_elem.nodes.end())
                    res = false;
            }
            return res;
        });
}

def_cont<id_type> mesh::get_fe_by_edge(const std::array<const id_type&, 2>& p_edge)
{
    return find_temp(m_fe_cont,
        [&p_edge](const finite_elem& p_elem) {
            auto res = true;
            for (auto& k : p_edge) {
                auto l = find(p_elem.nodes.begin(), p_elem.nodes.end(), k);
                if (l == p_elem.nodes.end()) {
                    res = false;
                    break;
                }
            }
            return res;
        });
}

def_cont<id_type> mesh::get_sfe_by_surface_id(const id_type& p_id)
{
    return find_temp(m_sfe_cont,
        [p_id](const surface_finite_elem& p_elem) {
            return p_id == p_elem.surface_id;
        });
}

def_cont<id_type> mesh::get_sfe_nodes_by_surface_id(const id_type& p_id)
{
    def_cont<id_type> retval;
    for (auto i = m_sfe_cont.begin(); i != m_sfe_cont.end();) {
        auto j = find_if(i, m_sfe_cont.end(), [p_id](const surface_finite_elem& p_elem) { return p_id == p_elem.surface_id; });
        if (j != m_sfe_cont.end()) {
            for (auto& k : j->nodes)
                retval.push_back(k);
            ++j;
        }
        i = j;
    }
    return move(retval);
}

def_cont<set<id_type>> mesh::get_n_cont()
{
    def_cont<set<id_type>> retval;
    retval.reserve(m_node_cont.size());
    for (auto& i : m_fe_cont) {
        auto node_size = i.nodes.size();
        for (size_t j = 0; j != node_size; ++j)
            for (size_t k = 0; k != node_size; ++k) {
                if (k == j)
                    continue;
                retval.at(i.nodes.at(j) - 1).insert(i.nodes.at(k));
            }
    }
    for (auto& i : m_sfe_cont) {
        auto node_size = i.nodes.size();
        for (size_t j = 0; j != node_size; ++j)
            for (size_t k = 0; k != node_size; ++k) {
                if (k == j)
                    continue;
                retval.at(i.nodes.at(j) - 1).insert(i.nodes.at(k));
            }
    }
    return move(retval);
}
