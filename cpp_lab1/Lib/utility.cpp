#include "utility.h"

#include <fstream>
#include <stdexcept>

#define MAGIC_NUMBER 1000000
#define ACCURACY 1e-9

using namespace std;

point get_center(const point& x, const point& y)
{
    point retval;
    if (x.size() != y.size())
        throw std::runtime_error("This isn't supposed to happen");
    for (size_t i = 0; i < x.size(); i++)
        retval.push_back((x[i] + y[i]) / 2);
    return move(retval);
}

bool equal(const point& x, const point& y)
{
    return std::equal(x.begin(), x.end(), y.begin(), y.end(), [](double a, double b) { return std::fabs(a - b) < ACCURACY; });
}

void print_to_file(const std::string& file_name, const def_cont<id_type>& cont)
{
    ofstream f(file_name);
    for (auto& i : cont)
        f << i << endl;
}

void print_to_file(const std::string& file_name, const def_cont<std::set<id_type>>& cont)
{
    ofstream f(file_name);
    for (size_t size = cont.size(), i = 0; i != size; ++i) {
        f << i + 1 << " : ";
        for (auto& j : cont[i])
            f << j << " ";
        f << endl;
    }
}
