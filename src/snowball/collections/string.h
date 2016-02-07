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
#include <sstream>
#include <locale>
#include <algorithm>
#include <functional>
#ifdef SNOWBALL_WITH_BOOST_LOCALE
#include <boost/locale.hpp>
#endif

#include "list.hpp"
#include "snowball/exceptions/exceptions.h"

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
    
    /**
     * @typedef iterator
     * forward iterator for String
     */
    typedef typename std::string::iterator iterator;
    
    /**
     * @typedef const_iterator
     * forward iterator for const String
     */
    typedef typename std::string::const_iterator const_iterator;
    
    /**
     * @typedef reverse_iterator
     * reverse iterator for String
     */
    typedef typename std::string::reverse_iterator reverse_iterator;
    
    /**
     * @typedef iterator
     * reverse iterator for const String
     */
    typedef typename std::string::const_reverse_iterator const_reverse_iterator;

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
      * Constructor.
      * 
      * Build a string from a character.
      * 
      * @param c character
      */
     String(char c);
     
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
     
    /**
     * Non-equality comparison.
     * 
     * Return true if both strings compared not equal.
     * @param other string to be compared to
     */
    bool operator!=(const String& other) const;

    /**
     * Non-equality comparison.
     * 
     * Return true if string and given standard string compare not equal.
     * @param str standard string to be compared to
     */
    bool operator!=(const std::string& str) const;

    /**
     * Non-equality comparison.
     * 
     * Return true if string and given C string compare not equal.
     * @param str standard string to be compared to
     */
    bool operator!=(const char* cstr) const;
    
    /**
     * Lower than comparison
     * 
     * Return true if current string is before given string in lexicographic 
     * order.
     * @param other string to be compared to
     */
    bool operator<(const String& other) const;

    /**
     * Lower than comparison
     * 
     * Return true if current string is before given string in lexicographic 
     * order.
     * @param other string to be compared to
     */
    bool operator<(const std::string& str) const;

    /**
     * Lower than comparison
     * 
     * Return true if current string is before given string in lexicographic 
     * order.
     * @param other string to be compared to
     */
    bool operator<(const char* cstr) const;
    
    /**
     * Lower than or equal to comparison
     * 
     * Return true if current string is before given string in lexicographic 
     * order or compared equal.
     * @param other string to be compared to
     */
    bool operator<=(const String& other) const;

    /**
     * Lower than or equal to comparison
     * 
     * Return true if current string is before given string in lexicographic 
     * order or compared equal.
     * @param other string to be compared to
     */
    bool operator<=(const std::string& str) const;

    /**
     * Lower than or equal to comparison
     * 
     * Return true if current string is before given string in lexicographic 
     * order or compared equal.
     * @param other string to be compared to
     */
    bool operator<=(const char* cstr) const;
    
    /**
     * Greater than comparison
     * 
     * Return true if current string is after given string in lexicographic 
     * order.
     * @param other string to be compared to
     */
    bool operator>(const String& other) const;

    /**
     * Greater than comparison
     * 
     * Return true if current string is after given string in lexicographic 
     * order.
     * @param other string to be compared to
     */
    bool operator>(const std::string& str) const;

    /**
     * Greater than comparison
     * 
     * Return true if current string is after given string in lexicographic 
     * order.
     * @param other string to be compared to
     */
    bool operator>(const char* cstr) const;
    
    /**
     * Greater than or equal to comparison
     * 
     * Return true if current string is after given string in lexicographic 
     * order or compared equal.
     * @param other string to be compared to
     */
    bool operator>=(const String& other) const;

    /**
     * Greater than or equal to comparison
     * 
     * Return true if current string is after given string in lexicographic 
     * order or compared equal.
     * @param other string to be compared to
     */
    bool operator>=(const std::string& str) const;

    /**
     * Greater than or equal to comparison
     * 
     * Return true if current string is after given string in lexicographic 
     * order or compared equal.
     * @param other string to be compared to
     */
    bool operator>=(const char* cstr) const;
    
    /**
     * Stat whether string contain a character or a substring.
     *
     * @param sub substring to look for
     */
    bool contains(const std::string& sub) const;
    
    /**
     * Stat whether string contain a character or a substring.
     *
     * @param sub substring to look for
     */
    bool contains(const String& sub) const;
    
    /**
     * Stat whether string contain a character or a substring.
     *
     * @param sub substring to look for
     */
    bool contains(const char* sub) const;
    
    /**
     * Stat whether string contain a character or a substring.
     *
     * @param sub character to look for
     */
    bool contains(const char sub) const;
    
    /**
     * Stat whether string starts with specified character or string.
     * 
     * @param str string to look for
     */
    bool startsWith(const std::string& str) const;

    /**
     * Stat whether string starts with specified character or string.
     * 
     * @param str string to look for
     */
    bool startsWith(const String& str) const;
    
    /**
     * Stat whether string starts with specified character or string.
     * 
     * @param cstr string to look for
     */
    bool startsWith(const char* cstr) const;
    
    /**
     * Stat whether string starts with specified character or string.
     * 
     * @param c character to look for
     */
    bool startsWith(const char c) const;
    
    /**
     * Stat whether string ends with specified character or string.
     * 
     * @param str string to look for
     */
    bool endsWith(const std::string& str) const;

    /**
     * Stat whether string ends with specified character or string.
     * 
     * @param str string to look for
     */
    bool endsWith(const String& str) const;
    
    /**
     * Stat whether string ends with specified character or string.
     * 
     * @param cstr string to look for
     */
    bool endsWith(const char* cstr) const;
    
    /**
     * Stat whether string ends with specified character or string.
     * 
     * @param c character to look for
     */
    bool endsWith(const char c) const;
    
    /**
     * Split string into sub-string.
     * 
     * The string is split by space characters, end of line, line break or 
     * tabulation.
     * 
     * A list with substrings is returned.
     */
    List<String> split() const;
    
    /**
     * Split string into sub-string.
     * 
     * The string is split by characters in given string.
     * 
     * A list with substrings is returned.
     */
    List<String> split(const std::string& str) const;
    
    /**
     * Split string into sub-string.
     * 
     * The string is split by characters in given string.
     * 
     * A list with substrings is returned.
     */
    List<String> split(const String& str) const;
    
    /**
     * Split string into sub-string.
     * 
     * The string is split by characters in given string.
     * 
     * A list with substrings is returned.
     */
    List<String> split(const char* cstr) const;
    
    /**
     * Split string into sub-string.
     * 
     * The string is split by given character.
     * 
     * A list with substrings is returned.
     */
    List<String> split(const char c) const;
    
    /**
     * Strip the left of the string.
     * 
     * Remove all leading space characters.
     * 
     * @return reference to itself
     */
    String& leftStrip();
    
    /**
     * Strip the left of the string.
     * 
     * Remove all leading specified characters.
     * 
     * @param str characters to be removed
     * @return reference to itself
     */
    String& leftStrip(const std::string& str);
        
    /**
     * Strip the left of the string.
     * 
     * Remove all leading specified characters.
     * 
     * @param str characters to be removed
     * @return reference to itself
     */
    String& leftStrip(const String& str);
    
    /**
     * Strip the left of the string.
     * 
     * Remove all leading specified characters.
     * 
     * @param cstr characters to be removed
     * @return reference to itself
     */
    String& leftStrip(const char* cstr);
    
    /**
     * Strip the left of the string.
     * 
     * Remove all leading specified characters.
     * 
     * @param c character to be removed
     * @return reference to itself
     */
    String& leftStrip(const char c);

    /**
     * Strip the right of the string.
     * 
     * Remove all trailing space characters.
     * 
     * @return reference to itself
     */
    String& rightStrip();
    
    /**
     * Strip the right of the string.
     * 
     * Remove all trailing specified characters.
     * 
     * @param str characters to be removed
     * @return reference to itself
     */
    String& rightStrip(const std::string& str);
        
    /**
     * Strip the right of the string.
     * 
     * Remove all trailing specified characters.
     * 
     * @param str characters to be removed
     * @return reference to itself
     */
    String& rightStrip(const String& str);
    
    /**
     * Strip the right of the string.
     * 
     * Remove all trailing specified characters.
     * 
     * @param cstr characters to be removed
     * @return reference to itself
     */
    String& rightStrip(const char* cstr);
    
    /**
     * Strip the right of the string.
     * 
     * Remove all trailing specified characters.
     * 
     * @param c character to be removed
     * @return reference to itself
     */
    String& rightStrip(const char c);

    /**
     * Strip both sides of the string.
     * 
     * Remove all trailing and leading space characters.
     * 
     * @return reference to itself
     */
    String& strip();
    
    /**
     * Strip both sides of the string.
     * 
     * Remove all trailing and leading specified characters.
     * 
     * @param str characters to be removed
     * @return reference to itself
     */
    String& strip(const std::string& str);
        
    /**
     * Strip both sides of the string.
     * 
     * Remove all trailing and leading specified characters.
     * 
     * @param str characters to be removed
     * @return reference to itself
     */
    String& strip(const String& str);
    
    /**
     * Strip both sides of the string.
     * 
     * Remove all trailing and leading specified characters.
     * 
     * @param cstr characters to be removed
     * @return reference to itself
     */
    String& strip(const char* cstr);
    
    /**
     * Strip both sides of the string.
     * 
     * Remove all trailing and leading specified characters.
     * 
     * @param c character to be removed
     * @return reference to itself
     */
    String& strip(const char c);

    /**
     * Strip the left of the string.
     * 
     * Remove all leading space characters.
     * 
     * @return a new string
     */
    String leftStrip() const;
    
    /**
     * Strip the left of the string.
     * 
     * Remove all leading specified characters.
     * 
     * @param str characters to be removed
     * @return a new string
     */
    String leftStrip(const std::string& str) const;
        
    /**
     * Strip the left of the string.
     * 
     * Remove all leading specified characters.
     * 
     * @param str characters to be removed
     * @return a new string     
     */
    String leftStrip(const String& str) const;
    
    /**
     * Strip the left of the string.
     * 
     * Remove all leading specified characters.
     * 
     * @param cstr characters to be removed
     * @return a new string
     */
    String leftStrip(const char* cstr) const;
    
    /**
     * Strip the left of the string.
     * 
     * Remove all leading specified characters.
     * 
     * @param c character to be removed
     * @return a new string
     */
    String leftStrip(const char c) const;

    /**
     * Strip the right of the string.
     * 
     * Remove all trailing space characters.
     * 
     * @return a new string
     */
    String rightStrip() const;
    
    /**
     * Strip the right of the string.
     * 
     * Remove all trailing specified characters.
     * 
     * @param str characters to be removed
     * @return a new string
     */
    String rightStrip(const std::string& str) const;
        
    /**
     * Strip the right of the string.
     * 
     * Remove all trailing specified characters.
     * 
     * @param str characters to be removed
     * @return a new string
     */
    String rightStrip(const String& str) const;
    
    /**
     * Strip the right of the string.
     * 
     * Remove all trailing specified characters.
     * 
     * @param cstr characters to be removed
     * @return a new string
     */
    String rightStrip(const char* cstr) const;
    
    /**
     * Strip the right of the string.
     * 
     * Remove all trailing specified characters.
     * 
     * @param c character to be removed
     * @return a new string
     */
    String rightStrip(const char c) const;

    /**
     * Strip both sides of the string.
     * 
     * Remove all trailing and leading space characters.
     * 
     * @return a new string
     */
    String strip() const;
    
    /**
     * Strip both sides of the string.
     * 
     * Remove all trailing and leading specified characters.
     * 
     * @param str characters to be removed
     * @return a new string
     */
    String strip(const std::string& str) const;
        
    /**
     * Strip both sides of the string.
     * 
     * Remove all trailing and leading specified characters.
     * 
     * @param str characters to be removed
     * @return a new string
     */
    String strip(const String& str) const;
    
    /**
     * Strip both sides of the string.
     * 
     * Remove all trailing and leading specified characters.
     * 
     * @param cstr characters to be removed
     * @return a new string
     */
    String strip(const char* cstr) const;
    
    /**
     * Strip both sides of the string.
     * 
     * Remove all trailing and leading specified characters.
     * 
     * @param c character to be removed
     * @return a new string
     */
    String strip(const char c) const;
    
    /**
     * Switch all characters to upper case.
     * 
     * Non-letter characters remain unchanged.
     * 
     * @return a reference to itself
     */
    String& upper();
    
    /**
     * Return a copy with all characters switched to upper case.
     * 
     * Non-letter characters remain unchanged.
     */
    String upper() const;
    
    /**
     * Switch all characters to lower case.
     * 
     * Non-letter characters remain unchanged.
     * 
     * @return a reference to itself
     */
    String& lower();
    
    /**
     * Return a copy with all characters switched to lower case.
     * 
     * Non-letter characters remain unchanged.
     */
    String lower() const;

    /**
     * Convert string into int.
     * 
     * @param base base in which literal is written
     * @throw ValueError if string does not represent a valid literal
     */
    int toInt(int base = 10) const throw(ValueError);
    
    /**
     * Convert string into float.
     * 
     * @throw ValueError if string does not represent a valid literal
     */
    float toFloat() const throw(ValueError);
    
    /**
     * Convert string into double.
     * 
     * @throw ValueError if string does not represent a valid literal
     */
    double toDouble() const throw(ValueError);
    
    /**
     * Convert string into bool.
     * 
     * @throw ValueError if string does not represent a valid literal
     */
    bool toBool() const throw(ValueError);

    /**
     * Convert into STL string
     */
    operator std::string() const;
    
    /**
     * Return iterator to begin of string.
     */
    iterator begin();
    
    /**
     * Return iterator to end of string.
     */
    iterator end();
    
    /**
     * Return reverse iterator to begin of string.
     */
    reverse_iterator rbegin();
    
    /**
     * Return reverse iterator to end of string.
     */
    reverse_iterator rend();

    /**
     * Return iterator to begin of const string.
     */
    const_iterator begin() const;
    
    /**
     * Return iterator to end of const string.
     */
    const_iterator end() const;
    
    /**
     * Return reverse iterator to begin of const string.
     */
    const_reverse_iterator rbegin() const;
    
    /**
     * Return reverse iterator to end of const string.
     */
    const_reverse_iterator rend() const;

    
    friend std::ostream& operator<<(std::ostream& os, const String& str);
    friend std::istream& operator>>(std::istream& is, String& str);
    
    friend std::istream& getline(std::istream&, String&, char);
    friend std::istream& getline(std::istream&, String&);
};

/**
 * Operator<<
 * 
 * Send string to output stream.
 * 
 * @param str string
 * @param os output stream
 */
std::ostream& operator<<(std::ostream& os, const String& str);

/**
 * Operator>>
 * 
 * Get a string from input stream.
 * 
 * @param str string
 * @param is input stream
 */
std::istream& operator>>(std::istream& is, String& str);

/**
 * Getline
 * 
 * Extract characters from input stream and put them in string until end-of-line
 * character is encountered.
 * 
 * @param is input stream
 * @param str output string
 */
std::istream& getline(std::istream& is, String& str);

/**
 * Getline
 * 
 * Extract characters from input stream and put them in string until delimiter
 * character is encountered.
 * 
 * @param is input stream
 * @param str output string
 * @param delim delimiter character
 */
std::istream& getline(std::istream& is, String& str, char delim);

#ifdef SNOWBALL_WITH_BOOST_LOCALE
/**
 * This enables to set once and for all locale settings for boost locale
 */
static boost::locale::generator __gen;
static std::locale __loc = std::locale::global(__gen(""));
#endif

} //end of namespace snowball
#endif