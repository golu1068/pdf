
/*
Static variables have a property of preserving their value even after they are out of their scope!
Hence, static variables preserve their previous value in their previous scope and are not initialized again in the new scope. 
// Volatile keyword
Volatile prevents any compiler optimization and says that the value of the object can be changed by something that is beyond 
the control of the program and so that compiler will not make any assumption about the object. Let see an example,

volatile int a;
When the compiler sees the above declaration then it avoids to make any assumption regarding the “a” and in every iteration 
read the value from the address which is assigned to the “a”.

// typedef:
The C language provides a very important keyword typedef for defining a new name for existing types.
 The typedef is the compiler directive mainly use with user-defined data types (structure, union or enum) to reduce their complexity and
  increase code readability and portability.

// Enum
An enum in C is a user-defined data type. It consists set of named constant integers. Using the enum keyword, we can declare 
an enumeration type by using the enumeration tag (optional) and a list of named integer.

//// structure padding
In the case of structure or union, the compiler inserts some extra bytes between the members of structure or union for
 the alignment, these extra unused bytes are called padding bytes and this technique is called padding.

Padding has increased the performance of the processor at the penalty of memory. In structure or union data members aligned 
as per the size of the highest bytes member to prevent the penalty of performance.

Big-endian
The most significant byte of data stored at the lowest memory address.

Little-endian
The least significant byte of data stored at the lowest memory address.

// Single precision
1  8  23
// double precision
1  11 52

// Union
Allows to store different data types in the same memory location. 
It means a single variable, i.e., same memory location, can be used to store multiple types of data. 

*/

#include <stdio.h>
#include <inttypes.h>
int main()
{
    //char mesg[]="nagenkjbck";
    char *mesg[] = {"nag","kum"};
    int x = -15;
    x = x >> 1;
    printf("%d\n", x);
}