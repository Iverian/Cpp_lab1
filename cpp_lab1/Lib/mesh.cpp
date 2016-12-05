#include "mesh.h"
#include "utility.h"

#include <algorithm>

using namespace std;
using namespace helper;

template <class Predicate, class Node_type>
def_cont<id_type> find_temp(def_cont<Node_type>& p_cont, Predicate&& p_pred);

mesh::mesh()
    : m_node_cont()
    , m_fe_cont()
    , m_sfe_cont()
{
}

def_cont<helper::node>& mesh::node_cont()
{
    return m_node_cont;
}

def_cont<helper::finite_elem>& mesh::fe_cont()
{
    return m_fe_cont;
}

def_cont<helper::surface_finite_elem>& mesh::sfe_cont()
{
    return m_sfe_cont;
}

helper::node& mesh::node(const id_type& p_index)
{
    return m_node_cont.at(p_index - 1);
}

helper::finite_elem& mesh::fe(const id_type& p_index)
{
    return m_fe_cont.at(p_index - 1);
}

helper::surface_finite_elem& mesh::sfe(const id_type& p_index)
{
    return m_sfe_cont.at(p_index - 1);
}

template <class Predicate, class Node_type>
def_cont<id_type> find_temp(def_cont<Node_type>& p_cont, Predicate&& p_pred)
{
    def_cont<id_type> retval;
    for (auto i = p_cont.begin(); i != p_cont.end();) {
        auto j = find_if(i, p_cont.end(), p_pred);
        if (j != p_cont.end()) {
            retval.push_back(j->id);
            ++j;
        }
        i = j;
    }
    return move(retval);
}

def_cont<id_type> mesh::get_fe_by_three_nodes(const array<id_type, 3>& p_nodes)
{
    return find_temp(m_fe_cont,
        [&p_nodes](const helper::finite_elem& p_elem) -> auto {
            auto res = true;
            for (auto k = p_nodes.begin(); res && k != p_nodes.end(); ++k) {
                auto l = find(p_elem.nodes.begin(), p_elem.nodes.end(), *k);
                if (l == p_elem.nodes.end())
                    res = false;
            }
            return res;
        });
}

def_cont<id_type> mesh::get_fe_by_edge(const array<id_type, 2>& p_edge)
{
    return find_temp(m_fe_cont,
        [&p_edge](const helper::finite_elem& p_elem) {
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
        [p_id](const helper::surface_finite_elem& p_elem) {
            return p_id == p_elem.surface_id;
        });
}

def_cont<id_type> mesh::get_sfe_nodes_by_surface_id(const id_type& p_id)
{
    def_cont<id_type> retval;
    for (auto i = m_sfe_cont.begin(); i != m_sfe_cont.end();) {
        auto j = find_if(i, m_sfe_cont.end(), [p_id](const helper::surface_finite_elem& p_elem) { return p_id == p_elem.surface_id; });
        if (j != m_sfe_cont.end()) {
            for (auto& k : j->nodes)
                retval.push_back(k);
            ++j;
        }
        i = j;
    }
    return move(retval);
}

def_cont<set<id_type>> mesh::get_cont_neighs()
{
    def_cont<set<id_type>> retval;
    retval.resize(m_node_cont.size());
    for (auto& i : m_fe_cont) {
        auto node_size = i.nodes.size();
        for (size_t j = 0; j != node_size; ++j)
            for (size_t k = 0; k != node_size; ++k) {
                if (k == j)
                    continue;
                retval.at(i.nodes.at(j) - 1).insert(i.nodes.at(k));
				retval.at(i.nodes.at(k) - 1).insert(i.nodes.at(j));
            }
    }
    for (auto& i : m_sfe_cont) {
        auto node_size = i.nodes.size();
        for (size_t j = 0; j != node_size; ++j)
            for (size_t k = 0; k != node_size; ++k) {
                if (k == j)
                    continue;
                retval.at(i.nodes.at(j) - 1).insert(i.nodes.at(k));
				retval.at(i.nodes.at(k) - 1).insert(i.nodes.at(j));
            }
    }
    return move(retval);
}

mesh& mesh::convert_to_square_type()
{
    auto cur_id = m_node_cont.back().id + 1;
    def_cont<helper::node> new_nodes;
    for (auto i = m_fe_cont.begin(); i != m_fe_cont.end(); ++i) {
        for (auto j = i->nodes.begin(); j != i->nodes.end(); ++j) {
            for (auto k = j + 1; k != i->nodes.end(); ++k) {
                auto center = get_center(node(*j).coord, node(*k).coord);
                if (find_if(new_nodes.begin(), new_nodes.end(), [&center](const helper::node& x) { return equal(x.coord, center); }) == new_nodes.end())
                    new_nodes.push_back({ cur_id++, INTERIOR, center });
            }
        }
    }
	for (auto& i : new_nodes)
		m_node_cont.push_back(i);
    return *this;
}
