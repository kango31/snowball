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
#include "list.hpp"
#include "../exceptions/exceptions.h"

#ifdef SNOWBALL_WITH_BOOST_HASH
#include <boost/functional/hash.hpp>
#endif //SNOWBALL_WITH_BOOST_HASH

namespace snowball
{


//==============================================================================
// DICTIONARY DECLARATION
//==============================================================================
    
/**
 * Implements a dictionary (hash table) on top of std::unordered_map.
 * 
 * The dictionary class works by default with boost::hash to provide hash values 
 * to keys. The key shall also have an operator== implemented to handle 
 * collisions in the hash table. This collision is by default checked by 
 * std::equal_to but may be tuned at convenience by user.
 * 
 * The hash tables provides constant time insertions and accesses. The downside 
 * resides in that hash table is unordered.
 */
template <typename Key, 
          typename Value,
#ifdef SNOWBALL_WITH_BOOST_HASH
          typename Hash=boost::hash<Key>,
#else
          typename Hash=std::hash<Key>,
#endif
          typename Pred=std::equal_to<Key>,
          typename Alloc=std::allocator<std::pair<const Key, Value> > >
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
     * Copy constructor
     * 
     * @param other dictionary to be copied
     */
    Dictionary(const Dictionary& other);
    
    /**
     * Assignment operator
     * 
     * @param other dictionary to be assigned from
     */
    Dictionary& operator=(const Dictionary& other);
    
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
     * If key does not exist, it is added to dictionary and the value associated
     * is generated from the default constructor of Value.
     * 
     * @param key key of item to be retrieved
     */
    Value& operator[](const Key& key);
    
    /**
     * Return item at specified key.
     * 
     * If key does not exist, it is added to dictionary and the value associated
     * is generated from the default constructor of Value.
     * 
     * @param key key of item to be retrieved
     */
    Value operator[](const Key& key) const;
    
    /**
     * Return item at specified key. If no such key exists, it returns instead
     * the default value provided and dictionary is left unchanged.
     * 
     * @param key  key of item to be retrieved
     * @param default value returned when key is not found
     */
    Value& get(const Key& key, Value& defaultValue);

    /**
     * Return item at specified key. If no such key exists, it returns instead
     * the default value provided and dictionary is left unchanged.
     * 
     * The move semantics here helps when a literal is passed as argument for 
     * default value.
     * 
     * @param key  key of item to be retrieved
     * @param default value returned when key is not found
     */
    Value& get(const Key& key, Value&& defaultValue);
    
    /**
     * Return item at specified key. If no such key exists, it returns instead
     * the default value provided and dictionary is left unchanged.
     * 
     * @param key  key of item to be retrieved
     * @param default value returned when key is not found
     */
    Value get(const Key& key, Value& defaultValue) const;

    /**
     * Return item at specified key. If no such key exists, it returns instead
     * the default value provided and dictionary is left unchanged.
     * 
     * The move semantics here helps when a literal is passed as argument for 
     * default value.
     * 
     * @param key  key of item to be retrieved
     * @param default value returned when key is not found
     */
    Value get(const Key& key, Value&& defaultValue) const;
    
    /**
     * Return a list of all dictionary keys.
     */
    List<Key> keys() const;

    /**
     * Return a list of all dictionary values.
     */
    List<Value> values() const;

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

template <typename K, typename V, typename H, typename P, typename A>
Dictionary<K, V, H, P, A>::Dictionary(const Dictionary& other)
    :m_map(other.m_map)
{ };

/*
 * Assignment operator
 */

template <typename K, typename V, typename H, typename P, typename A>
Dictionary<K, V, H, P, A>& Dictionary<K, V, H, P, A>::operator=(const Dictionary& other)
{ 
    if (this != &other)
        m_map = other.m_map;
    return *this;
};

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

/*
 * method: get
 */

template <typename K, typename V, typename H, typename P, typename A>
V& Dictionary<K, V, H, P, A>::get(const K& key, V& defaultValue)
{
    typename map_type::iterator it = m_map.find(key);
    if (it == m_map.end())
        return defaultValue;
    else
        return it->second;
}

template <typename K, typename V, typename H, typename P, typename A>
V& Dictionary<K, V, H, P, A>::get(const K& key, V&& defaultValue)
{
    typename map_type::iterator it = m_map.find(key);
    if (it == m_map.end())
        return defaultValue;
    else
        return it->second;
}

template <typename K, typename V, typename H, typename P, typename A>
V Dictionary<K, V, H, P, A>::get(const K& key, V& defaultValue) const
{
    typename map_type::const_iterator it = m_map.find(key);
    if (it == m_map.end())
        return defaultValue;
    else
        return it->second;
}

template <typename K, typename V, typename H, typename P, typename A>
V Dictionary<K, V, H, P, A>::get(const K& key, V&& defaultValue) const
{
    typename map_type::const_iterator it = m_map.find(key);
    if (it == m_map.end())
        return defaultValue;
    else
        return it->second;
}

/*
 * method: keys
 */

template <typename K, typename V, typename H, typename P, typename A>
List<K> Dictionary<K, V, H, P, A>::keys() const
{
    List<K> output;
    typename map_type::const_iterator it;
    for (it = m_map.begin(); it != m_map.end(); ++it)
        output.append(it->first);
    return output;
}

/*
 * method: values
 */

template <typename K, typename V, typename H, typename P, typename A>
List<V> Dictionary<K, V, H, P, A>::values() const
{
    List<V> output;
    typename map_type::const_iterator it;
    for (it = m_map.begin(); it != m_map.end(); ++it)
        output.append(it->second);
    return output;    
}
} //end of namespace snowball

#endif
