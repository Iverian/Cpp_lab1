#pragma once

#include "helper_class.h"

#include <vector>
#include <set>

void echo(std::istream&& p_src, std::ostream& p_dst);
bool user_confirm(std::istream& p_is, std::pair<char, char> p_yes_no = std::pair<char, char>('y', 'n'));
point get_center(const point& x, const point& y);
bool equal(const point& x, const point& y);
void print_to_file(const std::string& p_filename, const def_cont<id_type>& p_cont);
void print_to_file(const std::string& p_filename, const def_cont<std::set<id_type>>& p_cont);
bool eol(std::istream& p_is);
bool kutirkin_tech(const point& lhs, const point& rhs);