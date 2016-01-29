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

#include <string>

#include "list.hpp"

namespace snowball
{
/**
 * @brief implements a String class on top of std::string
 */
class String
{

    public:
        
    /**
     * @typedef size_type
     * size type of String
     */
    typedef typename std::string::size_type size_type;

    private:
    
    std::string m_str;
    
    public:
    
    /**
     * Constructor.
     *
     * Build an empty string.
     */
    String();
    
    /**
     * Constructor.
     * 
     * Build a string from a std::string
     * @param str input string
     */
     String(const std::string& str);
     
    /**
     * Constructor.
     * 
     * Build a string from a C string
     * @param cstr input string
     */
     String(const char* cstr);
     
     /**
      * Constructor.
      * 
      * Build a string by duplicating n times a given character.
      * @param n number of repetitions
      * @param c character to be duplicated
      */
     String(size_type n, char c);
     
     /**
      * Copy constructor.
      * 
      * Build a string from an existing string.
      * @param other existing string
      */
     String(const String& other);
     
     /**
      * Assignment operator.
      * 
      * Build a string from assigning an existing one.
      * @param other existing string
      */
     String& operator=(const String& other);
     
     /**
      * Assignment operator.
      * 
      * Build a string from assigning an existing std::string
      * @param str existing standard string
      */
     String& operator=(const std::string& str);
     
     /**
      * Assignment operator.
      * 
      * Build a string from assigning an existing C string
      * @param cstr existing C string
      */
     String& operator=(const char* cstr);
     
    /**
     * Destructor.
     */
     virtual ~String();
    
    /**
     * Return the size of the string.
     * 
     * The number of bytes is returned.
     */
    size_type size() const;
    
    /**
     * Equality comparison.
     * 
     * Return true if both strings compared equal.
     * @param other string to be compared to
     */
     bool operator==(const String& other) const;

    /**
     * Equality comparison.
     * 
     * Return true if string and given standard string compare equals.
     * @param str standard string to be compared to
     */
     bool operator==(const std::string& str) const;

    /**
     * Equality comparison.
     * 
     * Return true if string and given C string compare equals.
     * @param str standard string to be compared to
     */
     bool operator==(const char* cstr) const;    
    
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
//     int toInt() const throw(ValueError);
//     operator std::string() const;
//     friend std::istream& getline(std::istream&, String&, char);
//     friend std::istream& getline(std::istream&, String&);
};

// std::istream& getline(std::istream&, String&, char);
// std::istream& getline(std::istream&, String&);

} //end of namespace snowball
#endif