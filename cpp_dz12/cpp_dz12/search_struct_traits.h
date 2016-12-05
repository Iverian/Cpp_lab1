#pragma once

#include "utility.h"

#include <map>
#include <string>
#include <type_traits>
#include <vector>

#define STRMAXLEN 100

template <int id>
struct link;

template <class T>
using Search_cont = std::multimap<T, id_type>;
template <int id>
using Sc_iter = typename Search_cont<typename link<id>::type>::const_iterator;
template <int id>
using linked_type = typename link<id>::type;
template <int id>
using range = std::pair<Sc_iter<id>, Sc_iter<id>>;

template <class Record>
struct search_struct_traits {
    virtual ~search_struct_traits(){};
    virtual void index_record(const id_type& pos, const Record& x) = 0;
    virtual void delete_record(const Record& x) = 0;
    template <int id>
    std::vector<id_type> find(const LINK_VAL(id) & x)
    {
        return std::vector<id_type>();
    }
};

#define RECORD Record
#define RECORD_ITEM_T(__id__) decltype(RECORD().__id__)

#define DECL_SEARCH_FIELDS enum class search_fields

#define SEARCH_FIELDS search_fields

#define ENUM_VAL(__id__) int(SEARCH_FIELDS::__id__)

#define DECL_SEARCH_STRUCT                                                                                  \
    search_struct:                                                                                          \
    search_struct_traits<RECORD>

#define SEARCH_STRUCT search_struct

#define DECL_LINK(__id__)                                                                                   \
    template <>                                                                                             \
    struct link<ENUM_VAL(__id__)> {                                                                         \
        using type = std::conditional<std::is_same<std::decay<RECORD_ITEM_T(__id__)>::type, char*>::value,  \
            std::string,                                                                                    \
            RECORD_ITEM_T(__id__)>::type;                                                                   \
    }

#define LINK_VAL(__id__) link<ENUM_VAL(__id__)>::type

#define DECL_FIND(__id__)                                                                                   \
    \
template<>                                                                                                  \
        \
struct SEARCH_STRUCT::find_t<ENUM_VAL(__id__)>                                                              \
    {                                                                                                       \
        find_t(SEARCH_STRUCT& parent)                                                                       \
            : m_parent(parent)                                                                              \
        {                                                                                                   \
        }                                                                                                   \
        range<ENUM_VAL(__id__)> operator()(const LINK_VAL(__id__) & x)                                      \
        {                                                                                                   \
            return m_parent.__id__.equal_range(x);                                                          \
        }                                                                                                   \
    \
private:                                                                                                    \
        SEARCH_STRUCT& m_parent;                                                                            \
    \
};

#define FIND_IMPL                                                                                           \
    template <int id>                                                                                       \
    std::vector<id_type> SEARCH_STRUCT::find(const LINK_VAL(id) & x)                                        \
    {                                                                                                       \
        auto found = find_t<id>(*this)(x);                                                                  \
        std::vector<id_type> retval;                                                                        \
        for (auto i = found.first; i != found.second; ++i)                                                  \
            retval.push_back(i.second);                                                                     \
        retval.shrink_to_fit();                                                                             \
        return retval;                                                                                      \
    }

#define DECL_CONT(__id__) Search_cont<LINK_VAL(__id__)> __id__

#define DECL_ALL(__id__)                                                                                    \
    DECL_LINK(__id__);                                                                                      \
    DECL_FIND(__id__)
