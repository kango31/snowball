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

#ifndef SNOWBALL_ITERATOR_H
#define SNOWBALL_ITERATOR_H

namespace snowball
{

/**
 * @brief interface class for snowball iterators
 * 
 * @tparam T type of items returned by iterator
 * 
 * This class is used as an abstract interface for all concrete iterators 
 * made available through the snowball library.
 * It implements the Iterator design pattern.
 */

template <typename T>
class Iterator
{
    public:
        
    /**
     * Make iterator points to the first item of container.
     */
    virtual void first() = 0;
    
    /**
     * Move the iterator to the next item in the container.
     */
    virtual void next() = 0;
    
    /**
     * Stat whether the iteration is over.
     */
    virtual bool isDone() = 0;
    
    /**
     * Return item currently pointed by iterator.
     */
    virtual T& currentItem() = 0;
    
    protected:
       
    /**
     * Constructor.
     */
    Iterator() { };
    
};

template <typename T>
class Iterator<const T>
{
    public:
    
    /**
     * Make iterator points to the first item of container.
     */
    virtual void first() = 0;
    
    /**
     * Move the iterator to the next item in the container.
     */
    virtual void next() = 0;
    
    /**
     * Stat whether the iteration is over.
     */
    virtual bool isDone() = 0;
    
    /**
     * Return item currently pointed by iterator.
     */
    virtual const T& currentItem() = 0;
    
    protected:
       
    /**
     * Constructor.
     */
    Iterator() { };
};
    
} //end of snowball namespace

#endif