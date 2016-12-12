#include <variant.h>

#ifdef _VAR_1

#include <iomanip>

using namespace std;

computer to_text<computer>::get()
{
    computer x;
    cout << "Trademark code: " << endl;
    cin >> x.code;
    cout << "Trademark name: " << endl;
    cin >> x.name;
    cout << "Computer's type: " << endl;
    cin >> x.type;
    cout << "Computer's model: " << endl;
    cin >> x.model;
    cout << "Frequency: " << endl;
    cin >> x.chast;
    cout << "RAM Volume: " << endl;
    cin >> x.vol;
    cout << "HDD Volume: " << endl;
    cin >> x.obem;
    cout << "GPU Memory volume: " << endl;
    cin >> x._vol;
    cout << "Computer's price: " << endl;
    cin >> x.cost;
    cout << "Amount available: " << endl;
    cin >> x.col_vo;
    return x;
}

void to_text<computer>::operator()(
    const database& parent, const std::string& filename) const
{
    ofstream f(filename);
    f << "Code |    Name    |    Type    |    Model    | Frequency | RAM Vol. | HDD Vol. | GPU Vol. | Price "
         "| Amount"
      << endl;
    for (id_type i = 0; i != parent.size(); ++i) {
        auto x = parent.get_record(i);
        cout << x << endl;
        f << setw(4) << x.code << " | " << setw(10) << x.name << " | " << setw(10) << x.type << " | "
          << setw(11) << x.model << " | " << setw(9) << x.chast << " | " << setw(8) << x.vol << " | "
          << setw(8) << x.obem << " | " << setw(8) << x._vol << " | " << setw(5) << x.cost << " | "
          << setw(6) << x.col_vo << endl;
    }
}

std::ostream& operator<<(std::ostream& os, const computer& x)
{
    return os << "{" << x.code << "," << x.name << "," << x.type << "," << x.chast << "," << x.vol << ","
              << x.obem << "," << x._vol << "," << x.cost << "," << x.col_vo << "}";
}

#endif
