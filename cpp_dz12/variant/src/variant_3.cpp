#include <variant.h>

#ifdef _VAR_3

void to_text<drug>::operator()(const std::string& filename) const
{
}

std::ostream& operator<<(std::ostream& os, const drug& x)
{
    return os << "{ " << x.pharmacy_id << ", " << x.drug_name << ", " << x.pack_count_avail << ", "
              << x.pack_price << ", " << x.arrival_date << ", " << x.spoil_time << " }" << std::endl;
}

#endif
