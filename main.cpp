/*
Prject 4: Part 8 / 9
 video: Chapter 5 Part 6 Task 

Create a branch named Part8

 R-Values L-Values Move Semantics.

 This Task is going to demonstrate R-Values and writing Generic Code

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
    it's very easy to mess this task up. 
 
 Your job is to replace the owned type (the primitive specified by your template argument) from the 
     Templated Class you created in Ch5 p04 with a struct named Temporary that can behave ENTIRELY as a temporary object.
 
 That means you must use conversion functions to interact with what it owns.
 
 You need to figure out how to use conversion functions to be able to GET and SET the 'value' member variable.
    hint: conversion functions can return by value and also by ___...
  
 1) Here is a starting point for how to implement your Temporary struct.
 */

#include <typeinfo>
#include <iostream>
template<typename NumericType>
struct Temporary
{
    Temporary(NumericType t) : v(t)
    {
        std::cout << "I'm a Temporary<" << typeid(v).name() << "> object, #" << counter++ << std::endl;
    }
    /*
     revise these conversion functions to read/write to 'v' here
     hint: what qualifier do read-only functions usually have?
     */
    operator NumericType() const
    {
        /* read-only function */
        return v;
    }
    operator NumericType&()
    {
        /* read/write function */
        return v;
    }

private:
    static int counter;
    NumericType v;
};

/*
 2) add the definition of Temporary::counter here, which is a static variable and must be defined outside of the class.
    Remember the rules about how to define a Template member variable/function outside of the class.
*/
template<typename NumericType>
int Temporary<NumericType>::counter = 0;

/*
 3) You'll need to template your overloaded math operator functions in your Templated Class from Ch5 p04
    use static_cast to convert whatever type is passed in to your template's NumericType before performing the +=, -=, etc.  here's an example implementation:
 */
// namespace example
// {
// template<typename NumericType>
// struct Numeric
// {
//     //snip
//     template<typename OtherType>
//     Numeric& operator-=(const OtherType& o) 
//     { 
//         *value -= static_cast<NumericType>(o); 
//         return *this; 
//     }
//     //snip
// };
// }

/*
 4) remove your specialized <double> template of your Numeric<T> class from the previous task (ch5 p04)
    replace the 2 apply() functions in your Numeric<T> with the single templated apply() function from the specialized <double> template.
 */

/*
 5) Template your pow() function the same way you templated the overloaded math operators
    Remove the call to powInternal() and just call std::pow() directly.
    you'll need to static_cast<> the pow() argument the same way you did in the overloaded math operators, when you pass it to std::pow()
 */
/*
 
 6) Finally, your conversion function in your templated class is going to be returning this Temporary, 
        so you should probably NOT return by copy if you want your templated class's owned object to be modified by any math operation.
    See the previous hint for implementing the conversion functions for the Temporary if you want to get the held value
*/


/*
 7)   replace main() with the main below

 If you did everything correctly, this is the output you should get:
 
I'm a Temporary<f> object, #0
I'm a Temporary<i> object, #0
I'm a Temporary<d> object, #0
f: -1.89
d: -3.024
i: -9
Point { x: -1.89, y: -9 }
d: 3.024
I'm a Temporary<d> object, #1
I'm a Temporary<d> object, #2
d: 1.49519e+08
Point { x: -2.82591e+08, y: -1.34567e+09 }
I'm a Temporary<f> object, #1
I'm a Temporary<i> object, #1
I'm a Temporary<i> object, #2
I'm a Temporary<i> object, #3
intNum: 5
I'm a Temporary<f> object, #2
f squared: 3.5721
I'm a Temporary<f> object, #3
f cubed: 45.5796
I'm a Temporary<d> object, #3
d squared: 2.2356e+16
I'm a Temporary<d> object, #4
d cubed: 1.11733e+49
I'm a Temporary<i> object, #4
i squared: 81
I'm a Temporary<i> object, #5
i cubed: 531441

Use a service like https://www.diffchecker.com/diff to compare your output. 
*/

#include <iostream>
#include <cmath>
#include <functional>
#include <memory>
#include <type_traits>
#include <limits>

struct A { };

struct HeapA
{
    ~HeapA()
    {   
        delete a;
        a = nullptr;
    }
    A* a = new A();
};

struct IntType;
struct DoubleType;

/*-------------------------------------------------------------------------------*/
template<typename NumericType>
struct Numeric
{
    using Type = Temporary<NumericType>;
private:
    std::unique_ptr<Type> value;
public:
    Numeric( Type x ) : value( std::make_unique<Type>(x) ) { }

    template<typename Callable>
    Numeric& apply( Callable&& f )
    {
        f( value );

        return *this;
    }

    template<typename OtherType>
    Numeric& pow(const OtherType& x)
    {
        *value = static_cast<NumericType>(std::pow( *value, static_cast<NumericType>(x) ));
        return *this;
    }

    template<typename OtherType>
    Numeric& operator=( const OtherType& x)
    {
        *value = static_cast<NumericType>(x);
        return *this;
    }

    template<typename OtherType>
    Numeric& operator+=( const OtherType& x )
    {
        *value += static_cast<NumericType>(x);
        return *this;
    }

    template<typename OtherType>
    Numeric& operator-=( const OtherType& x )
    {
        *value -= static_cast<NumericType>(x);
        return *this;
    }

    template<typename OtherType>
    Numeric& operator*=( const OtherType& x )
    {
        *value *= static_cast<NumericType>(x);
        return *this;
    }
    
    template<typename DivisorType>
    Numeric& operator/=( const DivisorType& x )
    {
        if ( std::is_same<int, NumericType>::value )
        {
            if constexpr ( std::is_same<int, DivisorType>::value )
            {
                if constexpr ( x == 0 )
                {
                    std::cout << "error: integer division by zero is an error and will crash the program!" << std::endl;
                    return *this;
                }
            }
            else if( x < std::numeric_limits<DivisorType>::epsilon() )
            {
                std::cout << "can't divide integers by zero!" << std::endl;
                return *this;
            }
        }
        else if( x < std::numeric_limits<DivisorType>::epsilon() )
        {
            std::cout << "warning: floating point division by zero!" << std::endl;
        }

        *value /= static_cast<NumericType>(x);
        return *this;
    }

    operator Type() const { return *value; }
    operator NumericType() const { return *value; }
    operator NumericType&() { return *value; }
};

/*-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------*/
template<typename numTypeA, typename numTypeB>
struct Point
{
private:
    float x{0};
    float y{0};
public:
    Point( const numTypeA& var1, const numTypeB& var2 ) : x( var1 ), y( var2 ) { }
    
    template<typename OtherType>
    Point& multiply( const OtherType& m )
    {
        x *= static_cast<float>(m);
        y *= static_cast<float>(m);
        return *this;
    }
    
    void toString()
    {
        std::cout << "Point { x: " << x << ", y: " << y << " }" << std::endl; 	
    }
};

/*-------------------------------------------------------------------------------*/
template<typename numType>
void myNumericFreeFunct( std::unique_ptr<numType>& value )
{
    *value += static_cast<numType>(7.0f);
}

template<typename numType>
void cube( std::unique_ptr<numType>& value )
{
    *value = *value * *value * *value;
}

/*-------------------------------------------------------------------------------*/
// void part3()
// {
//     Numeric ft( 5.5f );
//     Numeric dt( 11.1 );
//     Numeric it ( 34 );
//     Numeric pi( 3.14 );

//     ft *= ft;
//     ft *= ft;
//     ft /= static_cast<float>(it);
//     std::cout << "The result of FloatType^3 divided by IntType is: " << ft << std::endl;
    
//     dt *= 3;
//     dt += static_cast<double>(it);
//     std::cout << "The result of DoubleType times 3 plus IntType is : " << dt << std::endl;

//     it /= static_cast<int>(pi);
//     it *= static_cast<int>(dt);
//     it -= static_cast<int>(ft);
//     std::cout << "The result of IntType divided by 3.14 multiplied by DoubleType minus FloatType is: " << it << std::endl;

//     std::cout << "An operation followed by attempts to divide by 0, which are ignored and warns user: " << std::endl;
//     it *= it;
//     it /= 0;
//     it /= 0.f;
//     it /= 0.0;
//     std::cout << it << std::endl;
    
//     it *= static_cast<int>(ft);
//     std::cout << "FloatType x IntType  =  " << it << std::endl;
    
//     it += static_cast<int>(dt);
//     it += static_cast<int>(ft);
//     it *= 24;
//     std::cout << "(IntType + DoubleType + FloatType) x 24 = " << it << std::endl;
// }

/*-------------------------------------------------------------------------------*/
// void part4()
// {
//     // ------------------------------------------------------------
//     //                          Power tests
//     // ------------------------------------------------------------
//     Numeric<float> ft1(2);
//     Numeric<double> dt1(2);
//     Numeric<int> it1(2);    
//     int floatExp = 2.0f;
//     int doubleExp = 2.0;
//     int intExp = 2;
//     Numeric<int> itExp(2);
//     Numeric<float> ftExp(2.0f);
//     Numeric<double> dtExp(2.0);
    
//     // Power tests with FloatType
//     std::cout << "Power tests with FloatType " << std::endl;
//     std::cout << "pow(ft1, floatExp) = " << ft1 << "^" << floatExp << " = " << ft1.pow(floatExp)  << std::endl;
//     std::cout << "pow(ft1, itExp) = " << ft1 << "^" << itExp << " = " << ft1.pow(static_cast<float>(itExp))  << std::endl;
//     std::cout << "pow(ft1, ftExp) = " << ft1 << "^" << ftExp << " = " << ft1.pow(ftExp)  << std::endl;    
//     std::cout << "pow(ft1, dtExp) = " << ft1 << "^" << dtExp << " = " << ft1.pow(static_cast<float>(dtExp))  << std::endl;    
//     std::cout << "---------------------\n" << std::endl;  

//     // Power tests with DoubleType
//     std::cout << "Power tests with DoubleType " << std::endl;
//     std::cout << "pow(dt1, doubleExp) = " << dt1 << "^" << doubleExp << " = " << dt1.pow(intExp)  << std::endl;
//     std::cout << "pow(dt1, itExp) = " << dt1 << "^" << itExp << " = " << dt1.pow(static_cast<double>(itExp))  << std::endl;
//     std::cout << "pow(dt1, ftExp) = " << dt1 << "^" << ftExp << " = " << dt1.pow(static_cast<double>(ftExp))  << std::endl;    
//     std::cout << "pow(dt1, dtExp) = " << dt1 << "^" << dtExp << " = " << dt1.pow(dtExp)  << std::endl;    
//     std::cout << "---------------------\n" << std::endl;    

//     // Power tests with IntType
//     std::cout << "Power tests with IntType " << std::endl;
//     std::cout << "pow(it1, intExp) = " << it1 << "^" << intExp << " = " << it1.pow(intExp)  << std::endl;
//     std::cout << "pow(it1, itExp) = " << it1 << "^" << itExp << " = " << it1.pow(itExp)  << std::endl;
//     std::cout << "pow(it1, ftExp) = " << it1 << "^" << ftExp << " = " << it1.pow(static_cast<int>(ftExp))  << std::endl;    
//     std::cout << "pow(it1, dtExp) = " << it1 << "^" << dtExp << " = " << it1.pow(static_cast<int>(dtExp)) << std::endl;    
//     std::cout << "===============================\n" << std::endl; 

//     // ------------------------------------------------------------
//     //                          Point tests
//     // ------------------------------------------------------------
//     Numeric ft2(3.0f);
//     Numeric dt2(4.0);
//     Numeric it2(5);
//     float floatMul = 6.0f; // float

//     // Point tests with float
//     std::cout << "Point tests with float argument:" << std::endl;
//     Point<float> p0(ft2, floatMul);
//     p0.toString();   
//     std::cout << "Multiplication factor: " << floatMul << std::endl;
//     p0.multiply(floatMul); 
//     p0.toString();   
//     std::cout << "---------------------\n" << std::endl;

//     // Point tests with FloatType
//     std::cout << "Point tests with FloatType argument:" << std::endl;
//     Point<float> p1(ft2, ft2);
//     p1.toString();   
//     std::cout << "Multiplication factor: " << ft2 << std::endl;
//     p1.multiply(ft2); 
//     p1.toString();   
//     std::cout << "---------------------\n" << std::endl;

//     // Point tests with DoubleType
//     std::cout << "Point tests with DoubleType argument:" << std::endl;
//     Point<float> p2(ft2, static_cast<float>(dt2));
//     p2.toString();   
//     std::cout << "Multiplication factor: " << dt2 << std::endl;
//     p2.multiply(static_cast<float>(dt2)); 
//     p2.toString();   
//     std::cout << "---------------------\n" << std::endl;

//     // Point tests with IntType
//     std::cout << "Point tests with IntType argument:" << std::endl;
//     Point<float> p3(ft2, static_cast<float>(dt2));
//     p3.toString();   
//     std::cout << "Multiplication factor: " << it2 << std::endl;
//     p3.multiply(it2); 
//     p3.toString();   
//     std::cout << "---------------------\n" << std::endl;
// }

// void part6()
// {
//     FloatType ft3(3.0f);
//     DoubleType dt3(4.0);
//     IntType it3(5);
    
//     std::cout << "Calling FloatType::apply() using a lambda (adds 7.0f) and FloatType as return type:" << std::endl;
//     std::cout << "ft3 before: " << ft3 << std::endl;
//     ft3.apply( [&]( float& a ) -> FloatType& { a += 7.0f; return ft3; } );
//     std::cout << "ft3 after: " << ft3 << std::endl;
//     std::cout << "Calling FloatType::apply() using a free function (adds 7.0f) and void as return type:" << std::endl;
//     std::cout << "ft3 before: " << ft3 << std::endl;
//     ft3.apply(myFloatFreeFunct);
//     std::cout << "ft3 after: " << ft3 << std::endl;
//     std::cout << "---------------------\n" << std::endl;

//     std::cout << "Calling DoubleType::apply() using a lambda (adds 6.0) and DoubleType as return type:" << std::endl;
//     std::cout << "dt3 before: " << dt3 << std::endl;
//     dt3.apply( [&]( double& a ) -> DoubleType& { a += 6.0; return dt3; } );
//     std::cout << "dt3 after: " << dt3 << std::endl;
//     std::cout << "Calling DoubleType::apply() using a free function (adds 6.0) and void as return type:" << std::endl;
//     std::cout << "dt3 before: " << dt3 << std::endl;
//     dt3.apply(myDoubleFreeFunct);
//     std::cout << "dt3 after: " << dt3 << std::endl;
//     std::cout << "---------------------\n" << std::endl;

//     std::cout << "Calling IntType::apply() using a lambda (adds 5) and IntType as return type:" << std::endl;
//     std::cout << "it3 before: " << it3 << std::endl;
//     it3.apply( [&]( int& a ) -> IntType& { a += 5; return it3; } );
//     std::cout << "it3 after: " << it3 << std::endl;
//     std::cout << "Calling IntType::apply() using a free function (adds 5) and void as return type:" << std::endl;
//     std::cout << "it3 before: " << it3 << std::endl;
//     it3.apply(myIntFreeFunct);
//     std::cout << "it3 after: " << it3 << std::endl;
//     std::cout << "---------------------\n" << std::endl;    
// }

// void part7()
// {
//     Numeric ft3(3.0f);
//     Numeric<double> dt3(4.0);
//     Numeric it3(5);
    
//     std::cout << "Calling Numeric<float>::apply() using a lambda (adds 7.0f) and Numeric<float> as return type:" << std::endl;
//     std::cout << "ft3 before: " << ft3 << std::endl;

//     {
//         using Type = decltype(ft3)::Type;
//         using ReturnType = decltype(ft3);
//         ft3.apply( [&ft3]( std::unique_ptr<Type>& a ) -> ReturnType& { *a += 7.0f; return ft3; } );
//     }

//     std::cout << "ft3 after: " << ft3 << std::endl;
//     std::cout << "Calling Numeric<float>::apply() twice using a free function (adds 7.0f) and void as return type:" << std::endl;
//     std::cout << "ft3 before: " << ft3 << std::endl;
//     ft3.apply(myNumericFreeFunct).apply(myNumericFreeFunct);
//     std::cout << "ft3 after: " << ft3 << std::endl;
//     std::cout << "---------------------\n" << std::endl;

//     std::cout << "Calling Numeric<double>::apply() using a lambda (adds 6.0) and Numeric<double> as return type:" << std::endl;
//     std::cout << "dt3 before: " << dt3 << std::endl;

//     {
//         using Type = decltype(dt3)::Type;
//         using ReturnType = decltype(dt3);
//         dt3.apply( [&]( std::unique_ptr<Type>& a ) -> ReturnType& { *a += 6.0; return dt3; } );
//     }
    
//     std::cout << "dt3 after: " << dt3 << std::endl;
//     std::cout << "Calling Numeric<double>::apply() twice using a free function (adds 7.0) and void as return type:" << std::endl;
//     std::cout << "dt3 before: " << dt3 << std::endl;
//     dt3.apply(myNumericFreeFunct<double>).apply(myNumericFreeFunct<double>); // This calls the templated apply fcn
//     std::cout << "dt3 after: " << dt3 << std::endl;
//     std::cout << "---------------------\n" << std::endl;

//     std::cout << "Calling Numeric<int>::apply() using a lambda (adds 5) and Numeric<int> as return type:" << std::endl;
//     std::cout << "it3 before: " << it3 << std::endl;

//     {
//         using Type = decltype(it3)::Type;
//         using ReturnType = decltype(it3);
//         it3.apply( [&]( std::unique_ptr<Type>& a ) -> ReturnType& { *a += 5; return it3; } );
//     }
//     std::cout << "it3 after: " << it3 << std::endl;
//     std::cout << "Calling Numeric<int>::apply() twice using a free function (adds 7) and void as return type:" << std::endl;
//     std::cout << "it3 before: " << it3 << std::endl;
//     it3.apply(myNumericFreeFunct).apply(myNumericFreeFunct);
//     std::cout << "it3 after: " << it3 << std::endl;
//     std::cout << "---------------------\n" << std::endl;    
// }

int main()
{
    Numeric<float> f(0.1f);
    Numeric<int> i(3);
    Numeric<double> d(4.2);
    
    f += 2.f;
    f -= i;
    f *= d;
    f /= 2.f;
    std::cout << "f: " << f << std::endl;
    
    d += 2.f;
    d -= i;
    d *= f;
    d /= 2.f;
    std::cout << "d: " << d << std::endl;
    
    i += 2.f; i -= f; i *= d; i /= 2.f;
    std::cout << "i: "<< i << std::endl;
    
    Point p(f, i);
    p.toString();
    
    d *= -1;
    std::cout << "d: " << d << std::endl;
    
    p.multiply(d.pow(f).pow(i));
    std::cout << "d: " << d << std::endl;
    
    p.toString();
    
    Numeric<float> floatNum(4.3f);
    Numeric<int> intNum(2);
    Numeric<int> intNum2(6);
    intNum = 2 + (intNum2 - 4) + static_cast<double>(floatNum) / 2.3;
    std::cout << "intNum: " << intNum << std::endl;
    
    {
        using Type = decltype(f)::Type;
        f.apply([&f](std::unique_ptr<Type>&value) -> decltype(f)&
                {
                    auto& v = *value;
                    v = v * v;
                    return f;
                });
        std::cout << "f squared: " << f << std::endl;
        
        f.apply( cube<Type> );
        std::cout << "f cubed: " << f << std::endl;
    }
    
    {
        using Type = decltype(d)::Type;
        d.apply([&d](std::unique_ptr<Type>&value) -> decltype(d)&
                {
                    auto& v = *value;
                    v = v * v;
                    return d;
                });
        std::cout << "d squared: " << d << std::endl;
        
        d.apply( cube<Type> );
        std::cout << "d cubed: " << d << std::endl;
    }
    
    {
        using Type = decltype(i)::Type;
        i.apply([&i](std::unique_ptr<Type>&value) -> decltype(i)&
                {
                    auto& v = *value;
                    v = v * v;
                    return i;
                });
        std::cout << "i squared: " << i << std::endl;
        
        i.apply( cube<Type> );
        std::cout << "i cubed: " << i << std::endl;
    }
}
