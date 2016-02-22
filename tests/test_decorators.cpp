#include "catch.hpp"

#include <iostream>
#include <chrono>
#include <cmath>
#include <thread>

#include "snowball/decorators/timeit.hpp"
#include "snowball/decorators/decorator.hpp"


using namespace snowball;
using namespace std;

float sum2(float a, float b)
{
    return a + b;
};

float sum3(float a, float b, float c)
{
    return a + b + c;
};

bool almostEquals(float a, float b, float eps=1.e-6)
{
    return abs(a - b) < eps;
};

void mysleep(int seconds)
{
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
};

class DummyDeco
{
public:
    DummyDeco() { };
    float operator()(float a, float b) {return a * b; };
    float div(float a, float b) {return a / b;};
};

class StaticDummyDeco
{
public:
    StaticDummyDeco() { };
    static float div(float a, float b) {return a / b; };
};


TEST_CASE("base class", "[decorators]")
{

    SECTION("using a function")
    {
        Decorator<float(float, float)> deco1(sum2);
        REQUIRE ( almostEquals(deco1(2., 5.), 7.) );
        Decorator<float(float, float, float)> deco2(sum3);
        REQUIRE ( almostEquals(deco2(2., 3., 5.), 10.) );
    }
    
    SECTION("using a lambda")
    {
        Decorator<float(float, float)> deco([](float a, float b) { return a - b;});
        REQUIRE ( almostEquals(deco(5., 1.), 4.) );
    }
    
    SECTION("using a functor object")
    {
        DummyDeco f;
        Decorator<float(float, float)> deco(f);
        REQUIRE (almostEquals(deco(3., 4.), 12.) );
    }
    
    SECTION("using a member function")
    {
        DummyDeco f;
        auto func = bind(&DummyDeco::div, f, placeholders::_1, placeholders::_2);
        Decorator<float(float, float)> deco1(func);
        REQUIRE (almostEquals(deco1(12., 3.), 4.));
        StaticDummyDeco s;
        auto sunc = bind(&StaticDummyDeco::div, placeholders::_1, placeholders::_2);
        Decorator<float(float, float)> deco2(sunc);
        REQUIRE (almostEquals(deco1(12., 4.), 3.));
    }
    
    SECTION("used as a closure")
    {
        auto func = bind([](float a, float b){return a - b;}, 10., placeholders::_1);
        Decorator<float(float)> deco(func);
        REQUIRE (almostEquals(deco(7.), 3.));
    }
}

TEST_CASE("timeit", "[decorators]")
{
    SECTION("wallTime")
    {
        TimeIt<void(int)> timer(mysleep);
        timer(1);
        REQUIRE (almostEquals(timer.wallTime(), 1000., 1.));
    }
    
    SECTION("cpuTime")
    {
        DummyDeco f;
        //we use a closure
        auto func = bind(&DummyDeco::div, f, 12., placeholders::_1);
        TimeIt<float(float)> timer(func, 1000);
        REQUIRE (almostEquals(timer(3.), 4.));
        REQUIRE (almostEquals(timer.cpuTime(), 0., 1.e-1)); //unless you computer requires a massive upgrade
    }
}