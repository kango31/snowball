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

#ifndef SNOWBALL_ALGORITHMS_H
#define SNOWBALL_ALGORITHMS_H

#include <algorithm>

#include "list.hpp"

namespace snowball
{

/**
 * Return the maximum value from a collection.
 * 
 * @tparam Container container type
 * @param cont container from which max has to be extracted
 */
template <typename Container>
typename Container::value_type& max(Container& cont)
{
    typename Container::iterator it;
    it = std::max_element(cont.begin(), cont.end());
    return *it;
}

/**
 * Return the maximum value from a collection.
 * 
 * @tparam Container container type
 * @param cont container from which max has to be extracted
 */
template <typename Container>
const typename Container::value_type& max(const Container& cont)
{
    typename Container::const_iterator it;
    it = std::max_element(cont.begin(), cont.end());
    return *it;
}

/**
 * Return the argmax (index at which value is maximum) from a collection.
 * 
 * @tparam Container container type
 * @param cont container from which argmax has to be extracted
 */
template <typename Container>
typename Container::index_type argmax(const Container& cont)
{
    typename Container::const_iterator it;
    it = std::max_element(cont.begin(), cont.end());
    return it - cont.begin();
}

/**
 * Return the minimum value from a collection.
 * 
 * @tparam Container container type
 * @param cont container from which min has to be extracted
 */
template <typename Container>
typename Container::value_type& min(Container& cont)
{
    typename Container::iterator it;
    it = std::min_element(cont.begin(), cont.end());
    return *it;
}

/**
 * Return the minimum value from a collection.
 * 
 * @tparam Container container type
 * @param cont container from which min has to be extracted
 */
template <typename Container>
const typename Container::value_type& min(const Container& cont)
{
    typename Container::const_iterator it;
    it = std::min_element(cont.begin(), cont.end());
    return *it;
}

/**
 * Return the argmin (index at which value is minimum) from a collection.
 * 
 * @tparam Container container type
 * @param cont container from which argmin has to be extracted
 */
template <typename Container>
typename Container::index_type argmin(const Container& cont)
{
    typename Container::const_iterator it;
    it = std::min_element(cont.begin(), cont.end());
    return it - cont.begin();
}

//Forward declaration of List template
template <typename T, typename Alloc> class List;

/**
 * Filter the given collection.
 * 
 * All items from the given collection passing a predicate test are included 
 * in the output collection.
 * 
 * The predicate is provided as a function pointer which signature is:
 * 
 * ~~~~~{.cpp}
 * bool (const typename Container::value_type&)
 * ~~~~~
 * 
 * @tparam Container container type
 * @param funcptr a function pointer predicate
 * @param cont container to be filtered
 * @param output output list with filtered items
 */
template <typename Container>
void filter(bool (*funcptr)(const typename Container::value_type& item),
            const Container& cont, 
            List<typename Container::value_type>& output)
{
    typename Container::const_iterator it;
    for(it = cont.begin(); it != cont.end(); ++it)
    {
        if (funcptr(*it))
            output.append(*it);
    }
}

/**
 * Filter the given collection.
 * 
 * All items from the given collection passing a predicate test are included 
 * in the output collection.
 * 
 * The predicate is provided as a functor which signature is:
 * 
 * ~~~~~{.cpp}
 * bool (const typename Container::value_type&)
 * ~~~~~
 * 
 * @tparam Container container type
 * @param pred a predicate functor
 * @param cont container to be filtered
 * @param output output list with filtered items
 */
template <typename Container, typename Predicate>
void filter(const Predicate& pred,
            const Container& cont, 
            List<typename Container::value_type>& output)
{
    typename Container::const_iterator it;
    for(it = cont.begin(); it != cont.end(); ++it)
    {
        if (pred(*it))
            output.append(*it);
    }
}

/**
 * Apply a function to all member in the list and return results in a list.
 * 
 * The function to be applied is provided as a functor and its signature must 
 * be:
 * 
 * ~~~~~{.cpp}
 * Result (const typename Container::value_type&)
 * ~~~~~
 * 
 * @tparam Container container type
 * @tparam Function functor type
 * @tparam Result type of output result of function
 * @param func functor to be applied
 * @param cont container to be filtered
 * @param output output list with processed items
 */
template <typename Container, typename Function, typename Result>
void map(const Function& func, 
         const Container& cont, 
         List<Result>& output)
{
    typename Container::const_iterator it;
    for(it = cont.begin(); it != cont.end(); ++it)
    {
        output.append(func(*it));
    }
}

/**
 * Apply a function to all member in the list and return results in a list.
 * 
 * The function to be applied is provided as a function pointer and its 
 * signature must be:
 * 
 * ~~~~~{.cpp}
 * Result (const typename Container::value_type&)
 * ~~~~~
 * 
 * @tparam Container container type
 * @tparam Function functor type
 * @tparam Result type of output result of function
 * @param funcptr function pointer
 * @param cont container to be filtered
 * @param output output list with processed items
 */
template <typename Container, typename Result>
void map(bool (*funcptr)(const typename Container::value_type&),
         const Container& cont, 
         List<Result>& output)
{
    typename Container::const_iterator it;
    for(it = cont.begin(); it != cont.end(); ++it)
    {
        output.append(funcptr(*it));
    }
}
         
} //end of snowball namespace

#endif