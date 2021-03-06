#include "catch.hpp"

#include <string>
#include <vector>
//#include <functional>
#include <iostream>
//#include <bitset>
//#include <random>
//#include <chrono>

#include "snowball/collections/dictionary.hpp"

using namespace snowball;
using namespace std;

int& funct1(int& a)
{
    cout << "ref " << a << endl;
    return a;
}

int& funct1(int&& a)
{
    cout << "move " << a << endl;
    return a;
}

//void funct1(int a)
//{
//    cout << "no ref " << a << endl;
//}

class HashableDummy
{
public:
    
    HashableDummy(string name): m_name(name) { m_values.clear(); };
    ~HashableDummy() { };
    HashableDummy(const HashableDummy& other): 
        m_name(other.m_name), m_values(other.m_values) { };
    HashableDummy& operator=(const HashableDummy& other)
    {
        if (&other != this)
        {
            m_name = other.m_name;
            m_values = other.m_values;
            m_values.resize(other.m_values.capacity());
        }   
        return *this;
    };
    bool operator==(const HashableDummy& other) const
    {
        if (m_name != other.m_name)
            return false;
        else
            return m_values == other.m_values;
    };
    void append(const int a)
    {
        m_values.push_back(a);
    };
    size_t size() const { return m_values.size(); };
    
    size_t capacity() const { return m_values.capacity(); };
    
private:

    string m_name;
    vector<int> m_values;
};


TEST_CASE("dictionary", "[collections]")
{
    
    SECTION("constructor")
    {
        Dictionary<string, int> dct1;
        REQUIRE (dct1.size() == 0);
        Dictionary<int, int> dct2;
        REQUIRE (dct2.size() == 0);
        Dictionary<HashableDummy, int, Hash<HashableDummy> > dct3;
        REQUIRE (dct3.size() == 0);
    }
    
    SECTION("assignment operator")
    {
        Dictionary<string, int> dct1;
        dct1["one"] = 1;
        dct1["two"] = 2;
        Dictionary<string, int> dct2;
        dct2 = dct1;
        REQUIRE(dct2.size() == 2);
        REQUIRE(dct2["two"] == 2);
    }

    SECTION("operator[] with non-const dictionary")
    {
        Dictionary<string, int> dct1;
        dct1[string("Hello World !")] = 1;
        dct1[string("Undefined")];
        REQUIRE (dct1["Hello World !"] == 1);
        REQUIRE (dct1["Undefined"] == 0);
        Dictionary<HashableDummy, string, Hash<HashableDummy> > dct2;
        HashableDummy dum1("odd");
        dum1.append(1);
        //dum1.append(3);
        //dum1.append(5);
        dct2[dum1] = "odd";
        HashableDummy cpy1(dum1);
        REQUIRE (dct2[dum1] == "odd");
        Hash<HashableDummy> hasher;
        cout << hasher(dum1) << " " << dum1.size() << endl;
        cout << hasher(cpy1) << " " << cpy1.size() << endl;
        cout << sizeof(dum1) << endl;
        cout << sizeof(cpy1) << endl;
        cout << dum1.capacity() << " " << cpy1.capacity() << endl;
        //HashableDummy cpy2(1);
        
        //REQUIRE (hasher(dum1) == hasher(cpy2));
        //REQUIRE (dum1 == cpy2);
        Hash< vector<int> > hasher2;
        const vector<int> vect1 = {0, 2, 4};
        const vector<int> vect2 = {0, 2, 4};
        cout << hasher2(vect1) << " " << hasher2(vect2) << endl;
        vector<int> vect3(vect2);
        cout << hasher2(vect2) << " " << hasher2(vect3) << endl;
        cout << reinterpret_cast<const char*>(&vect1) << endl;
    }
    
    SECTION("keys and values")
    {
        Dictionary<int, string> dict;
        dict[1] = "one";
        dict[2] = "two";
        dict[3] = "three";
        List<string> values = dict.values();
        List<int> keys = dict.keys();
        values.sort();
        keys.sort();
        REQUIRE (keys == List<int>({1, 2, 3}));
        REQUIRE (values == List<string>({"one", "three", "two"}));
    }
    
    SECTION("get with default value")
    {
        Dictionary<string, int> dict;
        dict["one"] = 1;
        dict["two"] = 2;
        const Dictionary<string, int> cdict(dict);
        REQUIRE (dict.get("one", 0) == 1);
        REQUIRE (dict.get("three", 3) == 3);
        REQUIRE (dict.size() == 2);
        REQUIRE (cdict.get("two", 0) == 2);
        REQUIRE (cdict.get("three", 3) == 3);
        REQUIRE (cdict.size() == 2);
        Dictionary<string, string> dict2;
        dict2["one"] = "un";
        dict2["two"] = "deux";
        REQUIRE (dict2.get("one", "n/a") == "un");
        dict2.get("two", "n/a") = "dos";
        REQUIRE (dict2.get("two", "n/a") == "dos");
        dict2.get("three", "n/a") = "tres";
        REQUIRE (dict2.size() == 2);
    }
    
}

