#include <variant.h>

#ifdef _VAR_2

#include <iomanip>

using namespace std;

training to_text<training>::get()
{
    training x;
    cout << "Client Surname:" << endl;
    cin >> x.client_surname;
    cout << "Code:" << endl;
    cin >> x.code;
    cout << "Name of sport:" << endl;
    cin >> x.name_of_sport;
    cout << "Trainer surname:" << endl;
    cin >> x.trainer_surname;
    cout << "Training date:" << endl;
    cin >> x.train_date;
    cout << "Training daytime:" << endl;
    cin >> x.train_daytime;
    cout << "Price per minute:" << endl;
    cin >> x.price_per_min;
    cout << "Count of minutes:" << endl;
    cin >> x.min_count;
}

void to_text<training>::operator()(const database& parent, const std::string& filename) const
{
    ofstream f(filename);
    f << "    CLIENT SURNAME |    CODE |    NAME OF SPORT |    TRAINER SURNAME |    TRAINING DATE |    "
         "TRAINING DAYTIME |    PRICE PER MINUTE |    COUNT OF MINUTES |"
      << endl;
    for (id_type i = 0, size = parent.size(); i != size; ++i) {
        auto rec = parent.get_record(i);
        cout << rec << endl;
        f << setw(18) << rec.client_surname << " | " << setw(7) << rec.code << " | " << setw(16)
          << rec.name_of_sport << " | " << setw(18) << rec.trainer_surname << " | " << setw(16)
          << rec.train_date << " | " << setw(19) << rec.train_daytime << " | " << setw(19)
          << rec.price_per_min << " | " << setw(19) << rec.min_count;
    }
}

std::ostream& operator<<(std::ostream& os, const training& x)
{
    return os << "{ " << x.client_surname << ", " << x.code << ", " << x.name_of_sport << ", "
              << x.trainer_surname << ", " << x.train_date << ", " << x.train_daytime << ", "
              << x.price_per_min << ", " << x.min_count << " }";
}

#endif
