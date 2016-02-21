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

#ifndef SNOWBALL_DECORATORS_TIMEIT_HPP
#define SNOWBALL_DECORATORS_TIMEIT_HPP

#include <chrono>
#include <ctime>

#include "decorator.hpp"

namespace snowball
{
    
/**
 * Forward declaration of a timer decorator
 */
template <typename Signature>
class TimeIt;

/**
 * Time the execution of a callable object.
 * 
 * The callable object has the following signature:
 * 
 * Rtype(Args...)
 * 
 * The TimeIt has two ways of measuring elapsed time:
 * - wall clock time
 * - cpu time (the time spent by process in the callable)
 * 
 * Both can be returned respectively with wallTime and cpuTime functions.
 * 
 * @tparam Rtype return type of callable object
 * @tparam Args argument types of callable object
 */
template <typename Rtype, typename... Args>
class TimeIt<Rtype(Args...)>: public Decorator<Rtype(Args...)>
{
public:
    
    /**
     * Constructor
     * 
     * In addition to any callable object, you can specify how many times the 
     * callable is going to be invoked. On very fast callable, it is better to 
     * increase the number of repetitions in order to have a more accurate 
     * estimate of elapsed times. By default, the repetition number is set to 1.
     * 
     * @param callable callable object to be assessed
     * @param repeat number of repetitions 
     */
    TimeIt(typename Decorator<Rtype(Args...)>::Callable callable, 
           int repeat = 1)
        : Decorator<Rtype(Args...)>(callable), m_repeat(repeat) { };
        
    /**
     * Destructor
     */
    virtual ~TimeIt() { };
    
    /**
     * Return the wall clock time in milliseconds.
     */
    float wallTime() const { return m_wall; };
    
    /**
     * Return the CPU time in milliseconds.
     * 
     * This is the actual time spent by the process in the callable call.
     */
    float cpuTime() const { return m_cpu; };
    
private:
    
    /**
     * Decoration function
     */
    virtual Rtype decorate(Args... args)
    {
        Rtype out;
        auto w_start = std::chrono::high_resolution_clock::now();
        auto c_start = std::clock();
        for (int i = 0; i < m_repeat; ++i)
            out = Decorator<Rtype(Args...)>::doCall(args...);
        auto c_end = std::clock();
        auto w_end = std::chrono::high_resolution_clock::now();
        m_wall = std::chrono::duration<float, std::milli>(w_end-w_start).count()
            / float(m_repeat);
        m_cpu = (c_end - c_start) / float(m_repeat) * 1000. / CLOCKS_PER_SEC;
        return out;
    };
    
    /**
     * Attributes
     */
    int m_repeat;
    float m_wall;
    float m_cpu;
};

/**
 * Time the execution of a callable object.
 * 
 * The callable object has the following signature:
 * 
 * void(Args...)
 * 
 * The TimeIt has two ways of measuring elapsed time:
 * - wall clock time
 * - cpu time (the time spent by process in the callable)
 * 
 * Both can be returned respectively with wallTime and cpuTime functions.
 * 
 * @tparam Rtype return type of callable object
 * @tparam Args argument types of callable object
 */
template <typename... Args>
class TimeIt<void(Args...)>: public Decorator<void(Args...)>
{
public:
    
    /**
     * Constructor
     * 
     * In addition to any callable object, you can specify how many times the 
     * callable is going to be invoked. On very fast callable, it is better to 
     * increase the number of repetitions in order to have a more accurate 
     * estimate of elapsed times. By default, the repetition number is set to 1.
     * 
     * @param callable callable object to be assessed
     * @param repeat number of repetitions 
     */
    TimeIt(typename Decorator<void(Args...)>::Callable callable, int repeat = 1)
        : Decorator<void(Args...)>(callable), m_repeat(repeat) { };
        
    /**
     * Destructor
     */
    virtual ~TimeIt() { };

    /**
     * Return the wall clock time in milliseconds.
     */
    float wallTime() const { return m_wall; };
    
    /**
     * Return the CPU time in milliseconds.
     * 
     * This is the actual time spent by the process in the callable call.
     */
    float cpuTime() const { return m_cpu; };
    
private:
    
    /**
     * Decoration function
     */
    virtual void decorate(Args... args)
    {
        auto w_start = std::chrono::high_resolution_clock::now();
        auto c_start = std::clock();
        for (int i = 0; i < m_repeat; ++i)
            Decorator<void(Args...)>::doCall(args...);
        auto c_end = std::clock();
        auto w_end = std::chrono::high_resolution_clock::now();
        m_wall = std::chrono::duration<float, std::milli>(w_end-w_start).count()
            / float(m_repeat);
        m_cpu = (c_end - c_start) / float(m_repeat) * 1000. / CLOCKS_PER_SEC;
    };
    
    /**
     * Attributes
     */
    int m_repeat;
    float m_wall;
    float m_cpu;
};

} //end of snowball namespace

#endif