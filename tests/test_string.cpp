#include "catch.hpp"

#include <iostream>
#include <sstream>
#include <cmath>

#include "snowball/collections/string.h"
#include "snowball/version.h"

using namespace snowball;


TEST_CASE("string", "[collections]")
{
    
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
        REQUIRE (test1 == "Hello World!");
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
    
    SECTION("endswith")
    {
        String test1("Hello World!");
        String test2(" World!");
        String test3("World !");
        std::string str1("d!");
        std::string str2("ld !");
        REQUIRE (test1.endswith(test2));
        REQUIRE (!test1.endswith(test3));
        REQUIRE (test1.endswith(str1));
        REQUIRE (!test1.endswith(str2));
        REQUIRE (test1.endswith("rld!"));
        REQUIRE (!test1.endswith(" Hello"));
        REQUIRE (test1.endswith('!'));
        REQUIRE (!test1.endswith('?'));
    }
    
    SECTION("split with space characters")
    {
        String test1("Hello World!\nYour name is:\tHAL");
        String test2("It's raining cats and dogs today !");
        String test3("I have    so\r\rmany    spaces    !\t\t! !!\n \t \r  !");
        List<String> fields;
        List<String> expected;
        fields = test1.split();
        expected = {"Hello", "World!", "Your", "name", "is:", "HAL"};
        REQUIRE (fields == expected);
        fields = test2.split();
        expected = {"It's", "raining", "cats", "and", "dogs", "today", "!"};
        REQUIRE (fields == expected);
        fields = test3.split();
        expected = {"I", "have", "so", "many", "spaces", "!", "!", "!!", "!"};
        REQUIRE (fields == expected);
    }
    
    SECTION("split with any characters")
    {
        String test("It's raining cats and dogs today !");
        String empty;
        List<String> fields;
        List<String> expected;
        fields = test.split('\'');
        expected = {"It", "s raining cats and dogs today !"};
        REQUIRE (fields == expected);
        fields = test.split("aeiouy");
        expected = {"It's r", "n", "ng c", "ts ", "nd d", "gs t", "d", " !"};
        REQUIRE (fields == expected);
        fields = test.split(std::string("aeiouy"));
        REQUIRE (fields == expected);
        fields = test.split(String("g"));
        expected = {"It's rainin", " cats and do", "s today !"};
        REQUIRE (fields == expected);
        fields = empty.split(';');
        expected = {""};
        REQUIRE (fields == expected);
    }
    
    SECTION("operator!=")
    {
        String test1("Hello World!");
        String test2("How are you ?");
        REQUIRE (test1 != test2);
        REQUIRE (test1 != std::string("Hello"));
        char cstr[] = "Hello World!";
        REQUIRE (!(test1 != cstr));
    }
    
    SECTION("operator<<")
    {
        std::stringstream ss;
        String test("It's raining cats and dogs today !");
        ss << test;
        REQUIRE (ss.str() == "It's raining cats and dogs today !");
    }
    
    SECTION("lstrip")
    {
        String test1("\t\t\t  Hello World !\r\n");
        REQUIRE (test1.lstrip() == "Hello World !\r\n");
        String test2("oiseau bleu");
        REQUIRE (test2.lstrip("aeiouy") == "seau bleu");
        String test3("mississipi");
        REQUIRE (test3.lstrip(std::string("sim")) == "pi");
        String test4("aaaaaaaaaaaaaahhhhh!!!");
        REQUIRE (test4.lstrip('a') == "hhhhh!!!");
        String test5("mississipi");
        REQUIRE (test5.lstrip(String("sim")) == "pi");        
    }
    
    SECTION("lstrip with const String")
    {
        const String test1("\t\t\t  Hello World !\r\n");
        REQUIRE (test1.lstrip() == "Hello World !\r\n");
        const String test2("oiseau bleu");
        REQUIRE (test2.lstrip("aeiouy") == "seau bleu");
        const String test3("mississipi");
        REQUIRE (test3.lstrip(std::string("sim")) == "pi");
        const String test4("aaaaaaaaaaaaaahhhhh!!!");
        REQUIRE (test4.lstrip('a') == "hhhhh!!!");
        const String test5("mississipi");
        REQUIRE (test5.lstrip(String("sim")) == "pi");        
    }
    
    SECTION("rstrip")
    {
        String test1("\t\t\t  Hello World !\r\n");
        REQUIRE (test1.rstrip() == "\t\t\t  Hello World !");
        String test2("oiseau bleu");
        REQUIRE (test2.rstrip("aeiouy") == "oiseau bl");
        String test3("mississipi");
        REQUIRE (test3.rstrip(std::string("sim")) == "mississip");
        String test4("aaaaaaaaaaaaaahhhhh!!!");
        REQUIRE (test4.rstrip('!') == "aaaaaaaaaaaaaahhhhh");
        String test5("mississipi");
        REQUIRE (test5.rstrip(String("sim")) == "mississip");        
    }
    
    SECTION("rstrip with const String")
    {
        const String test1("\t\t\t  Hello World !\r\n");
        REQUIRE (test1.rstrip() == "\t\t\t  Hello World !");
        const String test2("oiseau bleu");
        REQUIRE (test2.rstrip("aeiouy") == "oiseau bl");
        const String test3("mississipi");
        REQUIRE (test3.rstrip(std::string("sim")) == "mississip");
        const String test4("aaaaaaaaaaaaaahhhhh!!!");
        REQUIRE (test4.rstrip('!') == "aaaaaaaaaaaaaahhhhh");
        const String test5("mississipi");
        REQUIRE (test5.rstrip(String("sim")) == "mississip");        
    }
    
    SECTION("strip")
    {
        String test1("\t\t\t  Hello World !\r\n");
        REQUIRE (test1.strip() == "Hello World !");
        String test2("oiseau bleu");
        REQUIRE (test2.strip("aeiouy") == "seau bl");
        String test3("mississipi");
        REQUIRE (test3.strip(std::string("sim")) == "p");
        String test4("aaaaaaaaaaaaaahhhhh!!!");
        REQUIRE (test4.strip('!') == "aaaaaaaaaaaaaahhhhh");
        String test5("mississipi");
        REQUIRE (test5.strip(String("sim")) == "p");        
    }
    
    SECTION("strip with const String")
    {
        const String test1("\t\t\t  Hello World !\r\n");
        REQUIRE (test1.strip() == "Hello World !");
        const String test2("oiseau bleu");
        REQUIRE (test2.strip("aeiouy") == "seau bl");
        const String test3("mississipi");
        REQUIRE (test3.strip(std::string("sim")) == "p");
        const String test4("aaaaaaaaaaaaaahhhhh!!!");
        REQUIRE (test4.strip('!') == "aaaaaaaaaaaaaahhhhh");
        const String test5("mississipi");
        REQUIRE (test5.strip(String("sim")) == "p");        
    }
    
    SECTION("toInt")
    {
        String test1("12345");
        String test2("-678 ");
        String test3("3 words");
        String test4("");
        String test5("11");
        REQUIRE (test1.toInt() == 12345);
        REQUIRE (test2.toInt() == -678);
        REQUIRE_THROWS_AS (test3.toInt(), ValueError);
        REQUIRE_THROWS_AS (test4.toInt(), ValueError);
        REQUIRE (test5.toInt(2) == 3);
    }
    
    SECTION("toFloat")
    {
        String test1("3.11  ");
        String test2("3.11  !");
        String test3(".1234");
        String test4("-1.2345E+06");
        String test5("-1.2345e+06");
        REQUIRE (std::abs(test1.toFloat() - 3.11) < 1.E-6);
        REQUIRE_THROWS_AS(test2.toFloat(), ValueError);
        REQUIRE (std::abs(test3.toFloat() - 0.1234) < 1.E-6);
        REQUIRE (std::abs(test4.toFloat() + 1.2345E+6) < 1.E-6);
        REQUIRE (std::abs(test5.toFloat() + 1.2345e+6) < 1.E-6);
    }
    
    SECTION("toDouble")
    {
        String test1("3.11  ");
        String test2("3.11  !");
        String test3(".1234");
        String test4("-1.2345E+06");
        String test5("-1.2345e+06");
        REQUIRE (std::abs(test1.toDouble() - 3.11) < 1.E-6);
        REQUIRE_THROWS_AS(test2.toDouble(), ValueError);
        REQUIRE (std::abs(test3.toDouble() - 0.1234) < 1.E-6);
        REQUIRE (std::abs(test4.toDouble() + 1.2345E+6) < 1.E-6);
        REQUIRE (std::abs(test5.toDouble() + 1.2345e+6) < 1.E-6);
    }
    
    SECTION("toBool")
    {
        String test1("1");
        String test2("0");
        String test3("-1");
        REQUIRE (test1.toBool());
        REQUIRE (!test2.toBool());
        REQUIRE (test3.toBool());
    }
    
    SECTION("STL string conversion")
    {
        String test1("Hello World!");
        std::string test2(test1);
        REQUIRE (test2 == "Hello World!");
    }
    
    SECTION("upper")
    {
        String test1("Hello 123 WorlD !!");
        REQUIRE (test1.upper() == "HELLO 123 WORLD !!");
        String test2("Cédric");
        if (withBoostLocale())
        {
            REQUIRE (test2.upper() == "CÉDRIC");
            REQUIRE (test2.upper() == "C\u00C9DRIC");
        }
        else
            REQUIRE (test2.upper() == "CéDRIC");
        const String test3(test1);
        REQUIRE (test3.upper() == "HELLO 123 WORLD !!");
    }
    
    SECTION("lower")
    {
        String test1("Hello 123 WorlD !!");
        REQUIRE (test1.lower() == "hello 123 world !!");
        String test2("Cédric");
        REQUIRE (test2.lower() == "cédric");
        const String test3(test1);
        REQUIRE (test3.lower() == "hello 123 world !!");
    }

}