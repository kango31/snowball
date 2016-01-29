#include "catch.hpp"

#include <limits>
#include <cstddef>
#include <iostream>
#include <functional>

#include "snowball/collections/list.hpp"
#include "snowball/exceptions/exceptions.h"

using namespace snowball;


const int valueAt(const List<int>& list, int index)
{
    return list[index];
}

bool sortInt(const int& i, const int& j)
{
    if ((3 - i) * (3 - i) == (3 - j) * (3 - j))
        return i < j;
    else
        return (3 - i) * (3 - i) < (3 - j) * (3 - j);
}


TEST_CASE("list", "[collections]")
{ 

    class Dummy
    {
        private:
        int m_value;
        
        public:
        Dummy(int value): m_value(value) { };
        bool operator<(const Dummy& other) const { return m_value < other.m_value; };
        int value() const { return m_value; };
    };

    class Comp
    {
        public:
        Comp() { };
        bool compare(const int& i, const int& j) const { return i < j; };
        bool operator()(const int& i, const int& j) const { return i < j; };
    };

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
    
    SECTION("insert an item")
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
    
    SECTION("insert another list")
    {
        List<int> list = {0, 1, 2};
        list.insert(1, List<int>({3, 4, 5}));
        REQUIRE (list == List<int>({0, 3, 4, 5, 1, 2}));
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
        List<int> list = {6, 4, 4, 0, 5, 1, 2, 7, 3};
        list.remove(4);
        REQUIRE (list.size() == 8);
        REQUIRE (list[2] == 0);
        list.remove(3);
        REQUIRE (list.size() == 7);
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
    
    SECTION("sort with member method")
    {
        std::vector<int> vect = {6, 4, 0, 5, 1, 2, 7, 3};
        List<Dummy> list;
        std::vector<int>::iterator it;
        for (it = vect.begin(); it != vect.end(); ++it)
        {
            list.append(Dummy(*it));
        }
        REQUIRE (list.size() == 8);
        list.sort();
        List<int> output;
        List<Dummy>::iterator lit;
        for (lit = list.begin(); lit != list.end(); ++lit)
        {
            output.append((*lit).value());
        }        
        REQUIRE (output == List<int>({0, 1, 2, 3, 4, 5, 6, 7}));
    }
    
    SECTION("sort with functor")
    {
        List<int> list = {6, 4, 0, 5, 1, 2, 7, 3};
        Comp cmp;
        list.sort(cmp);
        REQUIRE (list == List<int>({0, 1, 2, 3, 4, 5, 6, 7}));
    }
    
    SECTION("sort with std::function around function")
    {
        List<int> list = {6, 4, 0, 5, 1, 2, 7, 3};
        std::function<bool(const int&, const int&)> func = sortInt;
        list.sort(func);
        REQUIRE (list == List<int>({3, 2, 4, 1, 5, 0, 6, 7}));
    }
    
    SECTION("sort with std::function around a functor")
    {
        List<int> list = {6, 4, 0, 5, 1, 2, 7, 3};
        Comp cmp;
        std::function<bool(const int&, const int&)> func = cmp;
        list.sort(func);
        REQUIRE (list == List<int>({0, 1, 2, 3, 4, 5, 6, 7}));
    }
    
    SECTION("sort with std::function around a class method")
    {
        List<int> list = {6, 4, 0, 5, 1, 2, 7, 3};
        Comp cmp;
        std::function<bool(const int&, const int&)> func = std::bind(&Comp::compare, cmp, std::placeholders::_1, std::placeholders::_2);
        list.sort(func);
        REQUIRE (list == List<int>({0, 1, 2, 3, 4, 5, 6, 7}));
    }
    
    SECTION("reverse")
    {
        List<int> list = {6, 4, 0, 5, 1, 2, 7, 3};
        list.sort(sortInt);
        REQUIRE (list == List<int>({3, 2, 4, 1, 5, 0, 6, 7}));
        list.reverse();
        REQUIRE (list == List<int>({7, 6, 0, 5, 1, 4, 2, 3}));
    }
    
    SECTION("native forward iterator")
    {
        List<int> list1 = {0, 2, 4, 6, 8};
        List<int>::iterator it1;
        for (it1 = list1.begin(); it1 != list1.end(); ++it1)
        {
            long i = it1 - list1.begin();
            REQUIRE (list1[i] == *it1);
        }
        const List<int> list2 = {1, 3, 5, 7, 9};
        List<int>::const_iterator it2;
        for (it2 = list2.begin(); it2 != list2.end(); ++it2)
        {
            long i = it2 - list2.begin();
            REQUIRE (list2[i] == *it2);
        }
    }
    
    SECTION("native reverse iterator")
    {
        List<int> list1 = {0, 2, 4, 6, 8};
        List<int>::reverse_iterator it1;
        for (it1 = list1.rbegin(); it1 != list1.rend(); ++it1)
        {
            long i = list1.size() - 1 - (it1 - list1.rbegin());
            REQUIRE (list1[i] == *it1);
        }
        const List<int> list2 = {1, 3, 5, 7, 9};
        List<int>::const_reverse_iterator it2;
        for (it2 = list2.rbegin(); it2 != list2.rend(); ++it2)
        {
            long i = list2.size() - 1 - (it2 - list2.rbegin());
            REQUIRE (list2[i] == *it2);
        }
    }
    
    SECTION("clear")
    {
        List<int> list1 = {0, 2, 4, 6, 8};
        REQUIRE (list1.size() == 5);
        list1.clear();
        REQUIRE (list1.size() == 0);
    }
    
    SECTION("list of pointers")
    {
        List<int*> list;
        int a = 0;
        int b = 1;
        int c = 2;
        int d = 3;
        list.append(&a);
        list.append(&b);
        list.append(&c);
        list.append(&d);
        REQUIRE (*list[2] == 2);
        REQUIRE (*list[0] == 0);
        
    }

} //end of TEST_CASE

TEST_CASE("list iterator", "[collections]")
{
    SECTION("Constructor")
    {
        List<int> list1 = {0, 2, 4, 6, 8};
        const List<int> list2 = {1, 3, 5, 9};
        ListIterator< List<int> > it1(list1);
        ListIterator< const List<int> > it2(list2);
        REQUIRE (it1.currentItem() == 0);
        REQUIRE (it2.currentItem() == 1);
        ReverseListIterator< List<int> > rit1(list1);
        ReverseListIterator< const List<int> > rit2(list2);
        REQUIRE (rit1.currentItem() == 8);
        REQUIRE (rit2.currentItem() == 9);
    }
    
    SECTION("Iteration")
    {
        List<int> list1 = {0, 2, 4, 6, 8};
        const List<int> list2 = {1, 3, 5, 7, 9};
        ListIterator< List<int> > it1(list1);
        ListIterator< const List<int> > it2(list2);
        ReverseListIterator< List<int> > rit1(list1);
        ReverseListIterator< const List<int> > rit2(list2);
        List<int> output;
        for (it1.first(); !it1.isDone(); it1.next())
        {
            output.append(it1.currentItem());
        }
        REQUIRE (output == List<int>({0, 2, 4, 6, 8}));
        output.clear();
        for (it2.first(); !it2.isDone(); it2.next())
        {
            output.append(it2.currentItem());
        }
        REQUIRE (output == List<int>({1, 3, 5, 7, 9}));
        output.clear();
        for (rit1.first(); !rit1.isDone(); rit1.next())
        {
            output.append(rit1.currentItem());
        }
        REQUIRE (output == List<int>({8, 6, 4, 2, 0}));
        output.clear();
        for (rit2.first(); !rit2.isDone(); rit2.next())
        {
            output.append(rit2.currentItem());
        }
        REQUIRE (output == List<int>({9, 7, 5, 3, 1}));
    }
    
    SECTION("Inplace modification of list")
    {
        List<int> list = {0, 2, 4, 6, 8};
        ListIterator< List<int> > it(list);
        ReverseListIterator< List<int> > rit(list);
        for (it.first(); !it.isDone(); it.next())
        {
            it.currentItem() *= 2;
        }
        REQUIRE (list == List<int>({0, 4, 8, 12, 16}));
        for (rit.first(); !rit.isDone(); rit.next())
        {
            rit.currentItem() *= 2;
        }
        REQUIRE (list == List<int>({0, 8, 16, 24, 32}));        
    }
    
    SECTION("Polymorphism check")
    {
        List<int> list1 = {0, 2, 4, 6, 8};
        const List<int> list2 = {1, 3, 5, 7, 9};
        ListIterator< List<int> > it1(list1);
        ListIterator< const List<int> > it2(list2);
        ReverseListIterator< List<int> > rit1(list1);
        ReverseListIterator< const List<int> > rit2(list2);
        List<int> output;
        Iterator<int>* pit1 = &it1;
        Iterator<const int>* pit2 = &it2;        
        for (pit1->first(); !pit1->isDone(); pit1->next())
        {
            pit1->currentItem() *= 2;
            output.append(it1.currentItem());
        }
        REQUIRE (output == List<int>({0, 4, 8, 12, 16}));
        output.clear();
        for (pit2->first(); !pit2->isDone(); pit2->next())
        {
            output.append(pit2->currentItem());
        }
        REQUIRE (output == List<int>({1, 3, 5, 7, 9}));
        output.clear();
        pit1 = &rit1;
        pit2 = &rit2;
        for (pit1->first(); !pit1->isDone(); pit1->next())
        {
            pit1->currentItem() *= 2;
            output.append(pit1->currentItem());
        }
        REQUIRE (output == List<int>({32, 24, 16, 8, 0}));
        output.clear();
        for (pit2->first(); !pit2->isDone(); pit2->next())
        {
            output.append(pit2->currentItem());
        }
        REQUIRE (output == List<int>({9, 7, 5, 3, 1}));
    }
}