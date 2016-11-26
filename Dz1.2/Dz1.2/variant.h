#pragma once

#include "Abstract_database.h"

#include <iostream>

#define MAXLEN 100

#define _VAR_1
//#define _VAR_2
//#define _VAR_3

#ifdef _VAR_1
#include "variant_1.h"
#elif defined(_VAR_2)
#include "variant_2.h"
#elif defined(_VAR_3)
#include "variant_3.h"
#endif

class Database : public Abstract_database<Record, Search_struct>
{
	using Abstract_database<Record, Search_struct>::Abstract_database;
	void bin_to_txt(const std::string& file_name) override;
};

std::ostream& operator<<(std::ostream& os, const Record& x);