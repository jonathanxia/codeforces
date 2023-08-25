from math import gcd
from collections import Counter, deque, defaultdict
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

def first_st(func, lo, hi):
    for x in range(lo, hi + 1):
        if func(x):
            return x
    
    return hi + 1

def last_st(func, lo, hi):
    for x in range(hi, lo - 1, -1):
        if func(x):
            return x
    return lo - 1

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

# MOD = 998244353
MOD = 1000000007

def mod(a, p=MOD):
    if p > 0: return (a % p + p) % p
    return a

def slc(a, idx):
    ret = []
    for i in idx:
        ret.append(a[i])
    
    return ret

def prod(a, p=-1):
    ret = a[0]
    for i in range(1, len(a)):
        ret *= a[i]
        ret = mod(ret, p)
    
    return ret

def cummax(a, reverse=False):
    ret = a.copy()
    n = len(a)
    if reverse:
        for i in range(n - 2, -1, -1):
            ret[i] = max(ret[i + 1], ret[i])
    else:
        for i in range(1, n - 1):
            ret[i] = max(ret[i], ret[i - 1])
    
    return ret

def cummin(a, reverse=False):
    ret = a.copy()
    n = len(a)
    if reverse:
        for i in range(n - 2, -1, -1):
            ret[i] = min(ret[i + 1], ret[i])
    else:
        for i in range(1, n - 1):
            ret[i] = min(ret[i], ret[i - 1])
    
    return ret

def with_idx(a):
    out = []
    for i, v in enumerate(a):
        out.append((i, v))
    
    return out