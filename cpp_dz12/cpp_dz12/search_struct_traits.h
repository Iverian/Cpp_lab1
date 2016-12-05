#pragma once

#include "utility.h"

#include <map>
#include <string>
#include <type_traits>
#include <vector>

#define STRMAXLEN 100

template <int id>
struct link;

template <int id>
using linked_type = typename link<id>::type;
template <class T>
using search_cont = std::multimap<T, id_type>;
template <int id>
using search_iter = typename search_cont<linked_type<id>>::const_iterator;
template <int id>
using range = std::pair<search_iter<id>, search_iter<id>>;

template <class Record>
struct search_struct;

#define record_ Record
#define search_fields_ search_fields
#define search_struct_ search_struct<record_>

#define insert_(ID, pos, record) (ID.insert(std::make_pair((record).ID, pos)))
#define erase_(ID, record) (ID.erase((record).ID))

#define field_type(struct_name, field) decltype(struct_name().field)
#define enum_to_int(enum_name, id) std::underlying_type<enum_name>::type(enum_name::id)
#define declare_search_fields enum search_fields_

#define declare_link(ID)                                                                                    \
    template <>                                                                                             \
    struct link<enum_to_int(search_fields_, ID)> {                                                          \
        using type                                                                                          \
            = std::conditional<std::is_same<std::decay<field_type(record_, ID)>::type, char*>::value,       \
                std::string,                                                                                \
                field_type(record_, ID)>::type;                                                             \
    }

#define linked_type_(ID) linked_type<enum_to_int(search_fields_, ID)>
#define declare_cont(ID) search_cont<linked_type_(ID)> ID

#define search_struct_decl_begin                                                                            \
    template <int id>                                                                                       \
    struct find_t;
#define search_struct_head template<> struct search_struct_
#define search_struct_decl_end

#define declare_find_t(ID)                                                                                  \
    \
template<>                                                                                                  \
        \
struct find_t<enum_to_int(search_fields_, ID)>                                                              \
    {                                                                                                       \
        find_t(search_struct_& parent)                                                                      \
            : m_parent(parent)                                                                              \
        {                                                                                                   \
        }                                                                                                   \
        range<enum_to_int(search_fields_, ID)> operator()(const linked_type_(ID) & x)                       \
        {                                                                                                   \
            return m_parent.ID.equal_range(x);                                                              \
        }                                                                                                   \
        search_struct_& m_parent;                                                                           \
    \
};

#define find_implementation                                                                                 \
    template <int id>                                                                                       \
    std::vector<id_type> find(const linked_type<id>& x)                                                     \
    {                                                                                                       \
        auto found = find_t<id>(*this)(x);                                                                  \
        std::vector<id_type> retval;                                                                        \
        for (auto i = found.first; i != found.second; ++i)                                                  \
            retval.push_back(i.second);                                                                     \
        retval.shrink_to_fit();                                                                             \
        return retval;                                                                                      \
    }

#define declare_search_struct(...)                                                                          \
    template <int id>                                                                                       \
    struct find_t;                                                                                          \
    template <>                                                                                             \
    struct search_struct_ {                                                                                 \
        __VA_ARGS__                                                                                         \
        void index_record(const id_type& pos, const record_& x);                                            \
        void delete_record(const record_& x);                                                               \
        find_implementation                                                                                 \
    }
