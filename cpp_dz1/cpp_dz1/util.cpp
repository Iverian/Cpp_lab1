#include "util.h"

#include <ctime>
#include <random>
#include <algorithm>
#include <iterator>
#define COUNT 10

using namespace std;

ifstream create_file(const string &filename)
{
    ofstream f(filename);
    minstd_rand0 r(time(nullptr));
    for (int i = 0; i < COUNT; i++)
        f << r() % 100 - 50 << endl;
	f.close();
	return ifstream(filename);
}

template <class T>
T create_cont(ifstream &s)
{
	T cont(COUNT);
	istream_iterator<int> iter(s);
	generate(cont.begin(), cont.end(), [&iter]() {return *iter++; });
	return cont;
}
