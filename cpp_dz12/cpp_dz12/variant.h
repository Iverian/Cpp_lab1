#pragma once

#include "abstract_database.h"
#include "search_struct_traits.h"

#include <iostream>

//#define _VAR_1
//#define _VAR_2
#define _VAR_3

template <class Record>
struct bin_to_txt;

#ifdef _VAR_1
#include "variant_1.h"
#elif defined(_VAR_2)
#include "variant_2.h"
#elif defined(_VAR_3)
#include "variant_3.h"
#endif

template<>
struct bin_to_txt<record_>
{
	void operator()(const std::string& filename) const;
};

using database = basic_database<record_, search_struct, bin_to_txt>;

std::ostream& operator<<(std::ostream& os, const record_& x);