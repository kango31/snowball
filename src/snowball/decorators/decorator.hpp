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

#ifndef SNOWBALL_DECORATORS_DECORATOR_HPP
#define SNOWBALL_DECORATORS_DECORATOR_HPP

#include <functional>


namespace snowball
{
    
/**
 * Forward declaration for Decorator class.
 * Purpose of Decorate is to decorate a callable object which signature is 
 * provided as template parameter. Decorate in this context means that behavior
 * may be added *before* and *after* the call to callable object.
 *
 * @tparam Signature signature of callable object
 */
template <typename Signature>
class Decorator;

/**
 * Implementation of a decorator for any callable object (function pointer, 
 * functor, lambda, member function...). This wide variety of callable object 
 * is the direct consequence of using std::function internally to store the 
 * callable object.
 * 
 * The callable object is returning a Rtype value while taking a variable 
 * number of parameters of any type. The any number of argument is handled by 
 * a variadic template.
 * 
 * The Decorator class is a functor implemented with a non-virtual interface.
 * The operator() is non-virtual and public. The logic of calling the callable
 * object is let to virtual private method that can be overloaded in derived 
 * class. This Decorator class is then a do-nothing decoration.
 * 
 * The private method to re-implement in derived class is decorate.
 * 
 * @tparam Rtype return type of callable object.
 * @tparam Args callable argument types
 */
template <typename Rtype, typename ...Args>
class Decorator<Rtype(Args...)>
{
public:
        
    /**
     * @typedef Callable
     * Type of stored callable object
     */
    typedef typename std::function<Rtype(Args...)> Callable;
    
    /**
     * Constructor
     * 
     * @param callable callable object
     */
    Decorator(Callable callable): m_callable(callable) { };
    
    /**
     * Destructor
     */
    virtual ~Decorator() { };
    
    /**
     * operator()
     * 
     * Run the underlying callable while decorating him.
     * This non-virtual method is not designed to be re-implemented in derived 
     * class. Re-implement decorate method instead.
     *
     * @param args callable arguments
     */
    Rtype operator()(Args... args)
    { 
        return decorate(args...);
    };
    
protected:
    
    /**
     * Encapsulate the call to underlying callable object.
     * 
     * @param args callable arguments
     */
    Rtype doCall(Args... args) const
    {
       return m_callable(args...); 
    };
    
private:
    
   /**
    * Decorate underlying callable object.
    * 
    * This method shall be re-implemented in derived classes.
    * 
    * @param args callable arguments
    */
    virtual Rtype decorate(Args... args)
    {
        return doCall(args...);
    };
   
private:
    
    /**
     * Attributes
     */
    Callable m_callable;
};

/**
 * Implementation of a decorator for any callable object (function pointer, 
 * functor, lambda, member function...). This wide variety of callable object 
 * is the direct consequence of using std::function internally to store the 
 * callable object.
 * 
 * The callable object is returning void while taking a variable 
 * number of parameters of any type. The any number of argument is handled by 
 * a variadic template.
 * 
 * The Decorator class is a functor implemented with a non-virtual interface.
 * The operator() is non-virtual and public. The logic of calling the callable
 * object is let to virtual private method that can be overloaded in derived 
 * class. This Decorator class is then a do-nothing decoration.
 * 
 * The private method to re-implement in derived class is decorate.
 * 
 * @tparam Args callable argument types
 */
template <typename ...Args>
class Decorator<void(Args...)>
{
public:
        
    /**
     * @typedef Callable
     * Type of stored callable object
     */
    typedef typename std::function<void(Args...)> Callable;
    
    /**
     * Constructor
     * 
     * @param callable callable object
     */
    Decorator(Callable callable): m_callable(callable) { };

    /**
     * Destructor
     */
    virtual ~Decorator() { };
    
    /**
     * operator()
     * 
     * Run the underlying callable while decorating him.
     * This non-virtual method is not designed to be re-implemented in derived 
     * class. Re-implement decorate method instead.
     *
     * @param args callable arguments
     */
    void operator()(Args... args)
    { 
        decorate(args...);
    };
    
protected:
    
    /**
     * Encapsulate the call to underlying callable object.
     * 
     * @param args callable arguments
     */
    void doCall(Args... args) const
    {
       m_callable(args...); 
    };
    
private:
    
   /**
    * Decorate underlying callable object.
    * 
    * This method shall be re-implemented in derived classes.
    * 
    * @param args callable arguments
    */
    virtual void decorate(Args... args)
    {
        doCall(args...);
    };
   
private:
    
    /**
     * Attributes
     */
    Callable m_callable;
};

    
} //end of namespace snowball

#endif
