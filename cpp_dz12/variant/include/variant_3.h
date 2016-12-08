#pragma once

#include <date.h>
#include <search_struct_traits.h>

struct drug {
    int pharmacy_id;
    char drug_name[STRMAXLEN];
    int pack_count_avail;
    double pack_price;
    date arrival_date;
    int spoil_time;
};

declare_record(drug)

declare_search_fields(pharmacy_id, drug_name, arrival_date)

declare_link(pharmacy_id)
declare_link(drug_name)
declare_link(arrival_date)

search_struct_decl_begin

declare_search_struct(
	declare_cont(pharmacy_id)
	declare_cont(drug_name)
	declare_cont(arrival_date)
)

search_struct_decl_end

declare_find_t(pharmacy_id)
declare_find_t(drug_name)
declare_find_t(arrival_date)


