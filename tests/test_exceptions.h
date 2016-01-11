#include <sstream>
#include "catch.hpp"

#include "exceptions/exceptions.h"

using namespace snowball;


void throwBaseException()
{
    THROW(BaseException, "this is a test exception");
}


void throwException()
{
    THROW(Exception, "this is an exception");
}


void throwIndexError()
{
    THROW(IndexError, "this is an index error");
}


void throwValueError()
{
    THROW(ValueError, "this is a value error");
}


TEST_CASE("exceptions", "[exceptions]")
{    
    SECTION("check base class")
    {
        try
        {
            throwBaseException();
        }
        catch (const BaseException& e)
        {
            REQUIRE (e.get_lineno() == 11);
            REQUIRE (e.get_filename() == __FILE__);
            REQUIRE (e.get_function() == "throwBaseException");
            REQUIRE (e.get_message() == "this is a test exception");
        }
    }
    
    SECTION("generic exception")
    {
        REQUIRE_THROWS_AS(throwException(), Exception);
    }
    
    SECTION("index error")
    {
        REQUIRE_THROWS_AS(throwIndexError(), IndexError);
    }

    SECTION("value error")
    {
        REQUIRE_THROWS_AS(throwValueError(), ValueError);
    }

} //end of TEST_CASE
