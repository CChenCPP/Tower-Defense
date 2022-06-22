#include "Utility.h"
#include <sstream>

int Parse::ctoi(char c)
{
    return c - '0';
}

std::string Parse::ctos(char c)
{
    return std::string(1,c);
}

std::vector<std::string> Parse::split(std::string& s, const std::string delimiter)
{
    std::vector<std::string> v;
    int delLen = delimiter.length();;
    int index = 0;
    std::string nextSubstr;
    while (s.length() > 0) {
        index = s.find(delimiter);
        if (index == std::string::npos) { v.push_back(s); break; };
        nextSubstr = s.substr(0, index);
        if (nextSubstr.length() > 0) { v.push_back(nextSubstr); };
        s = s.substr(index + delLen, s.length() - 1);
    }
    return v;
}

std::vector<std::string> Parse::split(std::string& s, char delim) {
    std::vector<std::string> v;
    std::stringstream line(s);
    std::string token;
    while (std::getline(line, token, delim)) {
        v.push_back(token);
    };
    return v;
}

std::vector<int> Parse::stringToInt(const std::vector<std::string>& v)
{
    std::vector<int> ints;
    ints.reserve(v.size());
    for (auto& string : v) {
        ints.push_back(std::atoi(string.c_str()));
    }
    return ints;
}
