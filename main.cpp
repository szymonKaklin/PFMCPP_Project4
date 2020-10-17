/*
 Project 4 - Part 2 / 9
 Video: Chapter 3 Part 6

 Create a branch named Part2

New/This/Pointers/References conclusion

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 0) in the blank space below, declare/define an empty struct named 'A' on a single Line. 
     on the lines below it, write a struct named 'HeapA' that correctly shows how to own an instance of 'A' 
         on the heap without leaking, without using smart pointers. 
 */
#include <iostream>

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

 /*
 1) Edit your 3 structs so that they own a heap-allocated primitive type without using smart pointers named 'value'
         IntType should own a heap-allocated int, for example.
 
 2) give it a constructor that takes the appropriate primitive
    this argument will initialize the owned primitive's value.
         i.e. if you're owning an int on the heap, your ctor argument will initialize that heap-allocated int's value.
 
 3) modify those add/subtract/divide/multiply member functions from chapter 2 on it
         a) make them modify the owned numeric type
         b) set them up so they can be chained together.
             i.e.
             DoubleType dt(3.5);
             dt.add(3.0).multiply(-2.5).divide(7.2); //an example of chaining
 
 4) write add/subtract/divide/multiply member functions for each type that take your 3 UDTs
        These are in addition to your member functions that take primitives
        for example, IntType::divide(const DoubleType& dt);
        These functions should return the result of calling the function that takes the primitive.
     
 5) Don't let your heap-allocated owned type leak!
 
 6) replace your main() with the main() below.
    It has some intentional mistakes that you need to fix to match the expected output
    i.e. don't forget to dereference your pointers to get the value they hold.

 7) click the [run] button.  Clear up any errors or warnings as best you can.
 */

 /*
your program should generate the following output EXACTLY.
This includes the warnings.
Use a service like https://www.diffchecker.com/diff to compare your output. 
you'll learn to solve the conversion warnings in the next project part.

18 warnings generated.
FloatType add result=4
FloatType subtract result=2
FloatType multiply result=4
FloatType divide result=0.25

DoubleType add result=4
DoubleType subtract result=2
DoubleType multiply result=4
DoubleType divide result=0.8

IntType add result=4
IntType subtract result=2
IntType multiply result=4
IntType divide result=1

Chain calculation = 590
New value of ft = (ft + 3.0f) * 1.5f / 5.0f = 0.975
---------------------

Initial value of dt: 0.8
Initial value of it: 590
Use of function concatenation (mixed type arguments) 
New value of dt = (dt * it) / 5.0f + ft = 95.375
---------------------

Intercept division by 0 
New value of it = it / 0 = error: integer division by zero is an error and will crash the program!
590
New value of ft = ft / 0 = warning: floating point division by zero!
inf
New value of dt = dt / 0 = warning: floating point division by zero!
inf
---------------------

good to go!





*/

struct IntType;
struct DoubleType;
struct FloatType
{
    FloatType( float x ) : value( new float(x) ) { }
    ~FloatType()
    {
        delete value;
        value = nullptr;
    }
    float* value = nullptr;
    
    FloatType& add( float x );
    FloatType& subtract( float x );
    FloatType& multiply( float x );
    FloatType& divide( float x );

    FloatType& add( const FloatType& ft );
    FloatType& add( const IntType& it );
    FloatType& add( const DoubleType& dt );

    FloatType& subtract( const FloatType& ft );
    FloatType& subtract( const IntType& it );
    FloatType& subtract( const DoubleType& dt );

    FloatType& multiply( const FloatType& ft );
    FloatType& multiply( const IntType& it );
    FloatType& multiply( const DoubleType& dt );

    FloatType& divide( const FloatType& ft );
    FloatType& divide( const IntType& it );
    FloatType& divide( const DoubleType& dt );
};

FloatType& FloatType::add( float x )
{
    *value += x;
    return *this;
}

FloatType& FloatType::subtract( float x )
{
    *value -= x;
    return *this;
}

FloatType& FloatType::multiply( float x )
{
    *value *= x;
    return *this;
}

FloatType& FloatType::divide( float x )
{
    if ( x == 0.f )
    {
        std::cout << "warning: floating point division by zero!" << std::endl;
    }
    *value /= x;
    return *this;
}

FloatType& FloatType::add( const FloatType& ft )
{
    return add( *ft.value );
}

FloatType& FloatType::subtract( const FloatType& ft )
{
    return subtract( *ft.value );
}

FloatType& FloatType::multiply( const FloatType& ft )
{
    return FloatType::multiply( *ft.value );
}

FloatType& FloatType::divide( const FloatType& ft )
{
    return divide( *ft.value );
}

struct IntType
{
    IntType( int x ) : value( new int(x) ) { }
    ~IntType()
    {   
        delete value;
        value = nullptr;
    }
    int* value = nullptr;
    
    IntType& add( int x );
    IntType& subtract( int x );
    IntType& multiply( int x );
    IntType& divide( int x );

    IntType& add( const IntType& it );
    IntType& add( const FloatType& ft );
    IntType& add( const DoubleType& dt );

    IntType& subtract( const IntType& it );
    IntType& subtract( const FloatType& ft );
    IntType& subtract( const DoubleType& dt );

    IntType& multiply( const IntType& it );
    IntType& multiply( const FloatType& ft );
    IntType& multiply( const DoubleType& dt );

    IntType& divide( const IntType& it );
    IntType& divide( const FloatType& ft );
    IntType& divide( const DoubleType& dt );
};

IntType& IntType::add( int x )
{
    *value += x;
    return *this;
}

IntType& IntType::subtract( int x )
{
    *value -= x;
    return *this;
}

IntType& IntType::multiply( int x )
{
    *value *= x;
    return *this;
}

IntType& IntType::divide( int x )
{
    if ( x == 0 )
    {
        std::cout << "error: integer division by zero is an error and will crash the program!" << std::endl;
        return *this;
    }
    *value /= x;
    return *this;  
}

IntType& IntType::add( const IntType& it )
{
    return add( *it.value );
}

IntType& IntType::subtract( const IntType& it )
{
    return subtract( *it.value );
}

IntType& IntType::multiply( const IntType& it )
{
    return multiply( *it.value );
}

IntType& IntType::divide( const IntType& it )
{
    return divide( *it.value );
}

struct DoubleType
{
    DoubleType( double x ) : value( new double(x) ) { }
    ~DoubleType()
    {   
        delete value;
        value = nullptr;
    }
    double* value = nullptr;
    
    DoubleType& add( double x );
    DoubleType& subtract( double x );
    DoubleType& multiply( double x );
    DoubleType& divide( double x );

    DoubleType& add( const DoubleType& dt );
    DoubleType& add( const IntType& dt );
    DoubleType& add( const FloatType& dt );

    DoubleType& subtract( const DoubleType& dt );
    DoubleType& subtract( const IntType& dt );
    DoubleType& subtract( const FloatType& dt );

    DoubleType& multiply( const DoubleType& dt );
    DoubleType& multiply( const IntType& dt );
    DoubleType& multiply( const FloatType& dt );

    DoubleType& divide( const DoubleType& dt );
    DoubleType& divide( const IntType& dt );
    DoubleType& divide( const FloatType& dt );    
};

DoubleType& DoubleType::add( double x )
{
    *value += x;
    return *this;
}

DoubleType& DoubleType::subtract( double x )
{
    *value -= x;
    return *this;
}

DoubleType& DoubleType::multiply( double x )
{
    *value *= x;
    return *this;
}

DoubleType& DoubleType::divide( double x )
{
    if ( x == 0. )
    {
        std::cout << "warning: floating point division by zero!" << std::endl;
    }
    *value /= x;
    return *this;
}

DoubleType& DoubleType::add( const DoubleType& dt )
{
    return add( *dt.value );
}

DoubleType& DoubleType::subtract( const DoubleType& dt )
{
    return subtract( *dt.value );
}

DoubleType& DoubleType::multiply( const DoubleType& dt )
{
    return multiply( *dt.value );
}

DoubleType& DoubleType::divide( const DoubleType& dt )
{
    return divide( *dt.value );
}

// Custom UDT Math Functions
// FloatType

FloatType& FloatType::add( const IntType& it )
{
    return add( *it.value );
}

FloatType& FloatType::add( const DoubleType& dt )
{
    return add( *dt.value );
}

FloatType& FloatType::subtract( const IntType& it )
{
    return subtract( *it.value );
}

FloatType& FloatType::subtract( const DoubleType& dt )
{
    return subtract( *dt.value );
}

FloatType& FloatType::multiply( const IntType& it )
{
    return multiply( *it.value );
}

FloatType& FloatType::multiply( const DoubleType& dt )
{
    return multiply( *dt.value );
}

FloatType& FloatType::divide( const IntType& it )
{
    return multiply( *it.value );
}

FloatType& FloatType::divide( const DoubleType& dt )
{
    return divide( *dt.value );
}

// IntType
IntType& IntType::add( const FloatType& ft )
{
    return add( *ft.value );
}

IntType& IntType::add( const DoubleType& dt )
{
    return add( *dt.value );
}

IntType& IntType::subtract( const FloatType& ft )
{
    return subtract( *ft.value );
}

IntType& IntType::subtract( const DoubleType& dt )
{
    return subtract( *dt.value );
}

IntType& IntType::multiply( const FloatType& ft )
{
    return multiply( *ft.value );
}

IntType& IntType::multiply( const DoubleType& dt )
{
    return multiply( *dt.value );
}

IntType& IntType::divide( const FloatType& ft )
{
    return multiply( *ft.value );
}

IntType& IntType::divide( const DoubleType& dt )
{
    return divide( *dt.value );
}

// DoubleType
DoubleType& DoubleType::add( const FloatType& ft )
{
    return add( *ft.value );
}

DoubleType& DoubleType::add( const IntType& it )
{
    return add( *it.value );
}

DoubleType& DoubleType::subtract( const FloatType& ft )
{
    return subtract( *ft.value );
}

DoubleType& DoubleType::subtract( const IntType& it )
{
    return subtract( *it.value );
}

DoubleType& DoubleType::multiply( const FloatType& ft )
{
    return multiply( *ft.value );
}

DoubleType& DoubleType::multiply( const IntType& it )
{
    return multiply( *it.value );
}

DoubleType& DoubleType::divide( const FloatType& ft )
{
    return multiply( *ft.value );
}

DoubleType& DoubleType::divide( const IntType& it )
{
    return divide( *it.value );
}

int main()
{   
    //testing instruction 0
    HeapA heapA; 

    //assign heap primitives
    FloatType ft ( 2.0f );
    DoubleType dt ( 2 );
    IntType it ( 2 ) ;

    std::cout << "FloatType add result=" << *ft.add( 2.0f ).value << std::endl;
    std::cout << "FloatType subtract result=" << *ft.subtract( 2.0f ).value << std::endl;
    std::cout << "FloatType multiply result=" << *ft.multiply( 2.0f ).value << std::endl;
    std::cout << "FloatType divide result=" << *ft.divide( 16.0f).value << std::endl << std::endl;

    std::cout << "DoubleType add result=" << *dt.add(2.0).value << std::endl;
    std::cout << "DoubleType subtract result=" << *dt.subtract(2.0).value << std::endl;
    std::cout << "DoubleType multiply result=" << *dt.multiply(2.0).value << std::endl;
    std::cout << "DoubleType divide result=" << *dt.divide(5.f).value << std::endl << std::endl;

    std::cout << "IntType add result=" << *it.add(2).value << std::endl;
    std::cout << "IntType subtract result=" << *it.subtract(2).value << std::endl;
    std::cout << "IntType multiply result=" << *it.multiply(2).value << std::endl;
    std::cout << "IntType divide result=" << *it.divide(3).value << std::endl << std::endl;
    std::cout << "Chain calculation = " << *(it.multiply(1000).divide(2).subtract(10).add(100)).value << std::endl;

        // FloatType object instanciation and method tests
    // --------
    std::cout << "New value of ft = (ft + 3.0f) * 1.5f / 5.0f = " << *ft.add( 3.0f ).multiply(1.5f).divide(5.0f).value << std::endl;
       
    std::cout << "---------------------\n" << std::endl; 
    
    // DoubleType/IntType object instanciation and method tests
    // --------
    std::cout << "Initial value of dt: " << *dt.value << std::endl;
    std::cout << "Initial value of it: " << *it.value << std::endl;
    // --------
    std::cout << "Use of function concatenation (mixed type arguments) " << std::endl;
    std::cout << "New value of dt = (dt * it) / 5.0f + ft = " << *(dt.multiply(it).divide(5.0f).add(ft).value) << std::endl;

    std::cout << "---------------------\n" << std::endl; 
    
    // Intercept division by 0
    // --------
    std::cout << "Intercept division by 0 " << std::endl;
    std::cout << "New value of it = it / 0 = " << *it.divide(0).value << std::endl;
    std::cout << "New value of ft = ft / 0 = " << *ft.divide(0).value << std::endl;
    std::cout << "New value of dt = dt / 0 = " << *dt.divide(0).value << std::endl;

    std::cout << "---------------------\n" << std::endl; 

    std::cout << "good to go!\n";

    return 0;
}
