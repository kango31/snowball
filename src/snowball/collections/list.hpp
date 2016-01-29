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

#ifndef SNOWBALL_LIST_H
#define SNOWBALL_LIST_H

#include <vector>
#include <exception>
#include <algorithm>

#include "snowball/exceptions/exceptions.h"
#include "iterator.h"


namespace snowball
{
    
//==============================================================================
// LIST DECLARATION
//==============================================================================
    
/**
 * @brief Implements a list on top of std::vector.
 * 
 * @tparam T type of items in the list
 * @tparam Alloc allocator to use for items
 * 
 * @warning index of std::vector is an unsigned integer of type 
 * std::vector::size_type. As list accepts negative index those methods take 
 * a long integer as input.
 * 
 * @note due to systematic index range check, operator[] method is slower than
 * the one from std::vector. In case you need a fast operator[] consider using 
 * a std::vector instead.
 * 
 * Fast methods of list:
 * - List<T, Alloc>::append
 * - List<T, Alloc>::pop (with no index specified)
 * 
 * Potentially slow methods because it requires to potentially navigate
 * throug the whole list:
 * - List<T, Alloc>::contains
 * - List<T, Alloc>::index
 * - List<T, Alloc>::count
 * 
 * Potentially slow methods because it causes an internal move of items:
 * - List<T, Alloc>::pop from anywhere in the list but last index
 * - List<T, Alloc>::insert
 * - List<T, Alloc>::remove
 */
template <typename T, typename Alloc = std::allocator<T> >
class List
{
    
    public:
    
    /**
     * @typedef size_type
     * size type for list
     */
    typedef typename std::vector<T, Alloc>::size_type size_type;
    
    /**
     * @typedef value_type
     * value type of list
     */    
    typedef typename std::vector<T, Alloc>::value_type value_type;
    
    /**
     * @typedef allocator_type
     * allocator type of list
     */
    typedef typename std::vector<T, Alloc>::allocator_type allocator_type;
    
    /**
     * @typedef iterator
     * a random access iterator to List<T, Alloc>::value_type
     */
    typedef typename std::vector<T, Alloc>::iterator iterator;
    
    /**
     * @typedef const_iterator
     * a random access iterator to const List<T, Alloc>::value_type
     */
    typedef typename std::vector<T, Alloc>::const_iterator const_iterator;

    /**
     * @typedef reverse_iterator
     * a random access reverse iterator to List<T, Alloc>::value_type
     */
    typedef typename std::vector<T, Alloc>::reverse_iterator reverse_iterator;
    
    /**
     * @typedef const_reverse_iterator
     * a random access reverse iterator to const List<T, Alloc>::value_type
     */
    typedef typename std::vector<T, Alloc>::const_reverse_iterator const_reverse_iterator;

    /**
     * @typedef index_type
     * the index type for list is size_type
     */
    typedef size_type index_type;
    
    public:
        
    /**
     * Constructor
     * 
     * Creates an empty list.
     * 
     * ~~~~~~~~~~~~~~~~~~~~~{.cpp}
     * List<int> list;
     * ~~~~~~~~~~~~~~~~~~~~~
     * 
     * @param alloc allocator to use for items
     */
    List(const allocator_type& alloc = allocator_type());
    
    /**
     * Constructor
     * 
     * ~~~~~~~~~~~~~~~~~~~~~{.cpp}
     * List<int> list = {0, 1, 2, 3};
     * ~~~~~~~~~~~~~~~~~~~~~
     * 
     * Creates a list from an initializer list
     * @param il initializer list
     * @param alloc allocator to use for items
     */
    List(std::initializer_list<T> il, 
         const allocator_type& alloc = allocator_type());
    
    /**
     * Constructor
     * 
     * Creates a list with duplicated constant value
     * 
     * ~~~~~~~~~~~~~~~~~~~~~{.cpp}
     * List<int> list(3, 0);
     * //list contains {0, 0, 0}
     * ~~~~~~~~~~~~~~~~~~~~~
     * 
     * @param number number of copies
     * @param value constant value
     * @param alloc allocator to use for items
     */
    List(size_type number, const T& value, 
         const allocator_type& alloc = allocator_type());
    
    /**
     * Constructor
     * 
     * Creates a list from an existing vector
     * 
     * ~~~~~~~~~~~~~~~~~~~~~{.cpp}
     * std::vector<int> vect = {0, 1, 2, 3};
     * List<int> list(vect);
     * //list contains {0, 1, 2, 3}
     * ~~~~~~~~~~~~~~~~~~~~~
     * 
     * @param vect existing vector
     * @param alloc allocator to use for items
     */
    List(const std::vector<T, Alloc>& vect, 
         const allocator_type& alloc = allocator_type());
    
    /**
     * Copy constructor
     * 
     * ~~~~~~~~~~~~~~~~~~~~~{.cpp}
     * List<int> list1 = {0, 2, 4, 6};
     * List<int> list2(list1);
     * //list2 contains {0, 2, 4, 6}
     * ~~~~~~~~~~~~~~~~~~~~~
     * 
     * @param other existing list
     */
    List(const List<T, Alloc>& other);
    
    /**
     * Copy constructor with allocator
     * 
     * ~~~~~~~~~~~~~~~~~~~~~{.cpp}
     * List<int> list1 = {0, 2, 4, 6};
     * List<int> list2(list1);
     * //list2 contains {0, 2, 4, 6}
     * ~~~~~~~~~~~~~~~~~~~~~
     * 
     * Creates a list from an existing one
     * @param other existing list
     * @param alloc allocator to use for items
     */
    List(const List<T, Alloc>& other, const allocator_type& alloc);
        
    /**
     * Destructor
     */
    virtual ~List();
    
    /**
     * Assignment operator with another list
     * 
     * ~~~~~~~~~~~~~~~~~~~~~{.cpp}
     * List<int> list1 = {0, 2, 4, 6};
     * List<int> list2 = {1, 2, 3};
     * list2 = list1;
     * //list2 contains {0, 2, 4, 6}
     * ~~~~~~~~~~~~~~~~~~~~~
     * 
     * @param other existing list
     */
    List<T, Alloc>& operator=(const List<T, Alloc>& other);
    
    /**
     * Assignment operator with a vector
     * 
     * ~~~~~~~~~~~~~~~~~~~~~{.cpp}
     * List<int> list1 = {0, 2, 4, 6};
     * List<int> list2 = {1, 2, 3};
     * list2 = list1;
     * //list2 contains {0, 2, 4, 6}
     * ~~~~~~~~~~~~~~~~~~~~~
     * 
     * @param vect existing vector
     */
    List<T, Alloc>& operator=(const std::vector<T, Alloc>& vect);
    
    /**
     * Assignment operator from an initializer list
     * 
     * ~~~~~~~~~~~~~~~~~~~~~{.cpp}
     * List<int> list = {1, 2, 3};
     * list2 = {0, 2, 4, 6}
     * //list2 contains {0, 2, 4, 6}
     * ~~~~~~~~~~~~~~~~~~~~~
     * 
     * @param il initializer list
     */
    List<T, Alloc>& operator=(std::initializer_list<T> il);
    
    /**
     * Return list size
     * 
     * ~~~~~~~~~~~~~~~~~~~~~{.cpp}
     * List<int> list = {0, 2, 4};
     * list.size(); //returns 3
     * ~~~~~~~~~~~~~~~~~~~~~
     * 
     * @return the number of items in the list
     */
    size_type size() const;
    
    /**
     * Return an item from the list at specified index.
     * 
     * This operator enables to change the value of item at specified index.
     * If specified index is negative, operator[] returns items from the end
     * of the list:
     * 
     * ~~~~~~~~~~~~~~~~~~~~~{.cpp}
     * List<int> list = {0, 2, 4, 6};
     * list[-1] = -6;
     * list[-2] = -4;
     * //list now contains {0, 2, -4, -6}
     * ~~~~~~~~~~~~~~~~~~~~~
     * 
     * @param index index of item
     * @throw IndexError if index is out of range
     */
    T& operator[](long index) throw(IndexError);
    
    /**
     * Return an item from the list at specified index.
     * 
     * This operator avoids the change of the item value.
     * If specified index is negative, operator[] returns items from the end
     * of the list:
     * 
     * ~~~~~~~~~~~~~~~~~~~~~{.cpp}
     * List<int> list = {0, 2, 4, 6};
     * list[-1]; //returns 6
     * list[-2]; //returns 4
     * ~~~~~~~~~~~~~~~~~~~~~
     * 
     * @param index index of item
     * @throw IndexError if index is out of range
     */
    const T& operator[](long index) const throw(IndexError);
    
    /**
     * Item-wise equality comparison with another list. 
     * 
     * If given list has the same size that current list and items at given 
     * index are all the same, lists are considered to be equal.
     * 
     * T list parameter shall implement operator!= for that method to be used.
     * 
     * ~~~~~~~~~~~~~~~~~~~~~{.cpp}
     * List<int> list1 = {1, 3, 5, 7};
     * List<int> list2 = {1, 3, 5};
     * List<int> list3 = {1, 3, 5};
     * list1 == list2; //returns false
     * list2 == list3; //returns true
     * ~~~~~~~~~~~~~~~~~~~~~
     * 
     * @param other list to be compared to
     * @return true if both lists are equal
     */
    bool operator==(const List<T, Alloc>& other) const;
    
    /**
     * Append an item to the end of the list
     * 
     * This method is fast.
     * 
     * @param item item to be append
     */
    void append(const T& item);
    
    /**
     * Insert an item in the list before specified index
     * 
     * If a negative index is specified, it is applied from the end of the list.
     * This method never throw an IndexError exception like opreator[] does: 
     * if index is beyond end of the list, item is inserted in last position and
     * if index is beyond start of the list it is inserted at begining of the 
     * list.
     * 
     * ~~~~~~~~~~~~~~~~~~~~~{.cpp}
     * List<int> list = {0, 1, 2};
     * list.insert(10, 3); //list is now {0, 1, 2, 3}
     * list.insert(-10, 4); //list is now {4, 0, 1, 2, 3}
     * list.insert(2, 5); //list is now {4, 0, 5, 1, 2, 3}
     * list.insert(0, 6); //list is now {4, 0, 5, 1, 2, 3}
     * list.insert(-1, 7); //list is now {4, 0, 5, 1, 2, 7, 3}
     * ~~~~~~~~~~~~~~~~~~~~~
     * @param index index where item is going to be inserted
     * @param item item to be inserted
     */
    void insert(long index, const T& item);
    
    /**
     * Insert another list before specified index.
     * 
     * If a negative index is specified, it is applied from the end of the list.
     * This method never throw an IndexError exception like opreator[] does: 
     * if index is beyond end of the list, item is inserted in last position and
     * if index is beyond start of the list it is inserted at begining of the 
     * list.
     * 
     * ~~~~~~~~~~~~~~~~~~~~~{.cpp}
     * List<int> list = {0, 1, 2};
     * list.insert(1, List<int>({3, 4, 5})); //list is now {0, 3, 4, 5, 1, 2}
     * ~~~~~~~~~~~~~~~~~~~~~
     * @param index index where item is going to be inserted
     * @param other other list to be inserted into current one
     */
    void insert(long index, const List<T, Alloc>& other);
    
    /**
     * Check wether a given item is in the list
     * 
     * @param item item to be looked for
     */
    bool contains(const T& item) const;

    /**
     * Remove and return an item from the list at specified index
     * 
     * If specified index is negative, operator[] returns items from the end
     * of the list.
     * 
     * If no index is specified, the last item from the list is returned.
     * 
     * If specified index is out of range or list is empty, an IndexError 
     * exception is thrown.
     * 
     * @param index index at which item shall be removed and returned
     * @throw IndexError if index is out of range
     */
    T pop(long index = -1) throw(IndexError);
    
    /**
     * Return the index of item in the list.
     * 
     * If item is not found, a ValueError exception is thrown.
     * 
     * @param item to be looked for
     * @throw ValueError if item is not in list
     */
    size_type index(const T item) const throw(ValueError);
    
    /**
     * Extend the content of current list by the one of provided list.
     * 
     * @param list list used to extend current one
     */
    void extend(const List<T, Alloc>& other);
    
    /**
     * Operator+=
     * 
     * This methods does exactely the same than List<T, Alloc>::extend.
     * 
     * @param list list used to extend current one
     */
    void operator+=(const List<T, Alloc>& other);
    
    /**
     * Operator+
     * 
     * This method return a new list that is a copy of current list extended 
     * by the items of the second list.
     * 
     * @param other list to be extended to the copy of current list
     */
    List<T, Alloc> operator+(const List<T, Alloc>& other) const;
    
    /**
     * Remove the first item in the list with specified value.
     * 
     * @param item item to be removed from the list
     * @throw ValueError if item is not in list
     */
    void remove(const T& item) throw(ValueError);

    /**
     * Count number of occurences of given item.
     * 
     * @param item item to count
     */
    size_type count(const T& item) const;
    
    /**
     * Reverse list.
     * 
     * The last item becomes first, the last but one becomes second an so on.
     */
    void reverse();
    
    /**
     * Sort list.
     * 
     * This method uses the operator< of T and cannot be used if this operator 
     * is not defined.
     */
    void sort();
    
    /**
     * Sort list.
     * 
     * This method uses a function provided as argument.
     * 
     * @param funcptr sorting function
     */
    void sort(bool (*funcptr)(const T&, const T&));
    
    /**
     * Sort list.
     * 
     * This method uses a functor object provided as argument.
     * The functor object must have an operator() method.
     * 
     * @param functor sorting functor of type Compare
     */
    template <typename Compare>
    void sort(const Compare& functor);
        
    /**
     * Iterator to the begin of the list.
     */
    iterator begin();
    
    /**
     * Const iterator to the begin of the list.
     */
    const_iterator begin() const;

    /**
     * Iterator to the end of the list.
     */
    iterator end();
    
    /**
     * Const iterator to the end of the list.
     */
    const_iterator end() const;
    
    /**
     * Reverse iterator to the reverse begining of the list.
     */
    reverse_iterator rbegin();
    
    /**
     * Const reverse iterator to the reverse begining of the list.
     */
    const_reverse_iterator rbegin() const;

    /**
     * Reverse iterator to the reverse end of the list.
     */
    reverse_iterator rend();
    
    /**
     * Const reverse iterator to the reverse end of the list.
     */
    const_reverse_iterator rend() const;
    
    /**
     * Clear all items from the list.
     */
    void clear();
    
    
    private:
    
    std::vector<T, Alloc> m_vector;
    
}; // end of List class

//==============================================================================
// LIST DEFINITION
//==============================================================================

//Constructor

template <typename T, typename Alloc>
List<T, Alloc>::List(const allocator_type& alloc) 
{ }

template <typename T, typename Alloc>
List<T, Alloc>::List(std::initializer_list<T> il, 
                     const allocator_type& alloc): m_vector(il, alloc) { };

template <typename T, typename Alloc>
List<T, Alloc>::List(size_type n, const T& v, const allocator_type& alloc): 
    m_vector(n, v, alloc) { };

template <typename T, typename Alloc>
List<T, Alloc>::List(const std::vector<T, Alloc>& vect, 
                     const allocator_type& alloc): m_vector(vect, alloc) { };

template <typename T, typename Alloc>
List<T, Alloc>::List(const List<T, Alloc>& other): m_vector(other.m_vector) { };

template <typename T, typename Alloc>
List<T, Alloc>::List(const List<T, Alloc>& other, const allocator_type& alloc): 
    m_vector(other.m_vector, alloc) { };

//Assignment operator
    
template <typename T, typename Alloc>
List<T, Alloc>& List<T, Alloc>::operator=(const List<T, Alloc>& other)
{
    m_vector = other.m_vector;
    return *this;
}

template <typename T, typename Alloc>
List<T, Alloc>& List<T, Alloc>::operator=(const std::vector<T, Alloc>& vect)
{
    m_vector = vect;
    return *this;
}

template <typename T, typename Alloc>
List<T, Alloc>& List<T, Alloc>::operator=(std::initializer_list<T> il)
{
    m_vector = il;
    return *this;
}

//Destructor

template <typename T, typename Alloc>
List<T, Alloc>::~List() { }

//size method

template <typename T, typename Alloc>
typename List<T, Alloc>::size_type List<T, Alloc>::size() const
{
    return m_vector.size();
}

//operator[]

template <typename T, typename Alloc>
T& List<T, Alloc>::operator[](long index) throw(IndexError)
{
    if (index < 0)
        index += size();
    try
    {
        return m_vector.at(index);
    }
    catch (std::out_of_range& e)
    {
        THROW(IndexError, "index out of range");
    }
}
    
template <typename T, typename Alloc>
const T& List<T, Alloc>::operator[](long index) const throw(IndexError)
{
    if (index < 0)
        index += size();
    try
    {
        return m_vector.at(index);
    }
    catch (std::out_of_range& e)
    {
        THROW(IndexError, "index out of range");
    }
}

//operator==

template <typename T, typename Alloc>
bool List<T, Alloc>::operator==(const List<T, Alloc>& other) const
{
    if (size() != other.size())
        return false;
    else
    {
        for (int i = 0; i < size(); ++i)
        {
            if (m_vector.at(i) != other.m_vector.at(i))
                return false;
        }
    return true;
    }
}

//method append

template <typename T, typename Alloc>
void List<T, Alloc>::append(const T& item)
{
    m_vector.push_back(item);
}

//method insert

template <typename T, typename Alloc>
void List<T, Alloc>::insert(long index, const T& item)
{
    size_type n = size();
    if (index < 0)
    {
        index += n;
        index = std::max(long(0), index);
    }
    index = std::min(index, long(n));
    m_vector.insert(m_vector.begin() + index, item);
}

template <typename T, typename Alloc>
void List<T, Alloc>::insert(long index, const List<T, Alloc>& other)
{
    size_type n = size();
    if (index < 0)
    {
        index += n;
        index = std::max(long(0), index);
    }
    index = std::min(index, long(n));
    m_vector.insert(m_vector.begin() + index, other.begin(), other.end());
}

//method contains

template <typename T, typename Alloc>
bool List<T, Alloc>::contains(const T& item) const
{
    typename std::vector<T, Alloc>::const_iterator it;
    it = std::find(m_vector.begin(), m_vector.end(), item);
    return it != m_vector.end();
}

//method pop

template <typename T, typename Alloc>
T List<T, Alloc>::pop(long index) throw(IndexError)
{
    T item;
    if (size() == 0)
        THROW(IndexError, "pop from an empty list");
    if (index == -1)
    {
        item = m_vector.back();
        m_vector.pop_back();
    }
    else
    {
        if (index < 0)
            index += size();
        try
        {
            item = m_vector.at(index);
        }
        catch (std::out_of_range& e)
        {
            THROW(IndexError, "index out of range");
        }
        typename std::vector<T>::iterator it = m_vector.begin() + index;
        m_vector.erase(it);
    }
    return item;
}

//index method

template <typename T, typename Alloc>
typename List<T, Alloc>::size_type List<T, Alloc>::index(const T item) const throw(ValueError)
{
    typename std::vector<T, Alloc>::const_iterator it;
    it = std::find(m_vector.begin(), m_vector.end(), item);
    if (it == m_vector.end())
        THROW(ValueError, "value not in list");
    else
        return it - m_vector.begin();
}

//extend method

template <typename T, typename Alloc>
void List<T, Alloc>::extend(const List<T, Alloc>& other)
{
    m_vector.insert(m_vector.end(), 
                    other.m_vector.begin(), 
                    other.m_vector.end());
}

//operator+=

template <typename T, typename Alloc>
void List<T, Alloc>::operator+=(const List<T, Alloc>& other)
{
    m_vector.insert(m_vector.end(), 
                    other.m_vector.begin(), 
                    other.m_vector.end());
}

//operator+

template <typename T, typename Alloc>
List<T, Alloc> List<T, Alloc>::operator+(const List<T, Alloc>& other) const
{
    List<T, Alloc> copy(*this);
    copy.extend(other);
    return copy;
}

//remove method

template <typename T, typename Alloc>
void List<T, Alloc>::remove(const T& item) throw(ValueError)
{
    size_type i = index(item);
    typename std::vector<T>::iterator it = m_vector.begin() + i;
    m_vector.erase(it);
}

//count method

template <typename T, typename Alloc>
typename List<T, Alloc>::size_type List<T, Alloc>::count(const T& item) const
{
    return std::count(m_vector.begin(), m_vector.end(), item);
}

//reverse method

template <typename T, typename Alloc>
void List<T, Alloc>::reverse()
{
    std::reverse(m_vector.begin(), m_vector.end());
}

//sort method

template <typename T, typename Alloc>
void List<T, Alloc>::sort()
{
    std::sort(m_vector.begin(), m_vector.end());
}

template <typename T, typename Alloc>
void List<T, Alloc>::sort(bool (*funcptr)(const T&, const T&))
{
    std::sort(m_vector.begin(), m_vector.end(), funcptr);
}

template <typename T, typename Alloc>
template <typename Compare>
void List<T, Alloc>::sort(const Compare& functor)
{
    std::sort(m_vector.begin(), m_vector.end(), functor);
}

//forward iterators

template <typename T, typename Alloc>
typename List<T, Alloc>::iterator List<T, Alloc>::begin()
{
    return m_vector.begin();
}

template <typename T, typename Alloc>
typename List<T, Alloc>::const_iterator List<T, Alloc>::begin() const
{
    return m_vector.begin();
}

template <typename T, typename Alloc>
typename List<T, Alloc>::iterator List<T, Alloc>::end()
{
    return m_vector.end();
}

template <typename T, typename Alloc>
typename List<T, Alloc>::const_iterator List<T, Alloc>::end() const
{
    return m_vector.end();
}

//reverse iterators

template <typename T, typename Alloc>
typename List<T, Alloc>::reverse_iterator List<T, Alloc>::rbegin()
{
    return m_vector.rbegin();
}

template <typename T, typename Alloc>
typename List<T, Alloc>::const_reverse_iterator List<T, Alloc>::rbegin() const
{
    return m_vector.rbegin();
}

template <typename T, typename Alloc>
typename List<T, Alloc>::reverse_iterator List<T, Alloc>::rend()
{
    return m_vector.rend();
}

template <typename T, typename Alloc>
typename List<T, Alloc>::const_reverse_iterator List<T, Alloc>::rend() const
{
    return m_vector.rend();
}

// clear method

template <typename T, typename Alloc>
void List<T, Alloc>::clear()
{
    m_vector.erase(m_vector.begin(), m_vector.end());
}

//==============================================================================
// LISTITERATOR DECLARATION
//==============================================================================

/**
 * @brief Implements an iterator object for List
 * 
 * @tparam Container List type
 * 
 * This is an implementation of the Iterator design pattern
 */
template <typename Container>
class ListIterator: public Iterator<typename Container::value_type>
{
        
    public:
    
    /**
     * Constructor.
     * 
     * Build a list iterator from an existing list.
     * 
     * @param list list to be iterated over
     */
    ListIterator(Container& list): m_list(&list) { first(); };
    
    /**
     * Copy constructor.
     * 
     * Build a list iterator from an existing iterator.
     * 
     * @param other iterator to be copied
     */    
    ListIterator(const ListIterator& other): m_list(other.m_list), m_cursor(other.m_cursor) { };
    
    /**
     * Destructor.
     */
    virtual ~ListIterator() { };
    
    /**
     * Assignment operator.
     * 
     * @param other iterator to be assigned from.
     */
    ListIterator& operator=(const ListIterator& other) { m_cursor = other.m_current; m_list = other.m_list; return *this; };

    /**
     * Move iterator to the first item.
     */
    virtual void first() { m_cursor = m_list->begin(); };
    
    /**
     * Move iterator to the next item.
     */
    void next() { ++m_cursor; }
    
    /**
     * Stat whether iteration is over.
     */
    virtual bool isDone() { return m_cursor >= m_list->end(); };
    
    /**
     * Return current item.
     */
    virtual typename Container::value_type& currentItem() { return *m_cursor; };
    
    private:
        
    Container* m_list;
    typename Container::iterator m_cursor;

};

/**
 * @brief Implements an iterator object for List
 * 
 * @tparam Container List type
 * 
 * This is an implementation of the Iterator design pattern
 */
template <typename Container>
class ListIterator<const Container>: public Iterator<const typename Container::value_type>
{
        
    public:
    
    /**
     * Constructor.
     * 
     * Build a list iterator from an existing list.
     * 
     * @param list list to be iterated over
     */
    ListIterator(const Container& list): m_list(&list) { first(); };
    
    /**
     * Copy constructor.
     * 
     * Build a list iterator from an existing iterator.
     * 
     * @param other iterator to be copied
     */    
    ListIterator(const ListIterator& other): m_list(other.m_list), m_cursor(other.m_cursor) { };
    
    /**
     * Destructor.
     */
    virtual ~ListIterator() { };
    
    /**
     * Assignment operator.
     * 
     * @param other iterator to be assigned from.
     */
    ListIterator& operator=(const ListIterator& other) { m_cursor = other.m_current; m_list = other.m_list; return *this; };

    /**
     * Move iterator to the first item.
     */
    virtual void first() { m_cursor = m_list->begin(); };
    
    /**
     * Move iterator to the next item.
     */
    void next() { ++m_cursor; }
    
    /**
     * Stat whether iteration is over.
     */
    virtual bool isDone() { return m_cursor >= m_list->end(); };
    
    /**
     * Return current item.
     */
    virtual const typename Container::value_type& currentItem() { return *m_cursor; };
    
    private:
        
    const Container* m_list;
    typename Container::const_iterator m_cursor;

};

/**
 * @brief Implements a reverse iterator object for List
 * 
 * @tparam Container List type
 * 
 * This is an implementation of the Iterator design pattern
 */
template <typename Container>
class ReverseListIterator: public Iterator<typename Container::value_type>
{
        
    public:
    
    /**
     * Constructor.
     * 
     * Build a list iterator from an existing list.
     * 
     * @param list list to be iterated over
     */
    ReverseListIterator(Container& list): m_list(&list) { first(); };
    
    /**
     * Copy constructor.
     * 
     * Build a list iterator from an existing iterator.
     * 
     * @param other iterator to be copied
     */    
    ReverseListIterator(const ReverseListIterator& other): m_list(other.m_list), m_cursor(other.m_cursor) { };
    
    /**
     * Destructor.
     */
    virtual ~ReverseListIterator() { };
    
    /**
     * Assignment operator.
     * 
     * @param other iterator to be assigned from.
     */
    ReverseListIterator& operator=(const ReverseListIterator& other) { m_cursor = other.m_current; m_list = other.m_list; return *this; };

    /**
     * Move iterator to the first item.
     */
    virtual void first() { m_cursor = m_list->rbegin(); };
    
    /**
     * Move iterator to the next item.
     */
    void next() { ++m_cursor; }
    
    /**
     * Stat whether iteration is over.
     */
    virtual bool isDone() { return m_cursor >= m_list->rend(); };
    
    /**
     * Return current item.
     */
    virtual typename Container::value_type& currentItem() { return *m_cursor; };
    
    private:
        
    Container* m_list;
    typename Container::reverse_iterator m_cursor;

};

/**
 * @brief Implements a reverse iterator object for List
 * 
 * @tparam Container List type
 * 
 * This is an implementation of the Iterator design pattern
 */
template <typename Container>
class ReverseListIterator<const Container>: public Iterator<const typename Container::value_type>
{
        
    public:
    
    /**
     * Constructor.
     * 
     * Build a list iterator from an existing list.
     * 
     * @param list list to be iterated over
     */
    ReverseListIterator(const Container& list): m_list(&list) { first(); };
    
    /**
     * Copy constructor.
     * 
     * Build a list iterator from an existing iterator.
     * 
     * @param other iterator to be copied
     */    
    ReverseListIterator(const ReverseListIterator& other): m_list(other.m_list), m_cursor(other.m_cursor) { };
    
    /**
     * Destructor.
     */
    virtual ~ReverseListIterator() { };
    
    /**
     * Assignment operator.
     * 
     * @param other iterator to be assigned from.
     */
    ReverseListIterator& operator=(const ReverseListIterator& other) { m_cursor = other.m_current; m_list = other.m_list; return *this; };

    /**
     * Move iterator to the first item.
     */
    virtual void first() { m_cursor = m_list->rbegin(); };
    
    /**
     * Move iterator to the next item.
     */
    void next() { ++m_cursor; }
    
    /**
     * Stat whether iteration is over.
     */
    virtual bool isDone() { return m_cursor >= m_list->rend(); };
    
    /**
     * Return current item.
     */
    virtual const typename Container::value_type& currentItem() { return *m_cursor; };
    
    private:
        
    const Container* m_list;
    typename Container::const_reverse_iterator m_cursor;

};

} //end of snowball namespace

#endif
