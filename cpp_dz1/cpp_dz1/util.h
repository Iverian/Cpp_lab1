#pragma once

#include <fstream>
#include <iostream>
#include <iterator>

#define COUNT 10

std::ifstream create_file(const std::string& filename);
template <class T>
T create_cont(std::ifstream&& s);
template <class T>
T print(T&& c, std::ostream& os = std::cout);

template <class T>
T create_cont(std::ifstream&& s)
{
    T cont(COUNT);
    std::istream_iterator<int> iter(s);
    generate(cont.begin(), cont.end(), [&iter]() { return *iter++; });
    return cont;
}

template <class T>
T print(T&& c, std::ostream& os)
{
    for_each(c.begin(), c.end(), [&os](int a) { os << a << " "; });
    return c;
}
