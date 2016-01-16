#include "catch.hpp"

#include <limits>
#include <cstddef>
#include <iostream>

#include "collections/list.hpp"
#include "exceptions/exceptions.h"

using namespace snowball;


const int valueAt(const List<int>& list, int index)
{
    return list[index];
}


class Dummy
{
    private:
    int m_value;
    
    public:
    Dummy(int value): m_value(value) { };
};

bool sortInt(const int& i, const int& j)
{
    if ((3 - i) * (3 - i) == (3 - j) * (3 - j))
        return i < j;
    else
        return (3 - i) * (3 - i) < (3 - j) * (3 - j);
}


TEST_CASE("list", "[collections]")
{        
    SECTION("empty list constructor")
    {
        List<int> list;
        REQUIRE (list.size() == 0);
    }
    
    SECTION("initializer list constructor")
    {
        List<int> list = {0, 1, 2, 3, 4};
        REQUIRE (list.size() == 5);
    }
    
    SECTION("constructor with duplicated value")
    {
        List<int> list(4, 0);
        REQUIRE (list.size() == 4);
    }
    
    SECTION("construction from an existing vector")
    {
        std::vector<int> vect = {0, 1, 2};
        List<int> list(vect);
        REQUIRE (list.size() == 3);
    }
    
    SECTION("copy construction")
    {
        List<int> list1 = {0, 1, 2, 3, 4, 5};
        List<int> list2(list1);
        REQUIRE (list2.size() == 6);
        const List<int> list3 = {0, 1, 2, 3, 4, 5};
        List<int> list4(list3);
        REQUIRE (list4.size() == 6);
    }
    
    SECTION("assignment from another list")
    {
        List<int> list1 = {0, 1, 2, 3, 4, 5};
        List<int> list2(3, 0);
        list2 = list1;
        REQUIRE (list2.size() == 6);
    }
    
    SECTION("assignment from a vector")
    {
        std::vector<int> vect = {0, 1, 2, 3, 4, 5};
        List<int> list(3, 0);
        list = vect;
        REQUIRE (list.size() == 6);
    }
    
    SECTION("assignment from a initializer list")
    {
        List<int> list(3, 0);
        list = {0, 1};
        REQUIRE (list.size() == 2);
    }
    
    SECTION("operator[]")
    {
        List<int> list = {0, 1, 2, 3, 4, 5, 6};
        REQUIRE (list[0] == 0);
        REQUIRE (list[2] == 2);
        REQUIRE (list[-1] == 6);
        REQUIRE (list[-3] == 4);
        REQUIRE (list[-7] == 0);
        REQUIRE (valueAt(list, 2) == 2);
        REQUIRE (valueAt(list, -7) == 0);
        REQUIRE_THROWS_AS (valueAt(list, 7), IndexError);
        REQUIRE_THROWS_AS (valueAt(list, 8), IndexError);
        REQUIRE_THROWS_AS (list.operator[](7), IndexError);
        REQUIRE_THROWS_AS (list[-8], IndexError);
    }
    
    SECTION("operator==")
    {
        List<int> list1 = {1, 2, 3, 4};
        List<int> list2 = {1, 2, 3};
        List<int> list3 = {1, 2, 3};
        REQUIRE (!(list1 == list2));
        REQUIRE (list2 == list3);
    }
        
    SECTION("append")
    {
        List<int> list;
        for (int i = 0; i < 10; ++i)
        {
            list.append(i);
        }
        REQUIRE (list.size() == 10);
        REQUIRE (list[4] == 4);
    }
    
    SECTION("insert")
    {
        List<int> list = {0, 1, 2};
        list.insert(10, 3);
        REQUIRE (list == List<int>({0, 1, 2, 3}));
        list.insert(-10, 4);
        REQUIRE (list == List<int>({4, 0, 1, 2, 3}));
        list.insert(2, 5);
        REQUIRE (list == List<int>({4, 0, 5, 1, 2, 3}));
        list.insert(0, 6);
        REQUIRE (list == List<int>({6, 4, 0, 5, 1, 2, 3}));
        list.insert(-1, 7);
        REQUIRE (list == List<int>({6, 4, 0, 5, 1, 2, 7, 3}));
    }
    
    SECTION("contains")
    {
        List<int> list = {0, 1, 2};
        REQUIRE (!list.contains(3));
        REQUIRE (list.contains(0));
        REQUIRE (list.contains(2));
    }
    
    SECTION("contains")
    {
        List<int> list = {6, 4, 0, 5, 1, 2, 7, 3};
        int i;
        REQUIRE (list.size() == 8);
        i = list.pop();
        REQUIRE (list.size() == 7);
        REQUIRE (i == 3);
        i = list.pop(-3);
        REQUIRE (list.size() == 6);
        REQUIRE (i == 1);
        i = list.pop(0);
        REQUIRE (list.size() == 5);
        REQUIRE (i == 6);
        i = list.pop(2);
        REQUIRE (list.size() == 4);
        REQUIRE (i == 5);
    }
    
    SECTION("index")
    {
        List<int> list = {6, 4, 0, 5, 1, 2, 7, 3};
        List<int>::size_type i;
        i = list.index(4);
        REQUIRE (i == 1);
        REQUIRE (list.index(5) == 3);
        REQUIRE_THROWS_AS (list.index(10), ValueError);
    }

    SECTION("extend")
    {
        List<int> list1 = {0, 2, 4, 6, 8};
        List<int> list2 = {1, 3, 5, 7, 9};
        list1.extend(list2);
        REQUIRE (list1 == List<int>({0, 2, 4, 6, 8, 1, 3, 5, 7, 9}));
    }
    
    SECTION("operator+=")
    {
        List<int> list1 = {0, 2, 4, 6, 8};
        List<int> list2 = {1, 3, 5, 7, 9};
        list1 += list2;
        REQUIRE (list1 == List<int>({0, 2, 4, 6, 8, 1, 3, 5, 7, 9}));
    }
    
    SECTION("operator+")
    {
        List<int> list1 = {0, 2, 4, 6, 8};
        List<int> list2 = {1, 3, 5, 7, 9};
        List<int> list3 = list1 + list2;
        REQUIRE (list3 == List<int>({0, 2, 4, 6, 8, 1, 3, 5, 7, 9}));
    }
    
    SECTION("count")
    {
        List<int> list = {0, 1, 2, 4, 2, 1, 0, 2, 3, 1};
        REQUIRE (list.count(1) == 3);
        REQUIRE (list.count(5) == 0);
        REQUIRE (list.count(4) == 1);
    }
    
    SECTION("remove")
    {
        List<int> list = {6, 4, 0, 5, 1, 2, 7, 3};
        list.remove(4);
        REQUIRE (list.size() == 7);
        REQUIRE (list[1] == 0);
        list.remove(3);
        REQUIRE (list.size() == 6);
        REQUIRE (list[-1] == 7);
        REQUIRE_THROWS_AS (list.remove(3), ValueError);
    }
    
    SECTION("sort")
    {
        List<int> list = {6, 4, 0, 5, 1, 2, 7, 3};
        list.sort();
        REQUIRE (list == List<int>({0, 1, 2, 3, 4, 5, 6, 7}));
    }
    
    SECTION("sort with function")
    {
        List<int> list = {6, 4, 0, 5, 1, 2, 7, 3};
        list.sort(sortInt);
        REQUIRE (list == List<int>({3, 2, 4, 1, 5, 0, 6, 7}));
    }
    
    SECTION("reverse")
    {
        List<int> list = {6, 4, 0, 5, 1, 2, 7, 3};
        list.sort(sortInt);
        REQUIRE (list == List<int>({3, 2, 4, 1, 5, 0, 6, 7}));
        list.reverse();
        REQUIRE (list == List<int>({7, 6, 0, 5, 1, 4, 2, 3}));
    }

} //end of TEST_CASE
