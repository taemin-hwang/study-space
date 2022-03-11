#ifndef UTILITY_H_
#define UTILITY_H_

#include <sstream>
#include <iomanip>
#include <string>

template< typename T >
std::string int2hex( T i )
{
    std::string ret;
    std::stringstream stream;
    stream << std::setfill ('0') << std::setw(sizeof(T)*2) << std::right << std::hex << i;
    stream >> ret;
    return ret.substr(ret.size() - 2);
}


#endif