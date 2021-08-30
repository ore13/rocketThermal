#ifndef STRING_HELPER
#define STRING_HELPER
#include <string>

// trim from end of string (right)
inline std::string& rtrim(std::string& s);

// trim from beginning of string (left)
inline std::string& ltrim(std::string& s);

// trim from both ends of string (right then left)
std::string& trim(std::string& s);

#endif