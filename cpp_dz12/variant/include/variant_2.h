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

declare_record(training);
declare_searchable(client_surname, trainer_surname, name_of_sport, train_date, min_count);
