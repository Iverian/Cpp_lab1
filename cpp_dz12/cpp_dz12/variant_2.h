#pragma once

#include "date.h"
#include "search_struct_traits.h"

struct RECORD {
    char client_surname[STRMAXLEN];
    int code;
    char name_of_sport[STRMAXLEN];
    char trainer_surname[STRMAXLEN];
    date train_date;
    int train_daytime;
    double price_per_min;
    int min_count;
};

DECL_SEARCH_FIELDS { client_surname, trainer_surname, name_of_sport, train_date, min_count };

DECL_LINK(client_surname);
DECL_LINK(trainer_surname);
DECL_LINK(name_of_sport);
DECL_LINK(train_date);
DECL_LINK(min_count);

struct DECL_SEARCH_STRUCT {
	void index_record(const id_type& pos, const RECORD& x) override;
	void delete_record(const RECORD& x) override;

	FIND_IMPL;

private:
	template <int id>
	struct find_t;

	Search_cont<LINK_VAL(client_surname)> client_surname;
	Search_cont<LINK_VAL(trainer_surname)> trainer_surname;
	Search_cont<LINK_VAL(name_of_sport)> name_of_sport;
	Search_cont<LINK_VAL(train_date)> train_date;
	Search_cont<LINK_VAL(min_count)> min_count;
};

DECL_FIND(client_surname);
DECL_FIND(trainer_surname);
DECL_FIND(name_of_sport);
DECL_FIND(train_date);
DECL_FIND(min_count);