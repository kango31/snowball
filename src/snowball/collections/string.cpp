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

String::String(char c): String(1, c) { }

/*
 * Assignment operator
 */

String& String::operator=(const String& other)
{
    if (this != &other)
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
 * operator!=
 */

bool String::operator!=(const String& other) const
{
    return m_str.compare(other.m_str) != 0;
}

bool String::operator!=(const std::string& str) const
{
    return m_str.compare(str) != 0;
}

bool String::operator!=(const char* cstr) const
{
    return m_str.compare(cstr) != 0;
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
 * Method startsWith
 */

bool String::startsWith(const std::string& str) const
{
    return m_str.compare(0, str.size(), str) == 0;
}

bool String::startsWith(const String& str) const
{
    return m_str.compare(0, str.size(), str.m_str) == 0;
}

bool String::startsWith(const char* cstr) const
{    
    return m_str.compare(0, std::char_traits<char>::length(cstr), cstr) == 0;
}

bool String::startsWith(const char c) const
{
    std::string str(1, c);
    return m_str.compare(0, 1, str) == 0;
}

/*
 * Method endsWith
 */

bool String::endsWith(const std::string& str) const
{
    return m_str.compare(m_str.size() - str.size(), str.size(), str) == 0;
}

bool String::endsWith(const String& str) const
{
    return m_str.compare(m_str.size() - str.size(), str.size(), str.m_str) == 0;
}

bool String::endsWith(const char* cstr) const
{    
    
    return m_str.compare(m_str.size() - std::char_traits<char>::length(cstr),
                         std::char_traits<char>::length(cstr), 
                         cstr) == 0;
}

bool String::endsWith(const char c) const
{
    std::string str(1, c);
    return m_str.compare(m_str.size() - 1, 1, str) == 0;
}

/*
 * Method split
 */

List<String> String::split(const std::string& sep) const
{
    List<String> fields;
    size_t pos, current;
    current = 0;
    while (true)
    {
        pos = m_str.find_first_of(sep, current);
        if (pos == string::npos)
        {
            fields.append(String(m_str.substr(current)));
            break;
        }
        else if (pos == current)
            current++;
        else
        {
            fields.append(String(m_str.substr(current, pos - current)));
            current = pos + 1;
        }
    }
    return fields;
}

List<String> String::split() const
{
    return split(std::string(" \t\r\n"));
}

List<String> String::split(const String& str) const
{
    return split(str.m_str);
}

List<String> String::split(const char* cstr) const
{
    return split(std::string(cstr));
}

List<String> String::split(const char c) const
{
    return split(std::string(1, c));
}

/*
 * Operator <<
 */

ostream& operator<<(ostream& os, const String& str)
{
    os << str.m_str;
    return os;
}

/*
 * Operator >>
 */

istream& operator>>(istream& is, String& str)
{
    is >> str.m_str;
    return is;
}

/*
 * Method leftStrip
 */

String& String::leftStrip()
{
    return leftStrip("\n\r\t ");
}

String& String::leftStrip(const char* s)
{
    size_t pos;
    pos = m_str.find_first_not_of(s);
    if (pos != std::string::npos)
        m_str.erase(m_str.begin(), m_str.begin() + pos);
    return *this;
}

String& String::leftStrip(const std::string& s)
{
    size_t pos;
    pos = m_str.find_first_not_of(s);
    if (pos != std::string::npos)
        m_str.erase(m_str.begin(), m_str.begin() + pos);
    return *this;
}

String& String::leftStrip(const String& s)
{
    return leftStrip(s.m_str);
}

String& String::leftStrip(const char c)
{
    return leftStrip(std::string(1, c));
}

String String::leftStrip() const
{
    return leftStrip("\n\r\t ");
}

String String::leftStrip(const char* s) const
{
    size_t pos;
    String copy(*this);
    pos = copy.m_str.find_first_not_of(s);
    if (pos != std::string::npos)
        copy.m_str.erase(copy.m_str.begin(), copy.m_str.begin() + pos);
    return copy;
}

String String::leftStrip(const std::string& s) const
{
    size_t pos;
    String copy(*this);
    pos = copy.m_str.find_first_not_of(s);
    if (pos != std::string::npos)
        copy.m_str.erase(copy.m_str.begin(), copy.m_str.begin() + pos);
    return copy;
}

String String::leftStrip(const String& s) const
{
    return leftStrip(s.m_str);
}

String String::leftStrip(const char c) const
{
    return leftStrip(std::string(1, c));
}

/*
 * Method rightStrip
 */

String& String::rightStrip()
{
    return rightStrip("\n\r\t ");
}

String& String::rightStrip(const char* s)
{
    size_t pos;
    pos = m_str.find_last_not_of(s);
    if (pos != std::string::npos)
        m_str.erase(m_str.begin() + pos + 1, m_str.end());
    return *this;
}

String& String::rightStrip(const std::string& s)
{
    size_t pos;
    pos = m_str.find_last_not_of(s);
    if (pos != std::string::npos)
        m_str.erase(m_str.begin() + pos + 1, m_str.end());
    return *this;
}

String& String::rightStrip(const String& s)
{
    return rightStrip(s.m_str);
}

String& String::rightStrip(const char c)
{
    return rightStrip(std::string(1, c));
}

String String::rightStrip() const
{
    return rightStrip("\n\r\t ");
}

String String::rightStrip(const char* s) const
{
    size_t pos;
    String copy(*this);
    pos = copy.m_str.find_last_not_of(s);
    if (pos != std::string::npos)
        copy.m_str.erase(copy.m_str.begin() + pos + 1, copy.m_str.end());
    return copy;
}

String String::rightStrip(const std::string& s) const
{
    size_t pos;
    String copy(*this);
    pos = copy.m_str.find_last_not_of(s);
    if (pos != std::string::npos)
        copy.m_str.erase(copy.m_str.begin() + pos + 1, copy.m_str.end());
    return copy;
}

String String::rightStrip(const String& s) const
{
    return rightStrip(s.m_str);
}

String String::rightStrip(const char c) const
{
    return rightStrip(std::string(1, c));
}

/*
 * Method strip
 */

String& String::strip()
{
    return leftStrip().rightStrip();
}

String& String::strip(const char* s)
{
    return leftStrip(s).rightStrip(s);
}

String& String::strip(const std::string& s)
{
    return leftStrip(s).rightStrip(s);
}

String& String::strip(const String& s)
{
    return leftStrip(s).rightStrip(s);
}

String& String::strip(const char c)
{
    return leftStrip(c).rightStrip(c);
}

String String::strip() const
{
    return leftStrip().rightStrip();
}

String String::strip(const char* s) const
{
    return leftStrip(s).rightStrip(s);
}

String String::strip(const std::string& s) const
{
    return leftStrip(s).rightStrip(s);
}

String String::strip(const String& s) const
{
    return leftStrip(s).rightStrip(s);
}

String String::strip(const char c) const
{
    return leftStrip(c).rightStrip(c);
}

/*
 * Method toInt
 */

int String::toInt(int base) const throw(ValueError)
{
    int value = 0;
    std::size_t nbread = 0;
    String str = strip();
    try
    {
        value = std::stoi(str.m_str, &nbread, base);
    }
    catch (const exception& e)
    {
        THROW(ValueError, "invalid literal for int");
    }
    if (nbread < str.size())
        THROW(ValueError, "invalid literal for int");
    return value;
}

/*
 * Method toFloat
 */

float String::toFloat() const throw(ValueError)
{
    float value = 0.;
    std::size_t nbread = 0;
    String str = strip();
    try
    {
        value = std::stof(str.m_str, &nbread);
    }
    catch (const exception& e)
    {
        THROW(ValueError, "invalid literal for float");
    }
    if (nbread < str.size())
        THROW(ValueError, "invalid literal for float");
    return value;
}

/*
 * Method toDouble
 */

double String::toDouble() const throw(ValueError)
{
    double value = 0.;
    std::size_t nbread = 0;
    String str = strip();
    try
    {
        value = std::stod(str.m_str, &nbread);
    }
    catch (const exception& e)
    {
        THROW(ValueError, "invalid literal for double");
    }
    if (nbread < str.size())
        THROW(ValueError, "invalid literal for double");
    return value;
}

/*
 * Method toBool
 */

bool String::toBool() const throw(ValueError)
{
    int value = 0;
    std::size_t nbread = 0;
    String str = strip();
    try
    {
        value = std::stoi(str.m_str, &nbread);
    }
    catch (const exception& e)
    {
        THROW(ValueError, "invalid literal int");
    }
    if (nbread < str.size())
        THROW(ValueError, "invalid literal int");
    return value != 0;
}

/*
 * operator string()
 */

String::operator string() const
{
    return m_str;
}

/*
 * method upper
 */

String& String::upper()
{
#ifdef SNOWBALL_WITH_BOOST_LOCALE
    m_str = boost::locale::to_upper(m_str);
#else
    auto func = [](const char c){ std::locale loc(""); return std::toupper(c, loc); };
    std::transform(m_str.begin(), 
                   m_str.end(), 
                   m_str.begin(), 
                   std::function<char(const char)>(func));
#endif    
    return *this;
}

String String::upper() const
{
    String copy(*this);
#ifdef SNOWBALL_WITH_BOOST_LOCALE
    copy.m_str = boost::locale::to_upper(copy.m_str);
#else
    auto func = [](const char c){ std::locale loc(""); return std::toupper(c, loc); };
    std::transform(copy.m_str.begin(), 
                   copy.m_str.end(), 
                   copy.m_str.begin(), 
                   std::function<char(const char)>(func));
#endif
    return copy;
}

/*
 * method lower
 */

String& String::lower()
{
#ifdef SNOWBALL_WITH_BOOST_LOCALE
    m_str = boost::locale::to_lower(m_str);
#else
    auto func = [](const char c){ std::locale loc(""); return std::tolower(c, loc); };
    std::transform(m_str.begin(), 
                   m_str.end(), 
                   m_str.begin(), 
                   std::function<char(const char)>(func));
#endif
    return *this;
}

String String::lower() const
{
    String copy(* this);
#ifdef SNOWBALL_WITH_BOOST_LOCALE
    copy.m_str = boost::locale::to_lower(copy.m_str);
#else    
    auto func = [](const char c){ std::locale loc(""); return std::tolower(c, loc); };
    std::transform(copy.m_str.begin(), 
                   copy.m_str.end(), 
                   copy.m_str.begin(), 
                   std::function<char(const char)>(func));
#endif
    return copy;
}


/* 
 * Non-member function getline
 */

istream& getline(istream& is, String& str, char delim)
{
    return std::getline(is, str.m_str, delim);
}

istream& getline(istream& is, String& str)
{
    return std::getline(is, str.m_str);
}

/*
 * method: begin
 */

typename String::iterator String::begin()
{
    return m_str.begin();
}

typename String::const_iterator String::begin() const
{
    return m_str.begin();
}

/*
 * method: end
 */

typename String::iterator String::end()
{
    return m_str.end();
}

typename String::const_iterator String::end() const
{
    return m_str.end();
}

/*
 * method: rbegin
 */

typename String::reverse_iterator String::rbegin()
{
    return m_str.rbegin();
}

typename String::const_reverse_iterator String::rbegin() const
{
    return m_str.rbegin();
}

/*
 * method: rend
 */

typename String::reverse_iterator String::rend()
{
    return m_str.rend();
}

typename String::const_reverse_iterator String::rend() const
{
    return m_str.rend();
}

/*
 * method: operator<
 */

bool String::operator<(const std::string& other) const
{
    return m_str < other;
};

bool String::operator<(const char* other) const
{
    return m_str < other;
};

bool String::operator<(const String& other) const
{
    return m_str < other.m_str;
};

/*
 * method: operator<=
 */

bool String::operator<=(const std::string& other) const
{
    return m_str <= other;
};

bool String::operator<=(const char* other) const
{
    return m_str <= other;
};

bool String::operator<=(const String& other) const
{
    return m_str <= other.m_str;
};

/*
 * method: operator>
 */

bool String::operator>(const std::string& other) const
{
    return m_str > other;
};

bool String::operator>(const char* other) const
{
    return m_str > other;
};

bool String::operator>(const String& other) const
{
    return m_str > other.m_str;
};

/*
 * method: operator>=
 */

bool String::operator>=(const std::string& other) const
{
    return m_str >= other;
};

bool String::operator>=(const char* other) const
{
    return m_str >= other;
};

bool String::operator>=(const String& other) const
{
    return m_str >= other.m_str;
};

} //end of namespace snowball