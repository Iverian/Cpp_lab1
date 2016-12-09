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

declare_record(drug);
declare_searchable(pharmacy_id, drug_name, arrival_date);



