#define _VARIANT_CPP

#include "variant.h"

#include <algorithm>

using namespace std;
template <class T>
T add_sum(T&& c);

#ifdef VAR1

template <class T>
T change_cont(T&& c)
{
    int first = 0, last = 0, counter = 1;
    for_each(c.begin(), c.end(), [&first, &last](int a) {if (a < 0) { if (first == 0) first = a; last = a; } });
    for_each(c.begin(), c.end(), [ sum = 2 * (first + last), &counter ](int& a) {if (counter % 3 == 0)a *= sum; ++counter; });
    return add_sum(c);
}

#elif defined(VAR2)

#else

#endif

template <class T>
T add_sum(T&& c)
{
    int sum = 0, sum_m = 0;
    for_each(c.begin(), c.end(), [&sum, &sum_m](int a) {sum += a; sum_m += abs(a); });
    c.push_back(sum);
    c.push_back(sum_m / c.size());
    return c;
}