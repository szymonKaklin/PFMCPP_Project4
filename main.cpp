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
 1) Edit your 3 structs so that they own a heap-allocated primitive type without using smart pointers  
         IntType should own a heap-allocated int, for example.
 
 2) give it a constructor that takes the appropriate primitive
    this argument will initialize the owned primitive's valuePtr.
         i.e. if you're owning an int on the heap, your ctor argument will initialize that heap-allocated int's valuePtr.
 
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
     
 
 5) print out the results with some creative couts 
    i.e.
         FloatType ft(0.1f);
         IntType it(3);
         std::cout << "adding 3 and subtracting 'it' from 'ft' results in the following valuePtr: " << *ft.add(2.f).subtract( it ).valuePtr << std::endl;  //note the dereference of the `valuePtr` member of `ft`
 
 6) Don't let your heap-allocated owned type leak!
 
 7) click the [run] button.  Clear up any errors or warnings as best you can.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 */
struct IntType;
struct DoubleType;
struct FloatType
{
    FloatType( float x ) : valuePtr( new float(x) ) { }
    ~FloatType()
    {
        delete valuePtr;
        valuePtr = nullptr;
    }
    float* valuePtr = nullptr;
    
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
    *valuePtr += x;
    return *this;
}

FloatType& FloatType::subtract( float x )
{
    *valuePtr -= x;
    return *this;
}

FloatType& FloatType::multiply( float x )
{
    *valuePtr *= x;
    return *this;
}

FloatType& FloatType::divide( float x )
{
    if ( x == 0.f )
    {
        std::cout << "Warning! Float division by 0" << std::endl;
    }
    *valuePtr /= x;
    return *this;
}

FloatType& FloatType::add( const FloatType& ft )
{
    return add( *ft.valuePtr );
}

FloatType& FloatType::subtract( const FloatType& ft )
{
    return subtract( *ft.valuePtr );
}

FloatType& FloatType::multiply( const FloatType& ft )
{
    return FloatType::multiply( *ft.valuePtr );
}

FloatType& FloatType::divide( const FloatType& ft )
{
    return divide( *ft.valuePtr );
}

struct IntType
{
    IntType( int x ) : valuePtr( new int(x) ) { }
    ~IntType()
    {   
        delete valuePtr;
        valuePtr = nullptr;
    }
    int* valuePtr = nullptr;
    
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
    *valuePtr += x;
    return *this;
}

IntType& IntType::subtract( int x )
{
    *valuePtr -= x;
    return *this;
}

IntType& IntType::multiply( int x )
{
    *valuePtr *= x;
    return *this;
}

IntType& IntType::divide( int x )
{
    if ( x == 0 )
    {
        std::cout << "Warning! Int Division by 0 not possible!" << std::endl;
        *valuePtr = 0;
        return *this;
    }
    *valuePtr /= x;
    return *this;  
}

IntType& IntType::add( const IntType& it )
{
    return add( *it.valuePtr );
}

IntType& IntType::subtract( const IntType& it )
{
    return subtract( *it.valuePtr );
}

IntType& IntType::multiply( const IntType& it )
{
    return multiply( *it.valuePtr );
}

IntType& IntType::divide( const IntType& it )
{
    return divide( *it.valuePtr );
}

struct DoubleType
{
    DoubleType( double x ) : valuePtr( new double(x) ) { }
    ~DoubleType()
    {   
        delete valuePtr;
        valuePtr = nullptr;
    }
    double* valuePtr = nullptr;
    
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
    *valuePtr += x;
    return *this;
}

DoubleType& DoubleType::subtract( double x )
{
    *valuePtr -= x;
    return *this;
}

DoubleType& DoubleType::multiply( double x )
{
    *valuePtr *= x;
    return *this;
}

DoubleType& DoubleType::divide( double x )
{
    if ( x == 0. )
    {
        std::cout << "Warning! Double division by 0" << std::endl;
    }
    *valuePtr /= x;
    return *this;
}

DoubleType& DoubleType::add( const DoubleType& dt )
{
    return add( *dt.valuePtr );
}

DoubleType& DoubleType::subtract( const DoubleType& dt )
{
    return subtract( *dt.valuePtr );
}

DoubleType& DoubleType::multiply( const DoubleType& dt )
{
    return multiply( *dt.valuePtr );
}

DoubleType& DoubleType::divide( const DoubleType& dt )
{
    return divide( *dt.valuePtr );
}

// Custom UDT Math Functions
// FloatType

FloatType& FloatType::add( const IntType& it )
{
    return add( *it.valuePtr );
}

FloatType& FloatType::add( const DoubleType& dt )
{
    return add( *dt.valuePtr );
}

FloatType& FloatType::subtract( const IntType& it )
{
    return subtract( *it.valuePtr );
}

FloatType& FloatType::subtract( const DoubleType& dt )
{
    return subtract( *dt.valuePtr );
}

FloatType& FloatType::multiply( const IntType& it )
{
    return multiply( *it.valuePtr );
}

FloatType& FloatType::multiply( const DoubleType& dt )
{
    return multiply( *dt.valuePtr );
}

FloatType& FloatType::divide( const IntType& it )
{
    return multiply( *it.valuePtr );
}

FloatType& FloatType::divide( const DoubleType& dt )
{
    return divide( *dt.valuePtr );
}

// IntType
IntType& IntType::add( const FloatType& ft )
{
    return add( *ft.valuePtr );
}

IntType& IntType::add( const DoubleType& dt )
{
    return add( *dt.valuePtr );
}

IntType& IntType::subtract( const FloatType& ft )
{
    return subtract( *ft.valuePtr );
}

IntType& IntType::subtract( const DoubleType& dt )
{
    return subtract( *dt.valuePtr );
}

IntType& IntType::multiply( const FloatType& ft )
{
    return multiply( *ft.valuePtr );
}

IntType& IntType::multiply( const DoubleType& dt )
{
    return multiply( *dt.valuePtr );
}

IntType& IntType::divide( const FloatType& ft )
{
    return multiply( *ft.valuePtr );
}

IntType& IntType::divide( const DoubleType& dt )
{
    return divide( *dt.valuePtr );
}

// DoubleType
DoubleType& DoubleType::add( const FloatType& ft )
{
    return add( *ft.valuePtr );
}

DoubleType& DoubleType::add( const IntType& it )
{
    return add( *it.valuePtr );
}

DoubleType& DoubleType::subtract( const FloatType& ft )
{
    return subtract( *ft.valuePtr );
}

DoubleType& DoubleType::subtract( const IntType& it )
{
    return subtract( *it.valuePtr );
}

DoubleType& DoubleType::multiply( const FloatType& ft )
{
    return multiply( *ft.valuePtr );
}

DoubleType& DoubleType::multiply( const IntType& it )
{
    return multiply( *it.valuePtr );
}

DoubleType& DoubleType::divide( const FloatType& ft )
{
    return multiply( *ft.valuePtr );
}

DoubleType& DoubleType::divide( const IntType& it )
{
    return divide( *it.valuePtr );
}

int main()
{
    std::cout << "good to go!\n" << std::endl;

    FloatType ft(0.1f);
    IntType it(3);
    DoubleType dt(2.4);
    
    std::cout << "Multiplying ft, it, and dt together gives: " << *ft.multiply( it ).multiply( dt ).valuePtr << std::endl;

    std::cout << "\n";

    std::cout << "Float: adding 2 to ft, subtracting 'it', and adding 'dt' results in: " << *ft.add(2.f).subtract( it ).add( dt ).valuePtr << std::endl;

    std::cout << "\n";
 
    std::cout << "Integer: adding ft to it, subtracting 3, dividing by ft, and multiplying by dt, results in: " << *it.add( ft ).subtract(3).divide( ft ).multiply( dt ).valuePtr << std::endl;

    std::cout << "\n";

    std::cout << "Double: subtracting ft from dt, multiplying by it, dividing by 3, adding 13, multiplying by 2.32 results in:  " << *dt.subtract( ft ).multiply( it ).divide( 3 ).add(13).multiply(2.32).valuePtr << std::endl;

    std::cout << "\n";

    std::cout << "Multiplying ft, it, and dt together gives: " << *ft.multiply( it ).multiply( dt ).valuePtr << std::endl;
}
