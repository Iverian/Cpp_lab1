#include <variant.h>

#ifdef _VAR_3

template <>
void search_struct<drug>::index_record(const id_type& pos, const drug& x)
{
	insert_(pharmacy_id, pos, x);
	insert_(drug_name, pos, x);
	insert_(arrival_date, pos, x);
}

template <>
void search_struct<drug>::delete_record(const drug& x)
{
	erase_(pharmacy_id, x);
	erase_(drug_name, x);
	erase_(arrival_date, x);
}

void to_text<drug>::operator()(const std::string& filename) const
{
}

std::ostream& operator<<(std::ostream& os, const drug& x)
{
    return os << "{ " << x.pharmacy_id << ", " << x.drug_name << ", " << x.pack_count_avail << ", "
              << x.pack_price << ", " << x.arrival_date << ", " << x.spoil_time << " }" << std::endl;
}

#endif
