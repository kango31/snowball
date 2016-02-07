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
    
    SECTION("constructor from char")
    {
        String test('A');
        REQUIRE (test == "A");
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
    
    SECTION("startsWith")
    {
        String test1("Hello World!");
        String test2("Hell");
        String test3("Hi");
        std::string str1("World");
        std::string str2("Earth");
        REQUIRE (test1.startsWith(test2));
        REQUIRE (!test1.startsWith(test3));
        REQUIRE (!test1.startsWith(str1));
        REQUIRE (!test1.startsWith(str2));
        REQUIRE (test1.startsWith("Hello "));
        REQUIRE (!test1.startsWith(" Hello"));
        REQUIRE (test1.startsWith('H'));
        REQUIRE (!test1.startsWith('?'));
    }
    
    SECTION("endswith")
    {
        String test1("Hello World!");
        String test2(" World!");
        String test3("World !");
        std::string str1("d!");
        std::string str2("ld !");
        REQUIRE (test1.endsWith(test2));
        REQUIRE (!test1.endsWith(test3));
        REQUIRE (test1.endsWith(str1));
        REQUIRE (!test1.endsWith(str2));
        REQUIRE (test1.endsWith("rld!"));
        REQUIRE (!test1.endsWith(" Hello"));
        REQUIRE (test1.endsWith('!'));
        REQUIRE (!test1.endsWith('?'));
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
    
    SECTION("operator>>")
    {
        String test;
        std::stringstream ss;
        ss.str("Hello!");
        ss >> test;
        REQUIRE (test == "Hello!");
    }
    
    SECTION("leftStrip")
    {
        String test1("\t\t\t  Hello World !\r\n");
        REQUIRE (test1.leftStrip() == "Hello World !\r\n");
        String test2("oiseau bleu");
        REQUIRE (test2.leftStrip("aeiouy") == "seau bleu");
        String test3("mississipi");
        REQUIRE (test3.leftStrip(std::string("sim")) == "pi");
        String test4("aaaaaaaaaaaaaahhhhh!!!");
        REQUIRE (test4.leftStrip('a') == "hhhhh!!!");
        String test5("mississipi");
        REQUIRE (test5.leftStrip(String("sim")) == "pi");        
    }
    
    SECTION("leftStrip with const String")
    {
        const String test1("\t\t\t  Hello World !\r\n");
        REQUIRE (test1.leftStrip() == "Hello World !\r\n");
        const String test2("oiseau bleu");
        REQUIRE (test2.leftStrip("aeiouy") == "seau bleu");
        const String test3("mississipi");
        REQUIRE (test3.leftStrip(std::string("sim")) == "pi");
        const String test4("aaaaaaaaaaaaaahhhhh!!!");
        REQUIRE (test4.leftStrip('a') == "hhhhh!!!");
        const String test5("mississipi");
        REQUIRE (test5.leftStrip(String("sim")) == "pi");        
    }
    
    SECTION("rightStrip")
    {
        String test1("\t\t\t  Hello World !\r\n");
        REQUIRE (test1.rightStrip() == "\t\t\t  Hello World !");
        String test2("oiseau bleu");
        REQUIRE (test2.rightStrip("aeiouy") == "oiseau bl");
        String test3("mississipi");
        REQUIRE (test3.rightStrip(std::string("sim")) == "mississip");
        String test4("aaaaaaaaaaaaaahhhhh!!!");
        REQUIRE (test4.rightStrip('!') == "aaaaaaaaaaaaaahhhhh");
        String test5("mississipi");
        REQUIRE (test5.rightStrip(String("sim")) == "mississip");        
    }
    
    SECTION("rightStrip with const String")
    {
        const String test1("\t\t\t  Hello World !\r\n");
        REQUIRE (test1.rightStrip() == "\t\t\t  Hello World !");
        const String test2("oiseau bleu");
        REQUIRE (test2.rightStrip("aeiouy") == "oiseau bl");
        const String test3("mississipi");
        REQUIRE (test3.rightStrip(std::string("sim")) == "mississip");
        const String test4("aaaaaaaaaaaaaahhhhh!!!");
        REQUIRE (test4.rightStrip('!') == "aaaaaaaaaaaaaahhhhh");
        const String test5("mississipi");
        REQUIRE (test5.rightStrip(String("sim")) == "mississip");        
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
    
    SECTION("cast to std::string")
    {
        String test("la même sensation de déjà vu");
        std::string output1(test);
        REQUIRE (output1 == "la même sensation de déjà vu");
        std::string output2 = static_cast<std::string>(test);
        REQUIRE (output2 == "la même sensation de déjà vu");
    }
    
    SECTION("getline")
    {
        std::stringstream ss;
        ss.str("hello; world; 123;");
        String test;
        getline(ss, test);
        REQUIRE (test == "hello; world; 123;");
    }
    
    SECTION("getline with delimiter")
    {
        std::stringstream ss;
        ss.str("hello; world; 123;");
        String test;
        getline(ss, test, ';');
        REQUIRE (test == "hello");
    }
    
    SECTION("forward iterator")
    {
        String test1("Hello");
        const String test2("World");
        std::vector<char> vect1 = {'H', 'e', 'l', 'l', 'o'};
        std::vector<char> vect2 = {'W', 'o', 'r', 'l', 'd'};
        String::iterator it1;
        String::const_iterator it2;
        std::vector<char>::iterator it = vect1.begin();
        for (it1 = test1.begin(); it1 != test1.end(); ++it1)
        {
            REQUIRE (*it1 == *it);
            ++it;
        }
        it = vect2.begin();
        for (it2 = test2.begin(); it2 != test2.end(); ++it2)
        {
            REQUIRE (*it2 == *it);
            ++it;
        }
    }

    SECTION("reverse iterator")
    {
        String test1("Hello");
        const String test2("World");
        std::vector<char> vect1 = {'o', 'l', 'l', 'e', 'H'};
        std::vector<char> vect2 = {'d', 'l', 'r', 'o', 'W'};
        String::reverse_iterator it1;
        String::const_reverse_iterator it2;
        std::vector<char>::iterator it = vect1.begin();
        for (it1 = test1.rbegin(); it1 != test1.rend(); ++it1)
        {
            REQUIRE (*it1 == *it);
            ++it;
        }
        it = vect2.begin();
        for (it2 = test2.rbegin(); it2 != test2.rend(); ++it2)
        {
            REQUIRE (*it2 == *it);
            ++it;
        }
    }
    
    SECTION("comparison operators with strings")
    {
        String test1("Aircraft");
        String test2("Bee");
        String test3("Crow");
        String test4("Duck");
        REQUIRE (test1 < test2);
        REQUIRE (test2 <= test2);
        REQUIRE (test2 <= test3);
        REQUIRE (test4 > test3);
        REQUIRE (test4 >= test3);
        REQUIRE (test4 >= test4);
    }

    SECTION("comparison operators with C strings")
    {
        String test1("Aircraft");
        String test2("Bee");
        String test3("Crow");
        String test4("Duck");
        REQUIRE (test1 < "Bee");
        REQUIRE (test2 <= "Bee");
        REQUIRE (test2 <= "Crow");
        REQUIRE (test4 > "Crow");
        REQUIRE (test4 >= "Crow");
        REQUIRE (test3 >= "Crow");
    }

    SECTION("comparison operators with C strings")
    {
        String test1("Aircraft");
        String test2("Bee");
        String test3("Crow");
        String test4("Duck");
        REQUIRE (test1 < std::string("Bee"));
        REQUIRE (test2 <= std::string("Bee"));
        REQUIRE (test2 <= std::string("Crow"));
        REQUIRE (test4 > std::string("Crow"));
        REQUIRE (test4 >= std::string("Crow"));
        REQUIRE (test3 >= std::string("Crow"));
    }
}