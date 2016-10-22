#pragma once

#include "utility.h"

#include <map>

#define def_link(__id__, __mapped_type__) \
    template <>                           \
    struct link<__id__> {                 \
        using value = __mapped_type__;    \
    }

#define def_find(__param__)                                                                                \
    template <>                                                                                            \
    Search_struct::range<(int)search_fields::__param__>                                                    \
    Search_struct::find<(int)search_fields::__param__>(const linked_val<(int)search_fields::__param__>& x) \
    {                                                                                                      \
        return __param__.equal_range(x);                                                                   \
    }

#define def_all(__id__, __mapped_type__)                   \
    def_link((int)search_fields::__id__, __mapped_type__); \
    def_find(__id__)

template <int Param>
struct link;

template <class T>
using Search_cont = std::multimap<T, id_type>;
template <int Param>
using Sc_iter = typename Search_cont<typename link<Param>::value>::iterator;

template <class Record>
struct search_struct_traits {
	template <int Param>
	using range = std::pair<Sc_iter<Param>, Sc_iter<Param>>;
	template <int Param>
	using linked_val = typename link<Param>::value;

    virtual ~search_struct_traits() {};
    virtual void index_record(const id_type& pos, const Record& x) = 0;
    virtual void delete_record(const Record& x) = 0;
    template <int Param>
    range<Param> find(const linked_val<Param>& x)
    {
        return make_pair(Sc_iter<Param>(), Sc_iter<Param>());
    }
};

