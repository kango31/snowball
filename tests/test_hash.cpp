#include "catch.hpp"

#include <functional>
#include <string>
#include <iostream>

#include <boost/functional/hash.hpp>


#include "snowball/collections/hash.hpp"

using namespace snowball;
using namespace std;


struct Dummy
{
    Dummy(int a, int b): a(a), b(b) { };
    int a;
    int b;
};

size_t hash_value(const Dummy& d)
{
    size_t seed = 0;
    boost::hash_combine(seed, d.a);
    boost::hash_combine(seed, d.b);
    return seed;
};


TEST_CASE("hash", "[collections]")
{
        
    SECTION("Default hash")
    {
        Dummy dum1(0, 0);
        Dummy dum2(0, 0);
        Dummy dum3(0, 1);
        Hash<Dummy> hasher;
        REQUIRE (hasher(dum1) == hasher(dum2));
        REQUIRE (hasher(dum1) != hasher(dum3));
        REQUIRE (hasher(dum3) == hasher(dum3));
    }
    
    SECTION("Specialized Hash")
    {
        REQUIRE (Hash<int>()(123) == std::hash<int>()(123));
        REQUIRE (Hash<long>()(45678999) == std::hash<long>()(45678999));
        REQUIRE (Hash<std::string>()(std::string("Hello World !")) == 
            std::hash<std::string>()(std::string("Hello World !")));
    }
    
    SECTION("boost hash")
    {
        boost::hash<int> int_hasher;
        int a = 3;
        size_t seed = int_hasher(a);
        cout << seed << endl;
        boost::hash<int*> pint_hasher;
        int* b = &a;
        int c = 3;
        int* d = &c;
        cout << pint_hasher(b) << " " << pint_hasher(d) << endl;
        cout << int_hasher(a) << " " << int_hasher(c) << endl;
        boost::hash<Dummy> dummy_hasher;
        Dummy dum1(0, 0);
        cout << dummy_hasher(dum1) << endl;
        Dummy dum2(0, 0);
        cout << dummy_hasher(dum2) << endl;
    }
}

