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

#include "version.h"

namespace snowball
{

void showVersion()
{
    std::cout << "Snowball version " << version() << std::endl;
    std::cout << "Copyright (C) 2016 Cédric Campguilhem\n";
    std::cout << "This program comes with ABSOLUTELY NO WARRANTY\n";
    std::cout << "This is free software, and you are welcome to ";
    std::cout << "redistribute it under certain conditions.\n";
    std::cout << "See here: ";
    std::cout << "http://www.gnu.org/licenses/gpl-3.0-standalone.html\n";
}


std::string version()
{
    std::stringstream ss;
    ss << SNOWBALL_VERSION_MAJOR << ".";
    ss << SNOWBALL_VERSION_MINOR << ".";
    ss << SNOWBALL_VERSION_PATCH;
    return ss.str();
}


int majorVersion()
{
    return SNOWBALL_VERSION_MAJOR;
}


int minorVersion()
{
    return SNOWBALL_VERSION_MINOR;
}


int patchVersion()
{
    return SNOWBALL_VERSION_PATCH;
}

bool withBoostLocale()
{
#ifdef SNOWBALL_WITH_BOOST_LOCALE
    return true;
#else
    return false;
#endif
}

bool withBoostHash()
{
#ifdef SNOWBALL_WITH_BOOST_HASH
    return true;
#else
    return false;
#endif
}
} //end of namespace snowball
