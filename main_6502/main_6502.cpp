#include <iostream>
#include <stdio.h>
#include <stdlib.h>



struct CPU
{
    using Byte = unsigned char;
    using Word = unsigned short;

    Word PC;    //program counter
    Word SP;    //stack pointer

    Byte A, X, Y;   //registers

    // processor status
    Byte C : 1; // carry flag
    Byte Z : 1; // zero flag
    Byte I : 1; // interrupt disable
    Byte D : 1; // decimal mode
    Byte B : 1; // break command
    Byte V : 1; // overflow flag
    Byte N : 1; // negative flag
};

int main()
{
    std::cout << "Hello World!\n";
}
