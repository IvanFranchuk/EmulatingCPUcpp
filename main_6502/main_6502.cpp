#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using Byte = unsigned char;
using Word = unsigned short;

using u32 = unsigned int;

struct Mem {
    static constexpr u32 MAX_MEM = 1024 * 64;
    Byte Data[MAX_MEM];

    void Initialise() {
        for (u32 i = 0; i < MAX_MEM; i++) {
            Data[i] = 0;
        }
    }

    // read 1 byte 
    Byte operator[](u32 Address) const {
        //assert here Address is < MAX_MEM
        return Data[Address];
    }

    // write 1 byte 
    Byte& operator[](u32 Address) {
        //assert here Address is < MAX_MEM
        return Data[Address];
    }
};

struct CPU
{
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

    void Reset( Mem& memory ) {
        PC = 0xFFFC;
        SP = 0x0100;
        C = Z = I = D = B = V = N = 0;
        A = X = Y = 0;
        memory.Initialise();
    }

    Byte FetchByte(u32& Cycles, Mem& memory) {
        Byte Data = memory[PC];
        PC++;
        Cycles--;
        return Data;
    }

    Byte ReadByte(u32& Cycles, Mem& memory) {
        Byte Data = memory[PC];
        Cycles--;
        return Data;
    }

    // opcodes
    static constexpr Byte
        INS_LDA_IM = 0xA9,
        INS_LDA_ZP = 0xA5;

    void Execute( u32 Cycles, Mem& memory) {
        while (Cycles > 0) {
            Byte Ins = FetchByte(Cycles, memory);
            switch ( Ins )
            {
            case INS_LDA_IM:
            {
                Byte Value = FetchByte(Cycles, memory);
                A = Value;
                Z = (A == 0);
                N = (A & 0b10000000) > 0;
            }break;
            case INS_LDA_ZP: {
                Byte ZeroPageAddress = FetchByte(Cycles, memory);

            }break; 
            default: {
                printf("INstruction not handled %d", Ins);
            }break;
            }
        }
    }
};

int main()
{
    Mem mem;
    CPU cpu;
    cpu.Reset( mem );
    // start - inline a little program
    mem[0xFFFC] = CPU::INS_LDA_IM;
    mem[0xFFFC] = 0x42;
    //end - inline a little program
    cpu.Execute( 2,  mem );
    return 0;
}
