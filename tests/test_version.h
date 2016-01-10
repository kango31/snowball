#include <sstream>
#include <string>
#include "catch.hpp"

#include "version.h"

using namespace snowball;


TEST_CASE("versions", "[version]")
{    
    SECTION("version")
    {
        std::stringstream ss;
        ss << SNOWBALL_VERSION_MAJOR << ".";
        ss << SNOWBALL_VERSION_MINOR << ".";
        ss << SNOWBALL_VERSION_PATCH;
        REQUIRE (version() == ss.str());
    }
    
    SECTION("majorVersion")
    {
        REQUIRE (majorVersion() == SNOWBALL_VERSION_MAJOR);
    }

    SECTION("minorVersion")
    {
        REQUIRE (minorVersion() == SNOWBALL_VERSION_MINOR);
    }
    
    SECTION("patchVersion")
    {
        REQUIRE (patchVersion() == SNOWBALL_VERSION_PATCH);
    }
    
} //end of TEST_CASE
