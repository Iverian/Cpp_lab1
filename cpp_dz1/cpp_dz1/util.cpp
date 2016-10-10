#define _UTIL_CPP 

#include "util.h"

#include <ctime>
#include <random>
#include <fstream>

//#define COUNT 10

using namespace std;

ifstream create_file(const string &filename)
{
    ofstream f(filename);
    minstd_rand0 r(time(nullptr));
    for (int i = 0; i < COUNT; i++)
        f << int(r() % 100) - 50 << endl;
	f.close();
	return ifstream(filename);
}
