#pragma once

#include <macro_list.h>
#include <utility.h>

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

template <class Record, template <int> class Find>
struct __search_struct__;

#define size_(array) sizeof(array) / sizeof(*array)
#define field_type(struct_name, field) decltype(struct_name().field)
#define enum_to_int(enum_name, id) static_cast<int>(enum_name::id)

#define record_ Record

#define declare_search_fields(...) enum search_fields { __VA_ARGS__ };

#define declare_link(ID)                                                                                    \
    template <>                                                                                             \
    struct link<enum_to_int(search_fields, ID)> {                                                           \
        using type                                                                                          \
            = std::conditional<std::is_same<std::decay<field_type(record_, ID)>::type, char*>::value,       \
                std::string,                                                                                \
                field_type(record_, ID)>::type;                                                             \
    };
#define declare_link_                                                                                       \
    template <int id>                                                                                       \
    struct link {                                                                                           \
        using type = int;                                                                                   \
    };
#define linked_type_(ID) linked_type<enum_to_int(search_fields, ID)>
#define declare_cont_(ID) search_cont<linked_type_(ID)> ID;

#define names ::_names
#define search_struct ::_search_struct

#define declare_find_t(ID)                                                                                  \
    template <>                                                                                             \
    struct find_t<enum_to_int(search_fields, ID)> {                                                         \
        find_t(const search_struct<record_>& parent)                                                        \
            : m_parent(parent)                                                                              \
        {                                                                                                   \
        }                                                                                                   \
        range<enum_to_int(search_fields, ID)> operator()(const linked_type_(ID) & x) const                  \
        {                                                                                                   \
            return m_parent.ID.equal_range(x);                                                              \
        }                                                                                                   \
        const search_struct<record_>& m_parent;                                                             \
    };

#define declare_find_                                                                                       \
    template <int id>                                                                                       \
    struct find_t {                                                                                         \
        find_t(const search_struct<record_>& parent)                                                        \
        {                                                                                                   \
        }                                                                                                   \
        range<id> operator()(const linked_type<id>& x) const                                                \
        {                                                                                                   \
            return range<id>();                                                                             \
        }                                                                                                   \
    };

#define stringize_single_(e) #e,
#define insert_(ID) (ID.insert(std::make_pair((x).ID, pos)));
#define erase_(ID) (ID.erase((x).ID));

#define declare_record(__record) using record_ = __record;

#define db_ref_ __db
#define retval_ __ret
#define find_case_statement(ID)                                                                             \
    case ID: {                                                                                              \
        linked_type_(ID) x;                                                                                 \
        std::cin >> x;                                                                                      \
        retval_ = db_ref_.template find<ID>(x);                                                             \
        break;                                                                                              \
    }
#define find_in_db_ __db_find

#define declare_find_function(...)                                                                          \
    template <template <class> class BinToText>                                                             \
    std::vector<id_type> find_in_db_(                                                                       \
        const basic_database<record_, search_struct, BinToText>& db_ref_, id_type id)                       \
    {                                                                                                       \
        std::vector<id_type> retval_;                                                                       \
        switch (id) {                                                                                       \
            identity_(map_(find_case_statement, __VA_ARGS__)) default:                                      \
            {                                                                                               \
                break;                                                                                      \
            }                                                                                               \
        }                                                                                                   \
        return retval_;                                                                                     \
    }

#define declare_searchable(...)                                                                             \
    declare_search_fields(__VA_ARGS__);                                                                     \
    namespace {                                                                                             \
        constexpr const char* const _names[] = {identity_(map_(stringize_single_, __VA_ARGS__))};           \
    };                                                                                                      \
    declare_link_;                                                                                          \
    identity_(map_(declare_link, __VA_ARGS__));                                                             \
    template <int id>                                                                                       \
    struct find_t;                                                                                          \
    template <template <int> class Find>                                                                    \
    struct __search_struct__<record_, Find> {                                                               \
        identity_(map_(declare_cont_, __VA_ARGS__));                                                        \
        void index_record(const id_type& pos, const record_& x)                                             \
        {                                                                                                   \
            identity_(map_(insert_, __VA_ARGS__));                                                          \
        }                                                                                                   \
        void delete_record(const record_& x)                                                                \
        {                                                                                                   \
            identity_(map_(erase_, __VA_ARGS__));                                                           \
        }                                                                                                   \
        template <int id>                                                                                   \
        std::vector<id_type> find(const linked_type<id>& x) const                                           \
        {                                                                                                   \
            auto found = Find<id>(*this)(x);                                                                \
            std::vector<id_type> retval;                                                                    \
            for (auto i = found.first; i != found.second; ++i)                                              \
                retval.push_back(i->second);                                                                \
            retval.shrink_to_fit();                                                                         \
            return retval;                                                                                  \
        }                                                                                                   \
    };                                                                                                      \
    namespace {                                                                                             \
        template <class Record>                                                                             \
        using _search_struct = __search_struct__<Record, find_t>;                                           \
    }                                                                                                       \
    declare_find_;                                                                                          \
    identity_(map_(declare_find_t, __VA_ARGS__));                                                           \
    declare_find_function(__VA_ARGS__)
