#include <lib/common.h>

// Overloading the << operator for __int128_t
// For some reason, the leetcode compilers do not have this
#ifndef LEETCODE
std::ostream& operator<<(std::ostream& os, const __int128_t& value)
{
    // Convert __int128_t to a string representation and output it
    std::string output;
    __int128_t cvalue = value;
    if (cvalue < 0) {
        output.append("-");
        cvalue = -cvalue;
    }
    vector<char> digits;
    while (cvalue > 0) {
        digits.pb(cvalue % 10 + '0');
        cvalue /= 10;
    }
    dep(i, len(digits) - 1, 0)
    {
        output += digits[i];
    }

    os << output;

    return os;
}

// Overloading the >> operator for __int128_t
std::istream& operator>>(std::istream& is, __int128_t& value)
{
    std::string input;
    is >> input;

    value = 0;
    FOR(i, 0, len(input) - 1)
    {
        value = value * 10 + (input[i] - '0');
    }

    return is;
}
#endif
