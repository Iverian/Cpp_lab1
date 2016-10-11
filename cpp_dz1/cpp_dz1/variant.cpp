#define _VARIANT_CPP

#include "variant.h"

#include <algorithm>

using namespace std;

template <class Value, class T>
T add_sum(T&& c);

#ifdef VAR1

template <class T>
T change_cont(T&& c)
{
    typename T::value_type first = T::value_type();
    auto last = first;
    int counter = 1;
    for_each(c.begin(), c.end(), [&first, &last](T::value_type a) {if (a < 0) { if (first == 0) first = a; last = a; } });
    for_each(c.begin(), c.end(), [ sum = 2 * (first + last), &counter ](T::value_type & a) {if (counter % 3 == 0) a *= sum; ++counter; });
    return add_sum<T::value_type>(move(c));
}

#elif defined(VAR2)

template <class T>
T change_cont(T&& c)
{
    auto x = *find_if(c.rbegin(), c.rend(), [](T::value_type a) { return a < T::value_type(); }) / 2;
    for_each(c.begin(), c.end(), [x](T::value_type& a) { a += x; });
    return add_sum<T::value_type>(move(c));
}

#else

#endif

template <class Value, class T>
T add_sum(T&& c)
{
    auto sum = Value();
    auto sum_m = sum;
    for_each(c.begin(), c.end(), [&sum, &sum_m](Value a) {sum += a; sum_m += abs(a); });
    c.push_back(sum);
    c.push_back(sum_m / c.size());
    return c;
}