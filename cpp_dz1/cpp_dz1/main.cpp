#include "util.h"
#include "variant.h"

#include <deque>
#include <iostream>
#include <list>
#include <vector>
#define FILENAME "in.txt"

using namespace std;

int main()
{
    cout << "загадай число" << endl;
    int a;
    cin >> a;
    switch (a % 3) {
    case 0:
        print(change_cont(create_cont<vector<int>>(create_file(FILENAME))));
		break;
    case 1:
        print(change_cont(create_cont<list<int>>(create_file(FILENAME))));
		break;
    case 2:
        print(change_cont(create_cont<deque<int>>(create_file(FILENAME))));
		break;
    default:
        break;
    }
    return 0;
}