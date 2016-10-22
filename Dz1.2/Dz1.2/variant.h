#pragma once

#include "DatabaseBase.h"

#include <iostream>
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

#define MAXLEN 100

#define _VAR_1
//#define _VAR_2
//#define _VAR_3

#ifdef _VAR_1

struct Record {
    int code;
    char model[MAXLEN];
    char name[MAXLEN];
    char type[MAXLEN];
    int chast;
    int vol;
    int obem;
    int _vol;
    int cost;
    int col_vo;
};

enum class search_fields {
    type,
    vol,
    obem,
    _vol
};

struct Search_struct : search_struct_traits<Record> {
    void index_record(const id_type& pos, const Record& x) override;
    void delete_record(const Record& x) override;
    ~Search_struct();

    template <int Param>
    range<Param> find(const linked_val<Param>& x);

private:
    Search_cont<char*> type;
    Search_cont<int> vol;
    Search_cont<int> _vol;
    Search_cont<int> obem;
};

def_all(type, char*);
def_all(vol, int);
def_all(_vol, int);
def_all(obem, int);

class Database : public DatabaseBase<Record, Search_struct>
{
	
};

#elif defined(_VAR_2)

#elif defined(_VAR_3)

#endif

std::ostream& operator<<(std::ostream& os, const Record& x);