#include "catch.hpp"

#include <functional>

#include "snowball/collections/list.hpp"
#include "snowball/collections/algorithms.hpp"

using namespace snowball;

bool isEven(const int& a)
{
    return a % 2 == 0;
}

bool isOdd(const int& a)
{
    return a % 2 > 0;
}

int dble(const int& a)
{
    return 2 * a;
}


TEST_CASE("min/max", "[algorithms]")
{
    SECTION("list max")
    {
        List<int> list = {0, 2, 5, 3, 2, 5, 9, 2, 1, 6};
        REQUIRE (max(list) == 9);
        max(list) = 0;
        REQUIRE (max(list) == 6);
    }
    
    SECTION("list min")
    {
        List<int> list = {0, 2, 5, 3, 2, 5, 9, 2, 1, 6};
        REQUIRE (min(list) == 0);
        min(list) = 9;
        REQUIRE (min(list) == 1);
    }
} //end of TEST_CASE


TEST_CASE("argmin/argmax", "[algorithms]")
{
    SECTION("list argmax")
    {
        List<int> list = {0, 2, 5, 3, 2, 5, 9, 2, 1, 6};
        REQUIRE (argmax(list) == 6);        
    }
    
    SECTION("list argmin")
    {
        List<int> list = {0, 2, 5, 3, 2, 5, 9, 2, 1, 6};
        REQUIRE (argmin(list) == 0);
    }

} //end of TEST_CASE


TEST_CASE("filter", "[algorithms]")
{
    
    class Dummy
    {
        public:
        Dummy() { };
        bool operator()(const int& a) const { return a % 2 > 0; };
    };
    
    SECTION("list and function pointer")
    {
        List<int> list = {0, 2, 5, 3, 2, 5, 9, 2, 1, 6};
        List<int> output;
        filter(list, isEven, output);
        REQUIRE (output == List<int>({0, 2, 2, 2, 6}));
    }

    SECTION("list and std::function")
    {
        List<int> list = {0, 2, 5, 3, 2, 5, 9, 2, 1, 6};
        List<int> output;
        filter(list, std::function<bool(const int&)>(isOdd), output);
        REQUIRE (output == List<int>({5, 3, 5, 9, 1}));
    }
    
    SECTION("list and functor")
    {
        List<int> list = {0, 2, 5, 3, 2, 5, 9, 2, 1, 6};
        List<int> output;
        Dummy dummy;
        filter(list, dummy, output);
        REQUIRE (output == List<int>({5, 3, 5, 9, 1}));
        output.clear();
        filter(list, std::function<bool(const int&)>(dummy), output);
        REQUIRE (output == List<int>({5, 3, 5, 9, 1}));
    }

} //end of TEST_CASE

TEST_CASE("map", "[algorithms]")
{
    SECTION("list with function pointer")
    {
        List<int> list = {0, 2, 5, 3, 2, 5, 9, 2, 1, 6};
        List<int> output;
        map(list, dble, output);
        REQUIRE (output == List<int>({0, 4, 10, 6, 4, 10, 18, 4, 2, 12}));
    }
    
    SECTION("list with functor")
    {
        List<int> list = {0, 2, 5, 3, 2, 5, 9, 2, 1, 6};
        List<int> output;
        map(list, std::function<int(const int&)>(dble), output);
        REQUIRE (output == List<int>({0, 4, 10, 6, 4, 10, 18, 4, 2, 12}));
    }
}