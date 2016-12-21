#include <variant.h>

#ifdef _VAR_3

#include <iomanip>

using namespace std;

drug to_text<drug>::get()
{
    drug x;
    cout << "Pharmacy ID:" << endl;
    cin >> x.pharmacy_id;
    cout << "Drug name:" << endl;
    cin >> x.drug_name;
    cout << "Pack count avail:" << endl;
    cin >> x.pack_count_avail;
    cout << "Pack price:" << endl;
    cin >> x.pack_price;
    cout << "Arrival date:" << endl;
    cin >> x.arrival_date;
    cout << "Spoil time:" << endl;
    cin >> x.spoil_time;
    return x;
}

void to_text<drug>::operator()(const database& parent, const std::string& filename) const
{
    ofstream f(filename);
    f << "    ID |      NAME |    COUNT AVAIL | PRICE |    DATE |    TIME   " << endl;
    for (id_type i = 0, size = parent.size(); i != size; ++i) {
        auto rec = parent.get_record(i);
        cout << rec << endl;
        f << setw(6) << rec.pharmacy_id << " | " << setw(10) << rec.drug_name << " | " << setw(15)
          << rec.pack_count_avail << " | " << setw(6) << rec.pack_price << " | " << setw(8)
          << rec.arrival_date << " | " << setw(8) << rec.spoil_time << endl;
    }
}

std::ostream& operator<<(std::ostream& os, const drug& x)
{
    return os << "{ " << x.pharmacy_id << ", " << x.drug_name << ", " << x.pack_count_avail << ", "
              << x.pack_price << ", " << x.arrival_date << ", " << x.spoil_time << " }" << std::endl;
}

#endif
