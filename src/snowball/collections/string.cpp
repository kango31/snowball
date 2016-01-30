/*
Snowball library
Copyright (C) 2016 Cédric Campguilhem

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "string.h"

#include <iostream>


using namespace std;

namespace snowball
{
    
/*
 * Constructors
 */

String::String(): m_str("") { }

String::String(const string& str): m_str(str) { }

String::String(const char* cstr): m_str(cstr) { }

String::String(typename String::size_type n, char c): m_str(n, c) { }

String::String(const String& other): m_str(other.m_str) { }

/*
 * Assignment operator
 */

String& String::operator=(const String& other)
{
    m_str = other.m_str;
    return *this;
}

String& String::operator=(const std::string& str)
{
    m_str = str;
    return *this;
}

String& String::operator=(const char* cstr)
{
    m_str = cstr;
    return *this;
}

/*
 * Destructor
 */

String::~String() { }

/*
 * Method: size
 */

typename String::size_type String::size() const
{
    return m_str.size();
}

/*
 * operator==
 */

bool String::operator==(const String& other) const
{
    return m_str == other.m_str;
}

bool String::operator==(const std::string& str) const
{
    return m_str == str;
}

bool String::operator==(const char* cstr) const
{
    return m_str == cstr;
}

/*
 * Method contains
 */

bool String::contains(const char* sub) const
{
    return (m_str.find(sub) != string::npos);
}

bool String::contains(const std::string& sub) const
{
    return (m_str.find(sub) != string::npos);
}

bool String::contains(const String& sub) const
{
    return (m_str.find(sub.m_str) != string::npos);
}

bool String::contains(const char sub) const
{
    return (m_str.find(sub) != string::npos);
}

/*
 * Method startswith
 */

bool String::startswith(const std::string& str) const
{
    return m_str.compare(0, str.size(), str) == 0;
}

bool String::startswith(const String& str) const
{
    return m_str.compare(0, str.size(), str.m_str) == 0;
}

bool String::startswith(const char* cstr) const
{    
    return m_str.compare(0, std::char_traits<char>::length(cstr), cstr) == 0;
}

bool String::startswith(const char c) const
{
    return m_str.compare(0, 1, std::string(&c)) == 0;
}

// /*
//  * Operator <<
//  */
// 
// ostream& operator<<(ostream& os, const KString& str)
// {
//     os << str.str;
//     return os;
// }
// 
// /*
//  * Method split
//  */
// 
// List<KString> KString::split(const string& sep) const
// {
//     List<KString> fields;
//     size_t pos, current;
//     current = 0;
//     int len = 0;
//     while (true)
//     {
//         pos = str.find(sep, current);
//         if (pos == string::npos)
//         {
//             fields.append(KString(str.substr(current)));
//             break;
//         }
//         else
//         {
//             fields.append(KString(str.substr(current, pos - current)));
//             current = pos + 1;
//         }
//     }
//     return fields;
// }
// 
// List<KString> KString::split() const
// {
//     List<KString> fields;
//     size_t pos, current;
//     string sep = " ";
//     current = 0;
//     int len = 0;
//     while (true)
//     {
//         pos = str.find(sep, current);
//         if (pos == string::npos)
//         {
//             fields.append(KString(str.substr(current)));
//             break;
//         }
//         else if (pos == current)
//             current++;
//         else
//         {
//             fields.append(KString(str.substr(current, pos - current)));
//             current = pos + 1;
//         }
//     }
//     return fields;
// }
// 
// /*
//  * Method toInt
//  */
// 
// int KString::toInt() const throw(ValueError)
// {
//     int value;
//     try
//     {
//         value = stoi(str);
//     }
//     catch (exception er)
//     {
//         throw_extended(ValueError, "cannot be converted into int");
//     }
//     return value;
// }
// 
// /*
//  * operator string()
//  */
// KString::operator string() const
// {
//     return str;
// }
// 
// 
// /*
//  * Method lstrip
//  */
// 
// void KString::lstrip()
// {
//     size_t pos;
//     pos = str.find_first_not_of("\n\r\t ");
//     if (pos != string::npos)
//         str.erase(str.begin(), str.begin() + pos);
// }
// 
// void KString::lstrip(const char* s)
// {
//     size_t pos;
//     pos = str.find_first_not_of(s);
//     if (pos != string::npos)
//         str.erase(str.begin(), str.begin() + pos);
// }
// 
// void KString::lstrip(const string& s)
// {
//     size_t pos;
//     pos = str.find_first_not_of(s);
//     if (pos != string::npos)
//         str.erase(str.begin(), str.begin() + pos);
// }
// 
// void KString::lstrip(const KString& s)
// {
//     size_t pos;
//     pos = str.find_first_not_of(s.str);
//     if (pos != string::npos)
//         str.erase(str.begin(), str.begin() + pos);
// }
// 
// /*
//  * Method rstrip
//  */
// 
// void KString::rstrip()
// {
//     size_t pos;
//     pos = str.find_last_not_of("\n\r\t ");
//     if (pos != string::npos)
//         str.erase(str.begin() + pos + 1, str.end());
// }
// 
// void KString::rstrip(const char* s)
// {
//     size_t pos;
//     pos = str.find_last_not_of(s);
//     if (pos != string::npos)
//         str.erase(str.begin() + pos + 1, str.end());
// }
// 
// void KString::rstrip(const string& s)
// {
//     size_t pos;
//     pos = str.find_last_not_of(s);
//     if (pos != string::npos)
//         str.erase(str.begin() + pos + 1, str.end());
// }
// 
// void KString::rstrip(const KString& s)
// {
//     size_t pos;
//     pos = str.find_last_not_of(s.str);
//     if (pos != string::npos)
//         str.erase(str.begin() + pos + 1, str.end());
// }
// 
// /*
//  * Method strip
//  */
// 
// void KString::strip()
// {
//     lstrip();
//     rstrip();
// }
// 
// void KString::strip(const char* s)
// {
//     lstrip(s);
//     rstrip(s);
// }
// 
// void KString::strip(const string& s)
// {
//     lstrip(s);
//     rstrip(s);
// }
// 
// void KString::strip(const KString& s)
// {
//     lstrip(s);
//     rstrip(s);
// }
// 
// /* 
//  * Non-member function getline
//  */
// 
// istream& getline(istream& is, KString& s, char delim)
// {
//     return std::getline(is, s.str, delim);
// }
// 
// istream& getline(istream& is, KString& s)
// {
//     return std::getline(is, s.str);
// }
    
} //end of namespace snowball