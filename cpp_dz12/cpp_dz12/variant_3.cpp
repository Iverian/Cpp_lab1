#include "variant.h"

#ifdef _VAR_3

void search_struct_::index_record(const id_type& pos, const record_& x)
{
    pharmacy_id.insert(std::make_pair(x.pharmacy_id, pos));
    drug_name.insert(std::make_pair(x.drug_name, pos));
    arrival_date.insert(std::make_pair(x.arrival_date, pos));
}

void search_struct_::delete_record(const record_& x)
{
    pharmacy_id.erase(x.pharmacy_id);
    drug_name.erase(x.drug_name);
    arrival_date.erase(x.arrival_date);
}

void Database::bin_to_txt(const std::string& file_name)
{
}

std::ostream& operator<<(std::ostream& os, const record_& x)
{
    return os << "{ " << x.pharmacy_id << ", " << x.drug_name << ", " << x.pack_count_avail << ", "
              << x.pack_price << ", " << x.arrival_date << ", " << x.spoil_time << " }" << std::endl;
}

#endif
