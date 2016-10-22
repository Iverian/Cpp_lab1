#include "utility.h"

#include <stdexcept>
#include <iostream>
#include <fstream>

using namespace std;

uint32_t convert_float_to_uint32_t(double x) {
	x *= 1000000;
	x += 1000000;
	return x;
}

uint32_t kutirkin_tech(const uint32_t & first, const uint32_t & second) {
	return (first + second + 1) * (first + second + 2) / 2;
}

uint32_t kutirkin_tech(const double& first, const double& second) {
	return kutirkin_tech(convert_float_to_uint32_t(first), convert_float_to_uint32_t(second));
}

uint32_t kutirkin_tech(const std::vector<double>& x)
{
	if (x.size() < 2)
		throw std::runtime_error("This isn't supposed to happen");
	uint32_t retval = 0;
	auto iter = x.begin();
	retval = kutirkin_tech(*iter, *(iter + 1));
	iter += 2;
	for (; iter != x.end(); ++iter)
		retval = kutirkin_tech(retval, convert_float_to_uint32_t(*iter));
	return retval;
}

std::vector<double> get_center(const std::vector<double>& x, const std::vector<double>& y)
{
	std::vector<double> retval;
	if (x.size() != y.size())
		throw std::runtime_error("This isn't supposed to happen");
	for (int i = 0; i < x.size(); i++) {
		retval.push_back((x[i] + y[i]) / 2);
	}
	return retval;
}


bool operator<(const node & lhs, const node & rhs) {
	bool retval = true;
	if (lhs.coord.size() != rhs.coord.size())
		throw std::runtime_error("This isn't supposed to happen");
	return kutirkin_tech(lhs.coord) < kutirkin_tech(rhs.coord);
}

void print_to_file(const std::string& file_name, const def_cont<id_type>& vec)
{
	ofstream f;
	f.open(file_name);
	for (int i = 0; i < vec.size(); ++i)
		f << vec[i];
}
