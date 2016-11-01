#pragma once

//#define VAR1
//#define VAR2
#define VAR3

template <class T>
T change_cont(T&& c);

#ifndef _VARIANT_CPP
#define _VARIANT_CPP
#include "variant.cpp"
#endif