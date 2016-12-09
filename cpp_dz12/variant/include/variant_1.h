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

declare_record(computer);
declare_searchable(type, vol, obem, _vol);

