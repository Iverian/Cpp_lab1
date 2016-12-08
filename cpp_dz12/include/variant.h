#pragma once

#include <basic_database.h>
#include <search_struct_traits.h>

#include <iostream>

//#define _VAR_1
//#define _VAR_2
#define _VAR_3

template <class Record>
struct to_text;

#ifdef _VAR_1
#include <variant_1.h>
#elif defined(_VAR_2)
#include <variant_2.h>
#elif defined(_VAR_3)
#include <variant_3.h>
#endif

template<>
struct to_text<record_>
{
	void operator()(const std::string& filename) const;
};

using database = basic_database<record_, search_struct, to_text>;

std::ostream& operator<<(std::ostream& os, const record_& x);