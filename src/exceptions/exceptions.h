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

#ifndef SNOWBALL_EXCEPTIONS_H
#define SNOWBALL_EXCEPTIONS_H

#include <string>
#include <iostream>
#include <exception>

/*
 * This Macro enables to throw exceptions and automatacilly provides the
 * __FILE__, __FUNCTION__, __LINE__ arguments
 * 
 */ 
#define THROW(Exception, msg) throw Exception(msg, __FILE__, \
                                              __FUNCTION__,  \
                                              __LINE__)

/**
 * @namespace snowball
 * @brief main namespace of snowball library
 */
namespace snowball
{

/**
 * Base class for exceptions.
 * Exception object stores file name, function name and line number in which 
 * exception has been thrown.
 */

class BaseException: public std::exception
{
    public:
    
    /**
     * Constructor (basic exception)
     *
     * @param msg exception message
     */
    BaseException(std::string msg);
    
    /**
     * Constructor (extended exception)
     *
     * @param msg exception message
     * @param func function name
     * @param filename file name
     * @param line lineno number
     */
    BaseException(std::string msg, std::string filename, std::string func, 
                  int lineno);
    
    /**
     * Destructor
     */
    virtual ~BaseException();
    
    /**
     * Get exception message.
     *
     * This function is expected to be overloaded by derived classes to provide
     * custom messages.
     * @return exception message
     */
    const std::string get_message() const;

    /**
     * Get function name in which exception has been thrown.
     * 
     * @return function name
     */
    const std::string get_function() const;
    
    /**
     * Get file name in which exception has been thrown.
     * 
     * @return file name
     */
    const std::string get_filename() const;
    
    /**
     * Get line number in which exception has been thrown.
     * 
     * @return line number
     */
    const int get_lineno() const;
    
    /**
     * Stat whether exception is extended (i.e. file name, function name and line
     * number has been provided).
     */
    const bool is_extended() const;
    
    private:
    
    std::string message;
    std::string function;
    std::string filename;
    int lineno;
};

/**
 * Generic Exception.
 * Any exception thrown by snowball is a instance of Exception class.
 */

class Exception: private BaseException
{
    public:
    
    /**
     * Constructor (basic exception)
     *
     * @param msg exception message
     */
    Exception(std::string msg);
    
    /**
     * Constructor (extended exception)
     * 
     * @param msg exception message
     * @param func function name
     * @param filename file name
     * @param lineno line number
     */
    Exception(std::string msg, std::string filename, std::string func, 
              int lineno);

    /**
     * Destructor
     */
    virtual ~Exception();
    
    /**
     * Return information (message plus file name, function name and line number
     * if available) on exception object.
     * @return exception message
    */
    virtual const char* what() const noexcept;
};


/**
 * IndexError exception.
 */

class IndexError: public Exception
{
    public:
    
    /**
     * Constructor (basic exception)
     * 
     * @param msg exception message
     */
    IndexError(std::string msg);
    
    /**
     * Constructor (extended exception)
     * 
     * @param msg exception message
     * @param func function name
     * @param filename file name
     * @param lineno line number
     */
    IndexError(std::string msg, std::string filename, std::string func, 
               int lineno);

    /**
     * Destructor
     */
    virtual ~IndexError();
};


/**
 * ValueError exception.
 */

class ValueError: public Exception
{
    public:
    
    /**
     * Constructor (basic exception)
     * 
     * @param msg exception message
     */
    ValueError(std::string msg);
    
    /**
     * Constructor (extended exception)
     * 
     * @param msg exception message
     * @param func function name
     * @param filename file name
     * @param lineno line number
     */
    ValueError(std::string msg, std::string filename, std::string func, 
               int lineno);
               
    /**
     * Destructor
     */
    virtual ~ValueError();
};

} //end of namespace snowball

#endif
