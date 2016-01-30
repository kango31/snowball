#include "catch.hpp"

#include <iostream>

#include "snowball/collections/string.h"

using namespace snowball;


TEST_CASE("string", "[collections]")
{
    
    class Dummy
    {
        public:
        Dummy(int a): m_a(a) { };
        
        private:
        int m_a;
    };
    
    SECTION("empty constructor")
    {
        String test;
        REQUIRE (test.size() == 0);
    }
    
    SECTION("constructor from C string")
    {
        String test("Hello World!");
        REQUIRE (test.size() == 12);
    }

    SECTION("constructor from std::string")
    {
        std::string test1("Hello World!");
        String test2(test1);
        REQUIRE (test2.size() == 12);
    }
    
    SECTION("constructor by duplication of a single character")
    {
        String test(10, '=');
        REQUIRE (test.size() == 10);
    }
    
    SECTION("copy constructor")
    {
        String test1(10, '=');
        String test2(test1);
        REQUIRE (test2.size() == 10);
    }
    
    SECTION("assignment operator")
    {
        String test1;
        test1 = std::string("Hello world!");
        REQUIRE (test1.size() == 12);
        test1 = String(10, '=');
        REQUIRE (test1.size() == 10);
        test1 = "hi!";
        REQUIRE (test1.size() == 3);
    }
    
    SECTION("operator==")
    {
        String test1("Hello World!");
        String test2(test1);
        REQUIRE (test1 == test2);
        REQUIRE (test1 == std::string("Hello World!"));
        char cstr[] = "Hello World!";
        REQUIRE (test1 == cstr);
    }
    
    SECTION("contains")
    {
        String test1("Hello World!");
        String test2("Hell");
        String test3("Hi");
        std::string str1("World");
        std::string str2("Earth");
        REQUIRE (test1.contains(test2));
        REQUIRE (!test1.contains(test3));
        REQUIRE (test1.contains(str1));
        REQUIRE (!test1.contains(str2));
        REQUIRE (test1.contains("ll"));
        REQUIRE (test1.contains("!"));
        REQUIRE (!test1.contains("?"));
        REQUIRE (test1.contains('!'));
        REQUIRE (!test1.contains('?'));
    }
    
    SECTION("startswith")
    {
        String test1("Hello World!");
        String test2("Hell");
        String test3("Hi");
        std::string str1("World");
        std::string str2("Earth");
        REQUIRE (test1.startswith(test2));
        REQUIRE (!test1.startswith(test3));
        REQUIRE (!test1.startswith(str1));
        REQUIRE (!test1.startswith(str2));
        REQUIRE (test1.startswith("Hello "));
        REQUIRE (!test1.startswith(" Hello"));
        REQUIRE (test1.startswith('H'));
        REQUIRE (!test1.startswith('?'));
    }
}