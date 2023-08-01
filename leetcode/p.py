M = 10 ** 9 + 7

cache = {}
def memoize(func):
    def wrap(x, y, z):
        if (x, y, z) in cache:
            return cache[x, y, z]
        
        cache[x, y, z] = func(x, y, z)
        return cache[x, y, z]
    
    return wrap

@memoize
def func(digit, low, high):
    assert len(low) == len(high)

    L = int(low[0])
    R = int(high[0])

    if digit < L or digit > R:
        return 0
    
    if len(low) == 1:
        return 1

    n = len(low)

    ret = 0
    if L == R:
        return func(digit + 1, low[1:], high[1:]) + func(digit - 1, low[1:], high[1:])

    if digit == L:
        if digit < 9:
            ret += func(digit + 1, low[1:], "9" * (n - 1))
        if digit > 0:
            ret += func(digit - 1, low[1:], "9" * (n - 1))
    
    elif digit == R:
        if digit < 9:
            ret += func(digit + 1, "0" * (n - 1), high[1:])
        if digit > 0:
            ret += func(digit - 1, "0" * (n - 1), high[1:])
    
    else:
        if digit < 9:
            ret += func(digit + 1, "0" * (n - 1), "9" * (n - 1))
        if digit > 0:
            ret += func(digit - 1, "0" * (n - 1), "9" * (n - 1))

    return ret % M

class Solution:
    def countSteppingNumbers(self, low: str, high: str) -> int:
        ans = 0
        while len(low) < len(high):
            for i in range(0, 10):
                ans += func(i, low, "9" * len(low))
                ans %= M
            low = "1" + "0" * (len(low))
        
        for i in range(0, 10):
            ans += func(i, low, high)
            print(i, low, high, ans)
            ans %= M
        
        print("low=", low)
        print("high=", high)
        return ans % M