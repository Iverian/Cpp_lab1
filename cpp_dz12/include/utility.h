#pragma once

#include <cstdint>
#include <fstream>
#include <iterator>
#include <iostream>

using id_type = int64_t;

template <class Record>
void set_pos(const id_type &pos, std::ios_base::seekdir way, std::ostream &os)
{
	os.seekp(pos * sizeof(Record), way);
}

template <class Record>
void set_pos(const id_type &pos, std::ios_base::seekdir way, std::istream &is)
{
	is.seekg(pos * sizeof(Record), way);
}

