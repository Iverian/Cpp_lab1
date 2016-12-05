#pragma once

#include "abstract_database.h"
#include "search_struct_traits.h"

#include <iostream>

//#define _VAR_1
//#define _VAR_2
#define _VAR_3

#ifdef _VAR_1
#include "variant_1.h"
#elif defined(_VAR_2)
#include "variant_2.h"
#elif defined(_VAR_3)
#include "variant_3.h"
#endif

class Database : public abstract_database<Record, search_struct_>
{
	using abstract_database<Record, search_struct_>::abstract_database;
	void bin_to_txt(const std::string& file_name) override;
};

std::ostream& operator<<(std::ostream& os, const record_& x);