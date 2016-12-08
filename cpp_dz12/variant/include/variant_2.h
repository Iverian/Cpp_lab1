#pragma once

#include <date.h>
#include <search_struct_traits.h>

struct training {
    char client_surname[STRMAXLEN];
    int code;
    char name_of_sport[STRMAXLEN];
    char trainer_surname[STRMAXLEN];
    date train_date;
    int train_daytime;
    double price_per_min;
    int min_count;
};

declare_record(training)

declare_search_fields( client_surname, trainer_surname, name_of_sport, train_date, min_count)

declare_link(client_surname)
declare_link(trainer_surname)
declare_link(name_of_sport)
declare_link(train_date)
declare_link(min_count)

search_struct_decl_begin

declare_search_struct(
	declare_cont(client_surname)
	declare_cont(trainer_surname)
	declare_cont(name_of_sport)
	declare_cont(train_date)
	declare_cont(min_count)
)

search_struct_decl_end

declare_find_t(client_surname)
declare_find_t(trainer_surname)
declare_find_t(name_of_sport)
declare_find_t(train_date)
declare_find_t(min_count)


