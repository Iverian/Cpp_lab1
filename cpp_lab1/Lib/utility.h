#pragma once

#include "helper_class.h"

#include <vector>
#include <fstream>

uint32_t convert_float_to_uint32_t(double x);
uint32_t kutirkin_tech(const uint32_t& first, const uint32_t& second);
uint16_t kutirkin_tech(const double& first, const double& second);
uint32_t kutirkin_tech(const std::vector<double>& x);
std::vector<double> get_center(const std::vector<double>& x, const std::vector<double>& y);
bool operator<(const node& lhs, const node& rhs);
void print_to_file(const std::string& file_name, const def_cont<id_type>& vec);
