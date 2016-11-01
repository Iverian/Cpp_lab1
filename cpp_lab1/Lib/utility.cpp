#include "utility.h"

#include <fstream>
#include <stdexcept>
#include <string>

#define MAGIC_NUMBER 1000000
#define ACCURACY 1e-9

#define BUFSIZE 100

using namespace std;

void echo(std::istream&& p_src, std::ostream& p_dst)
{
	string buf;
	buf.reserve(BUFSIZE);
	while (p_src) {
		getline(p_src, buf);
		p_dst << buf << endl;
	}
}

bool user_confirm(istream& p_is, pair<char, char> p_yes_no)
{
    char c;
    while (p_is.get(c) && c != p_yes_no.first && c != p_yes_no.second)
        ;
    return c == p_yes_no.first;
}

point get_center(const point& x, const point& y)
{
    point retval;
    if (x.size() != y.size())
        throw runtime_error("This isn't supposed to happen");
    for (size_t size = x.size(), i = 0; i != size; i++)
        retval.push_back((x[i] + y[i]) / 2);
    return move(retval);
}

bool equal(const point& x, const point& y)
{
    return std::equal(x.begin(), x.end(), y.begin(), y.end(),
    		[](double a, double b)
    {
	    return fabs(a - b) < ACCURACY;
    });
}

void print_to_file(const string& p_filename, const def_cont<id_type>& cont)
{
    ofstream f(p_filename);
    for (auto& i : cont)
        f << i << endl;
}

void print_to_file(const string& p_filename, const def_cont<set<id_type>>& cont)
{
    ofstream f(p_filename);
    for (size_t size = cont.size(), i = 0; i != size; ++i) {
        f << i + 1 << " : ";
        for (auto& j : cont[i])
            f << j << " ";
        f << endl;
    }
}

bool eol(istream& p_is)
{
	char c;
	while (p_is.get(c) && !isspace(c) && c != '\n')
		;
	if (c != '\n')
		p_is.putback(c);
	return c == '\n';
}
