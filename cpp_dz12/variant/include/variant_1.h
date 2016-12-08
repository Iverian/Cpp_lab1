#pragma once

#include <search_struct_traits.h>

struct computer {
    int code;
    char model[STRMAXLEN];
    char name[STRMAXLEN];
    char type[STRMAXLEN];
    int chast;
    int vol;
    int obem;
    int _vol;
    int cost;
    int col_vo;
};

declare_record(computer)

declare_search_fields(type, vol, obem, _vol)

declare_link(type)
declare_link(vol)
declare_link(obem)
declare_link(_vol)

search_struct_decl_begin

declare_search_struct(
    declare_cont(type)
    declare_cont(vol)
    declare_cont(obem)
    declare_cont(_vol)
)

search_struct_decl_end

declare_find_t(type)
declare_find_t(vol)
declare_find_t(obem)
declare_find_t(_vol)
