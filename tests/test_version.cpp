#include <sstream>
#include <string>
#include "catch.hpp"

#include "snowball/version.h"

using namespace snowball;


TEST_CASE("version", "[version]")
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
    
    SECTION("withBoostLocale")
    {
#ifdef SNOWBALL_WITH_BOOST_LOCALE
        REQUIRE(withBoostLocale());
#else
        REQUIRE(!withBoostLocale());
#endif
    }
    
    SECTION("withBoostHash")
    {
#ifdef SNOWBALL_WITH_BOOST_HASH
        REQUIRE(withBoostHash());
#else
        REQUIRE(!withBoostHash());
#endif        
    }
    
} //end of TEST_CASE
