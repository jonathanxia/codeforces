from math import gcd
from collections import deque, defaultdict
from typing import List, Dict

def largest_st(func, lo, hi):
    ans = lo - 1
    while lo <= hi:
        mid = (lo + hi) // 2
        if func(mid):
            ans = mid
            lo = mid + 1
        else:
            hi = mid - 1
    
    return ans

def smallest_st(func, lo, hi):
    ans = hi + 1
    while lo <= hi:
        mid = (lo + hi) // 2
        if func(mid):
            ans = mid
            hi = mid - 1
        else:
            lo = mid + 1
        
    return ans

def lcm(x, y):
    return x * y / gcd(x, y)

def list_to_str(a):
    return [str(x) for x in a]

def memoize(func):
    cache = {}
    def wrap(*args):
        targs = tuple(args)
        if targs in cache:
            return cache[targs]
        
        cache[targs] = func(*args)
        return cache[targs]
    
    return wrap