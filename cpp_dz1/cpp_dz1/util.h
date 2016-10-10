#pragma once

#include <fstream>

std::ifstream create_file(const std::string& filename);
template <class T>
T create_cont(std::ifstream& s);

