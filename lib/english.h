#pragma once
#include <lib/common.h>

#define between(lo, hi) (lo), (hi)
#define such_that(x) (x)
#define that_satisfies(x) (x)
#define the_largest(var, range, cond) largest_st((var), (cond), range)
#define the_smallest(var, range, cond) smallest_st((var), (cond), range)
#define the_first(var, range, cond) first_st((var), (cond), range)
#define the_last(var, range, cond) last_st((var), (cond), range)
#define there_exists(var, range, cond) exists_st((var), (cond), range)
#define for_all(var, range, cond) all_st((var), (cond), range)
