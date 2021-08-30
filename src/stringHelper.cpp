#include <string>
#include "stringHelper.hpp"
const char* ws = " \t\n\r\f\v";

// trim from end of string (right)
std::string& rtrim(std::string& s)
{
    s.erase(s.find_last_not_of(ws) + 1);
    return s;
}

// trim from beginning of string (left)
std::string& ltrim(std::string& s)
{
    s.erase(0, s.find_first_not_of(ws));
    return s;
}

// trim from both ends of string (right then left)
std::string& trim(std::string& s)
{
    return ltrim(rtrim(s));
}
