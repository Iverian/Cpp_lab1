//Мы скопипастили этот код со stackoverflow, ведь именно так работают настоящие программисты

#pragma once

#define identity_(x) x

#define map_(macro, ...) identity_(apply_(choose_map_start_, count_(__VA_ARGS__))(macro, __VA_ARGS__))

#define choose_map_start_(count) map##count

#define apply_(macro, ...) identity_(macro(__VA_ARGS__))

#define map1(m, x) m(x)
#define map2(m, x, ...) m(x) identity_(map1(m, __VA_ARGS__))
#define map3(m, x, ...) m(x) identity_(map2(m, __VA_ARGS__))
#define map4(m, x, ...) m(x) identity_(map3(m, __VA_ARGS__))
#define map5(m, x, ...) m(x) identity_(map4(m, __VA_ARGS__))

#define evaluate_count_(_1, _2, _3, _4, _5, count, ...) count
#define count_(...) identity_(evaluate_count_(__VA_ARGS__, 5, 4, 3, 2, 1))

