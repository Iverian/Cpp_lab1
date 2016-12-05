#pragma once

#include "date.h"
#include "search_struct_traits.h"

struct RECORD {
    int pharmacy_id;
    char drug_name[STRMAXLEN];
    int pack_count_avail;
    double pack_price;
    date arrival_date;
    int spoil_time;

    RECORD()
        : pharmacy_id(0)
        , drug_name()
        , pack_count_avail(0)
        , pack_price(0.)
        , arrival_date()
        , spoil_time(0)
    {
		std::memset(drug_name, 0, STRMAXLEN);
    }
};

DECL_SEARCH_FIELDS{pharmacy_id, drug_name, arrival_date};

DECL_LINK(pharmacy_id);
DECL_LINK(drug_name);
DECL_LINK(arrival_date);

struct DECL_SEARCH_STRUCT {
    void index_record(const id_type& pos, const RECORD& x) override;
    void delete_record(const RECORD& x) override;

    FIND_IMPL

private:
    template <int id>
    struct find_t;

    Search_cont<LINK_VAL(pharmacy_id)> pharmacy_id;
    Search_cont<LINK_VAL(drug_name)> drug_name;
    Search_cont<LINK_VAL(arrival_date)> arrival_date;
};

DECL_FIND(pharmacy_id);
DECL_FIND(drug_name);
DECL_FIND(arrival_date);