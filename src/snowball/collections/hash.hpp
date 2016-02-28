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

#ifndef SNOWBALL_HASH_HPP
#define SNOWBALL_HASH_HPP

namespace snowball
{  
/**
 * This class provides a default hash function to all objects for which 
 * std::hash has not been specialized. This hash function performance is not 
 * extraordinary and shall be specialized by user to improve efficiency.
 * 
 * This class is taken from Bjarne Stroustrup textbook The C++ Programming 
 * Language, special edition.
 * 
 * @tparam T object for which has is going to be calculated
 */
template <typename T>
struct Hash
{
    /**
     * Operator()
     * 
     * Hash object is a functor and this operator is the only one member that 
     * is implemented.
     * 
     * @param key value to be hashed
     * @returns hash of object
     */
    size_t operator()(const T& key) const
    {
        size_t res = 0;
        size_t len = sizeof(T);
        const char* p = reinterpret_cast<const char*>(&key);
        while(len--)
            res = (res << 1)^*p++;
        return res;
    };
};

/**
 * Specialization of Hash for long
 * 
 * We use std::hash.
 */
template <>
struct Hash<long>
{
    /**
     * Operator()
     * 
     * Hash object is a functor and this operator is the only one member that 
     * is implemented.
     * 
     * @param key value to be hashed
     * @returns hash of object
     */
    size_t operator()(const long& key) const
    {
        return std::hash<long>()(key);
    };
};

/**
 * Specialization of Hash for int
 * 
 * We use std::hash.
 */
template <>
struct Hash<int>
{
    /**
     * Operator()
     * 
     * Hash object is a functor and this operator is the only one member that 
     * is implemented.
     * 
     * @param key value to be hashed
     * @returns hash of object
     */
    size_t operator()(const int& key) const
    {
        return std::hash<int>()(key);
    };
};

/**
 * Specialization of Hash for std::string
 * 
 * We use std::hash.
 */
template <>
struct Hash<std::string>
{
    /**
     * Operator()
     * 
     * Hash object is a functor and this operator is the only one member that 
     * is implemented.
     * 
     * @param key value to be hashed
     * @returns hash of object
     */
    size_t operator()(const std::string& key) const
    {
        return std::hash<std::string>()(key);
    };
};

} //end of snowball namespace

#endif