#include <iostream>
#include <variant.h>

using namespace std;

enum actions { ADD_RECORDS, GET_RECORD, DELETE_RECORD, CHANGE_RECORD, FIND_RECORD, SUMMARY, QUIT };

static const char* help_msg = "0 - add record\n"
                              "1 - get record by id\n"
                              "2 - delete record by id\n"
                              "3 - change record by id\n"
                              "4 - find record\n"
                              "5 - summary\n"
                              "6 - quit";

ostream& print(const vector<id_type>& cont, database& db, ostream& os = cout);

int main()
{
    database db("db");
    cout << help_msg << endl;
    for (int a; cout << "> ", cin >> a;)
        switch (actions(a)) {
        case ADD_RECORDS: {
            auto rec = to_text<record_>::get();
            db.add_record(rec);
            break;
        }
        case GET_RECORD: {
            id_type id;
            cout << "enter id between 0 and " << db.size() << endl;
            cin >> id;
            cout << db.get_record(id) << endl;
            break;
        }
        case DELETE_RECORD: {
            id_type id;
            cout << "enter id between 0 and " << db.size() << endl;
            cin >> id;
            db.delete_record(id);
            break;
        }
        case CHANGE_RECORD: {
            id_type id;
            cout << "enter id between 0 and " << db.size() << endl;
            cin >> id;
            auto rec = to_text<record_>::get();
            db.change_record(id, rec);
            break;
        }
        case FIND_RECORD: {
            for (int i = 0; i < size_(names); ++i)
                cout << i << " - " << names[i] << endl;
            id_type id;
            cout << "enter searchable id between 0 and " << size_(names) << endl;
            cin >> id;
            switch (id) {
            case 0: {
                linked_type<0> x;
                cin >> x;
                print(db.find<0>(x, "last_find.txt"), db) << endl;
                break;
            }
            case 1: {
                linked_type<1> x;
                cin >> x;
                print(db.find<1>(x, "last_find.txt"), db) << endl;
                break;
            }
            case 2: {
                linked_type<2> x;
                cin >> x;
                print(db.find<2>(x, "last_find.txt"), db) << endl;
                break;
            }
            case 3: {
                linked_type<3> x;
                cin >> x;
                print(db.find<3>(x, "last_find.txt"), db) << endl;
                break;
            }
            case 4: {
                linked_type<4> x;
                cin >> x;
                print(db.find<4>(x, "last_find.txt"), db) << endl;
                break;
            }
            default:
                break;
            }
            break;
        }
        case SUMMARY: {
            db.to_text("summary.txt");
            break;
        }
        case QUIT:
            goto exit;
        default:
            cout << "USAGE: " << endl << help_msg << endl;
            break;
        }
exit:
    return 0;
}

ostream& print(const vector<id_type>& cont, database& db, ostream& os)
{
    os << "[ ";
    for (auto i = cont.begin(); i != cont.end(); ++i) {
        os << db.get_record(*i) << (next(i) == cont.end() ? "" : ", ") << endl;
    }
    return os << " ]";
}