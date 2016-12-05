#pragma once

#include "search_struct_traits.h"

struct RECORD {
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

DECL_SEARCH_FIELDS{type, vol, obem, _vol};

DECL_LINK(type, char*);
DECL_LINK(vol, RECORD_ITEM_T(vol));
DECL_LINK(obem, RECORD_ITEM_T(obem));
DECL_LINK(_vol, RECORD_ITEM_T(_vol));

struct DECL_SEARCH_STRUCT {
    void index_record(const id_type& pos, const RECORD& x) override;
    void delete_record(const RECORD& x) override;

    FIND_IMPL

private:
    template <int id>
    struct find_t;

    Search_cont<LINK_VAL(type)> type;
    Search_cont<LINK_VAL(vol)> vol;
    Search_cont<LINK_VAL(obem)> obem;
    Search_cont<LINK_VAL(_vol)> _vol;
};

DECL_FIND(type)
DECL_FIND(vol)
DECL_FIND(obem)
DECL_FIND(_vol)
