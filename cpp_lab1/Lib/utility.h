#pragma once

#include "helper_class.h"

#include <vector>
#include <set>

point get_center(const point& x, const point& y);
bool equal(const point& x, const point& y);
void print_to_file(const std::string& file_name, const def_cont<id_type>& cont);
void print_to_file(const std::string& file_name, const def_cont<std::set<id_type>>& cont);
