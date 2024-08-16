#pragma once
#include <lib/common.h>

// Strings
namespace str
{
    string lower(const string &s)
    {
        string result = s;
        transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }

    string upper(const string &s)
    {
        string result = s;
        transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }

    template <typename T>
    string join(const vector<T> &elements, const string &delimiter)
    {
        ostringstream oss;
        for (size_t i = 0; i < elements.size(); ++i)
        {
            if (i != 0)
            {
                oss << delimiter;
            }
            oss << elements[i];
        }
        return oss.str();
    }

    ll indexof(string s, string s2)
    {
        auto idx = s.find(s2);
        if (idx == std::string::npos)
            return -1;
        return ll(idx);
    }

    ll indexof(string s, char c)
    {
        auto idx = s.find(c);
        if (idx == std::string::npos)
            return -1;
        return ll(idx);
    }

    ll contains(string s, string s2)
    {
        return indexof(s, s2) != -1;
    }

    int stoi(char ch)
    {
        return int(ch - '0');
    }

    string slc(const string &s, int start, int end)
    {
        return s.substr(start, end - start + 1);
    }

    vector<string> split(const string &s, char delimiter)
    {
        vector<string> result;
        stringstream ss(s);
        string token;

        while (getline(ss, token, delimiter))
        {
            result.push_back(token);
        }

        return result;
    }

    string fill(const string &s, int num)
    {
        string ret = "";
        for (int i = 0; i < num; i++)
        {
            ret += s;
        }
        return ret;
    }

    // Function to convert an integer to its binary string representation
    template <typename T>
    std::string bin(T number) {
        if (number == 0) return "0";
        std::string output;
        bool is_neg = false;
        if (number < 0) {
            is_neg = true;
            number *= -1;
        }
        while (number > 0) {
            output += (number & 1) ? "1" : "0";
            number >>= 1;
        }
        if (is_neg) output += "-";
        reverse(output.begin(), output.end());
        return output;
    }

    // Function to convert an integer to its hexadecimal string representation
    template <typename T>
    std::string hex(T number) {
        std::ostringstream oss;
        if (number < 0) {
            oss << "-";
            number = -number;
        }
        oss << std::hex << number;
        return oss.str();
    }

    // Create a LL bitmask that represents which
    // characters are present in the given string s
    ll char_bitset(const std::string& s) {
        ll ret = 0; 
        foreach(c, upper(s)) {
            ret |= 1ll << (c - 'A');
        }
        return ret;
    }
}