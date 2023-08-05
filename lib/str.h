#include "common.h"

// Strings
namespace str {
string lower(const string& s)
{
    string result = s;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

string upper(const string& s)
{
    string result = s;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

template <typename T>
string join(const vector<T>& elements, const string& delimiter)
{
    ostringstream oss;
    for (size_t i = 0; i < elements.size(); ++i) {
        if (i != 0) {
            oss << delimiter;
        }
        oss << elements[i];
    }
    return oss.str();
}

int stoi(char ch)
{
    return int(ch - '0');
}

string slc(const string& s, int start, int end)
{
    return s.substr(start, end - start);
}

vector<string> split(const string& s, char delimiter)
{
    vector<string> result;
    stringstream ss(s);
    string token;

    while (getline(ss, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}

string fill(const string& s, int num)
{
    string ret = "";
    for (int i = 0; i < num; i++) {
        ret += s;
    }
    return ret;
}
}