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

#ifndef SNOWBALL_DICTIONARY_HPP
#define SNOWBALL_DICTIONARY_HPP

#include <unordered_map>
#include <stdexcept>

#include "hash.hpp"
#include "../exceptions/exceptions.h"

namespace snowball
{

//==============================================================================
// DICTIONARY DECLARATION
//==============================================================================
    
/**
 * Implements a dictionary (hash table) on top of std::unordered_map.
 * 
 * The dictionary class works be default with std::hash to provide hash values 
 * to keys. The key shall also have an operator== implemented to handle 
 * collisions in the hash table. This collision is by default checked by 
 * std::equal_to but may be tuned at convenience by user.
 * 
 * The hash tables provides constant time insertions and accesses. The downside 
 * resides in that hash table is unordered.
 */
template <typename Key, 
          typename Value, 
          typename Hash=std::hash<Key>,
          typename Pred=std::equal_to<Key>,
          typename Alloc=std::allocator<std::pair<Key, Value> > >
class Dictionary
{
private:
    
    /**
     * @typedef map_type 
     * Type of underlying std::unordered_map
     */
    typedef typename std::unordered_map<Key, Value, Hash, Pred, Alloc> map_type;

public:
    
    /**
     * @typedef size_type
     * Type of dictionary size
     */
    typedef typename map_type::size_type size_type;
    
    /**
     * Constructor
     * 
     * Default constructor for empty Dictionary.
     */
    Dictionary();
    
    /**
     * Destructor
     */
    virtual ~Dictionary();
    
    /**
     * Return size of dictionary.
     * 
     * The number of pairs in the dictionary is returned.
     */
    size_type size() const;
    
    /**
     * Return item at specified key.
     * 
     * @param key
     */
    Value& operator[](const Key& key);
    
    /**
     * Return item at specified key.
     * 
     * @param key
     */
    Value operator[](const Key& key) const;
    
    
private:

    /**
     * Attributes
     */
    map_type m_map;
    
};
    
//==============================================================================
// DICTIONARY DEFINITION
//==============================================================================

/*
 * Constructor
 */

template <typename K, typename V, typename H, typename P, typename A>
Dictionary<K, V, H, P, A>::Dictionary() { };

/*
 * Destructor
 */

template <typename K, typename V, typename H, typename P, typename A>
Dictionary<K, V, H, P, A>::~Dictionary() { };

/*
 * Method: size
 */

template <typename K, typename V, typename H, typename P, typename A>
typename Dictionary<K, V, H, P, A>::size_type 
Dictionary<K, V, H, P, A>::size() const
{
    return m_map.size();
}

/*
 * method: operator[]
 */

template <typename K, typename V, typename H, typename P, typename A>
V& Dictionary<K, V, H, P, A>::operator[](const K& key)
{
    return m_map[key];
}

template <typename K, typename V, typename H, typename P, typename A>
V Dictionary<K, V, H, P, A>::operator[](const K& key) const
{
    return m_map[key];
}

} //end of namespace snowball

#endif
