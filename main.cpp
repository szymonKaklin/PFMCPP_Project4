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
     
 
 5) print out the results with some creative couts 
    i.e.
         FloatType ft(0.1f);
         IntType it(3);
         std::cout << "adding 3 and subtracting 'it' from 'ft' results in the following value: " << *ft.add(2.f).subtract( it ).value << std::endl;  //note the dereference of the `value` member of `ft`
 
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
    FloatType( float x ) : heapFloatPtr( new float(x) ) { }
    ~FloatType()
    {
        delete heapFloatPtr;
        heapFloatPtr = nullptr;
    }
    float* heapFloatPtr = nullptr;
    
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
    *heapFloatPtr += x;
    return *this;
}

FloatType& FloatType::subtract( float x )
{
    *heapFloatPtr -= x;
    return *this;
}

FloatType& FloatType::multiply( float x )
{
    *heapFloatPtr *= x;
    return *this;
}

FloatType& FloatType::divide( float x )
{
    if ( x == 0.f )
    {
        std::cout << "Warning! Float division by 0" << std::endl;
    }
    *heapFloatPtr /= x;
    return *this;
}

FloatType& FloatType::add( const FloatType& ft )
{
    return add( *ft.heapFloatPtr );
}

FloatType& FloatType::subtract( const FloatType& ft )
{
    return subtract( *ft.heapFloatPtr );
}

FloatType& FloatType::multiply( const FloatType& ft )
{
    return FloatType::multiply( *ft.heapFloatPtr );
}

FloatType& FloatType::divide( const FloatType& ft )
{
    return divide( *ft.heapFloatPtr );
}

struct IntType
{
    IntType( int x ) : heapIntPtr( new int(x) ) { }
    ~IntType()
    {   
        delete heapIntPtr;
        heapIntPtr = nullptr;
    }
    int* heapIntPtr = nullptr;
    
    IntType& add( int x );
    IntType& subtract( int x );
    IntType& multiply( int x );
    IntType& divide( int x );
};

IntType& IntType::add( int x )
{
    *heapIntPtr += x;
    return *this;
}

IntType& IntType::subtract( int x )
{
    *heapIntPtr -= x;
    return *this;
}

IntType& IntType::multiply( int x )
{
    *heapIntPtr *= x;
    return *this;
}

IntType& IntType::divide( int x )
{
    if ( x == 0 )
    {
        std::cout << "Warning! Int Division by 0 not possible!" << std::endl;
        *heapIntPtr = 0;
        return *this;
    }
    *heapIntPtr /= x;
    return *this;  
}

struct DoubleType
{
    DoubleType( double x ) : heapDoublePtr( new double(x) ) { }
    ~DoubleType()
    {   
        delete heapDoublePtr;
        heapDoublePtr = nullptr;
    }
    double* heapDoublePtr = nullptr;
    
    DoubleType& add( double x );
    DoubleType& subtract( double x );
    DoubleType& multiply( double x );
    DoubleType& divide( double x );
};

DoubleType& DoubleType::add( double x )
{
    *heapDoublePtr += x;
    return *this;
}

DoubleType& DoubleType::subtract( double x )
{
    *heapDoublePtr -= x;
    return *this;
}

DoubleType& DoubleType::multiply( double x )
{
    *heapDoublePtr *= x;
    return *this;
}

DoubleType& DoubleType::divide( double x )
{
    if ( x == 0. )
    {
        std::cout << "Warning! Double division by 0" << std::endl;
    }
    *heapDoublePtr /= x;
    return *this;
}

// Custom UDT Math Functions

FloatType& FloatType::add( const IntType& it )
{
    return add( *it.heapIntPtr );
}

FloatType& FloatType::add( const DoubleType& dt )
{
    return add( *dt.heapDoublePtr );
}

FloatType& FloatType::subtract( const IntType& it )
{
    return subtract( *it.heapIntPtr );
}

FloatType& FloatType::subtract( const DoubleType& dt )
{
    return subtract( *dt.heapDoublePtr );
}

FloatType& FloatType::multiply( const IntType& it )
{
    return multiply( *it.heapIntPtr );
}

FloatType& FloatType::multiply( const DoubleType& dt )
{
    return multiply( *dt.heapDoublePtr );
}

FloatType& FloatType::divide( const IntType& it )
{
    return multiply( *it.heapIntPtr );
}

FloatType& FloatType::divide( const DoubleType& dt )
{
    return divide( *dt.heapDoublePtr );
}

int main()
{
    std::cout << "good to go!\n" << std::endl;
    
    FloatType ft(5.f);
    IntType it(5);
    DoubleType dt(234.352);

    FloatType ft2(2.f);

    std::cout << *ft.add( ft2 ).add( it ).add( dt ).divide( it ).multiply( ft2 ).subtract( ft2 ).subtract( dt ).heapFloatPtr;
    std::cout << "\n";

    // auto resultf = ft.add(1.2f);
    // auto resultf2 = ft.divide(3.2f);
    // auto resultf3 = ft.multiply(5.45f);

    // auto resultChain = ft.add(2.43f).multiply(3.4f);

    // auto resulti = it.multiply(7, 9);
    // auto resulti2 = it.divide(3, 0);
    // auto resulti3 = it.subtract(6, 13);

    // auto resultd = dt.multiply(2, 8);
    // auto resultd2 = dt.divide(7, 5.2);
    // auto resultd3 = dt.divide(6, 0);

    // std::cout << "\nResult of ft.add: " << *ft.heapFloatPtr << std::endl;
    // std::cout << "Result of ft.divide: " << *ft.heapFloatPtr << std::endl;
    // std::cout << "Result of ft.multiply: " << *ft.heapFloatPtr << std::endl;

    std::cout << "Result of ft.add().multiply().subtract().divide(): " << *ft.add(3.2f).multiply(0.84f).subtract(2.53f).divide(2.3f).heapFloatPtr << std::endl;

    std::cout << "Result of it.add().multiply().subtract().divide(): " << *it.add(7).multiply(-3).subtract(-15).divide(3).heapIntPtr << std::endl;

    std::cout << "Result of dt.add().multiply().subtract().divide(): " << *dt.add(5.3).multiply(-2.46).subtract(135.6).divide(-45.6).heapDoublePtr << std::endl;

    // std::cout << "\nResult of it.multiply: " << resulti << std::endl;
    // std::cout << "Result of it.divide: " << resulti2 << std::endl;
    // std::cout << "Result of it.subtract: " << resulti3 << std::endl; 

    // std::cout << "\nResult of dt.multiply: " << resultd << std::endl;
    // std::cout << "Result of dt.divide: " << resultd2 << std::endl; 
    // std::cout << "Result of dt.divide: " << resultd3 << std::endl;
   
}
