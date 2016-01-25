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

/**
 * @file
 */

#ifndef SNOWBALL_STRING_H
#define SNOWBALL_STRING_H

#include "list.hpp"

namespace snowball
{

class String{

private:
    
    std::string m_str;
    
public:
    
    String();
//     String(const std::string&);
//     ~String();
//     friend std::ostream& operator<<(std::ostream&, const String&);
//     List<String> split(const std::string& sep) const;
//     List<String> split() const;
//     bool startswith(const std::string&) const;
//     void lstrip();
//     void lstrip(const char*);
//     void lstrip(const std::string&);
//     void lstrip(const String&);
//     void rstrip();
//     void rstrip(const char*);
//     void rstrip(const std::string&);
//     void rstrip(const String&);
//     void strip();
//     void strip(const char*);
//     void strip(const std::string&);
//     void strip(const String&);
//     bool contains(const char*) const;
//     bool contains(const std::string&) const;
//     bool contains(const String&) const;
//     bool operator==(const std::string&) const;
//     bool operator==(const String&) const;
//     int toInt() const throw(ValueError);
//     operator std::string() const;
//     friend std::istream& getline(std::istream&, String&, char);
//     friend std::istream& getline(std::istream&, String&);
};

// std::istream& getline(std::istream&, String&, char);
// std::istream& getline(std::istream&, String&);

} //end of namespace snowball
#endif