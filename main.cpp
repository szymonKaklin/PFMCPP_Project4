
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

struct HeapA;
struct A
{ 
    A( HeapA& heapA_ ) : heapA( heapA_ ) { }
    HeapA& heapA;
};

struct AWrapper
{
    AWrapper( A* ptr ) : pointerToA( ptr ) { }
    ~AWrapper()
    {
        delete pointerToA;
    }
    A* pointerToA = nullptr;
};

// Thi is a struct named 'HeapA' which owns an instance of 'A' , which is created on the heap via the AWrapper struct so that deletion of pointer is taken care of
struct HeapA
{
    HeapA() : a( new A( *this ) ) { }
    AWrapper a;
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






struct FloatType
{
    float add( float lhs, float rhs );
    float subtract( float lhs, float rhs );
    float multiply( float lhs, float rhs );
    float divide( float lhs, float rhs );
};

float FloatType::add( float lhs, float rhs)
{
    return lhs + rhs;
}

float FloatType::subtract( float lhs, float rhs)
{
    return lhs - rhs;
}

float FloatType::multiply( float lhs, float rhs)
{
    return lhs * rhs;
}

float FloatType::divide( float lhs, float rhs)
{
    if (std::abs(rhs - 0.0f) < 0.0000000001f )
    {
        std::cout << "Warning! Float division by 0" << std::endl;
    }
    return lhs / rhs;
}

struct IntType
{
    int add( int lhs, int rhs );
    int subtract( int lhs, int rhs );
    int multiply( int lhs, int rhs );
    int divide( int lhs, int rhs );
};

int IntType::add(int lhs, int rhs)
{
    return lhs + rhs;
}

int IntType::subtract(int lhs, int rhs)
{
    return lhs - rhs;
}

int IntType::multiply(int lhs, int rhs)
{
    return lhs * rhs;
}

int IntType::divide(int lhs, int rhs)
{
    if ( rhs == 0 )
    {
        std::cout << "Warning! Int Division by 0 not possible!" << std::endl;
        return 0;
    }
    return lhs / rhs;  
}

struct DoubleType
{
    double add( double lhs, double rhs );
    double subtract( double lhs, double rhs );
    double multiply( double lhs, double rhs );
    double divide( double lhs, double rhs );
};

double DoubleType::add(double lhs, double rhs)
{
    return lhs + rhs;
}

double DoubleType::subtract(double lhs, double rhs)
{
    return lhs - rhs;
}

double DoubleType::multiply(double lhs, double rhs)
{
    return lhs * rhs;
}

double DoubleType::divide(double lhs, double rhs)
{
    if (std::abs(rhs - 0) < 0.0000000001 )
    {
        std::cout << "Warning! Double division by 0" << std::endl;
    }
    return lhs / rhs;
}




int main()
{
    std::cout << "good to go!\n" << std::endl;
    
    FloatType ft;
    IntType it;
    DoubleType dt;

    auto resultf = ft.add(3.2f, 2.3f);
    auto resultf2 = ft.divide(5.3f, 0.0f);
    auto resultf3 = ft.multiply(18.233f, 42.541f);

    auto resulti = it.multiply(7, 9);
    auto resulti2 = it.divide(3, 0);
    auto resulti3 = it.subtract(6, 13);

    auto resultd = dt.multiply(2, 8);
    auto resultd2 = dt.divide(7, 5.2);
    auto resultd3 = dt.divide(6, 0);

    std::cout << "\nResult of ft.add: " << resultf << std::endl;
    std::cout << "Result of ft.divide: " << resultf2 << std::endl;
    std::cout << "Result of ft.multiply: " << resultf3 << std::endl;

    std::cout << "\nResult of it.multiply: " << resulti << std::endl;
    std::cout << "Result of it.divide: " << resulti2 << std::endl;
    std::cout << "Result of it.subtract: " << resulti3 << std::endl; 

    std::cout << "\nResult of dt.multiply: " << resultd << std::endl;
    std::cout << "Result of dt.divide: " << resultd2 << std::endl; 
    std::cout << "Result of dt.divide: " << resultd3 << std::endl;
   
}
