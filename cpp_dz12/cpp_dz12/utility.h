#pragma once

#include <cstdint>
#include <fstream>

using id_type = uint16_t;

template <class Record>
void set_pos(const id_type& pos, int way, std::ostream& os)
{
	os.seekp(pos * sizeof(Record), way);
}

template <class Record>
void set_pos(const id_type& pos, int way, std::istream& is)
{
	is.seekg(pos * sizeof(Record), way);
}