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

#ifndef SNOWBALL_VERSION_H
#define SNOWBALL_VERSION_H

#include <iostream>
#include <string>
#include <sstream>

/*
The following macros are defined from CMake
*/

//#define SNOWBALL_VERSION_MAJOR @SNOWBALL_VERSION_MAJOR@
//#define SNOWBALL_VERSION_MINOR @SNOWBALL_VERSION_MINOR@
//#define SNOWBALL_VERSION_PATCH @SNOWBALL_VERSION_PATCH@

/**
 * @namespace snowball
 * @brief main namespace of snowball library
 */
namespace snowball
{

/**
 * Display the version number.
 */
void showVersion();

/**
 * Return a string containing the version.
 */
std::string version();

/**
 * Return the major version number.
 */
int majorVersion();

/**
 * Return the minor version number.
 */
int minorVersion();

/**
 * Return the patch version number.
 */
int patchVersion();

/**
 * State whether snowball is compiled with Boost.Locale
 */
bool withBoostLocale();

/**
 * State whether snowball is compiled with Boost Functional/Hash
 */
bool withBoostHash();

} //namespace snowball

#endif

