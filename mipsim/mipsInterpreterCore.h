//
//  mipsInterpreterCore.h
//  mipsim
//  Computer Architecture Assignment 1 2014
//  Jacob Simionato a1175808

#ifndef __mipsim__mipsInterpreterCore__
#define __mipsim__mipsInterpreterCore__

#include <iostream>

#include "mipsTypes.h"
#include "memorySystem.h"

#define NUM_GP_REGS 32 //Number of general purpose registers


/*
 ====================== MipsInterpreterCore ======================
 A class which represents the state of a MIPS processor including its registers and a pointer to a memory system. A MIPS instruction need only interact with the Mips interpreter core during execution.
 */
class MipsInterpreterCore{
public:
    //Initializes register values to zero and sets memory system pointer to null
    MipsInterpreterCore(MemorySystemGeneric* memorySystemInst, MemorySystemGeneric* memorySystemData);
    
    //Initializes register values to zero;
    void resetRegs();
    
    //Prints values of registers
    void print();
    
    //Get and set methods for registers
    wordT getRegUns(int regNum);
    void setRegUns(int regNum, wordT val);
    wordST getRegSig(int regNum);
    void setRegSig(int regNum, wordST val);
    wordT getPc();
    void setPc(wordT val);
    
    //Increment PC forwards by this unsigned value
    void incPc(wordT val);
    
    //Relative jump by a distance in byte address represented as a signed long
    void relJumpPc(long val);
    
    //Fetch the instruction from memory at the current PC address
    wordT fetchInstruction();
    
    //Return a pointer to the bound memory system
    MemorySystemGeneric* getMemorySystemInst();
    
    //Word IO from Memory system
    void setWordData(wordT address, wordT data);
    wordT retrieveWordData(wordT address);

private:
    
    wordT m_regPc;
    wordT m_regGp[NUM_GP_REGS];
    
    //Pointer to memory system associated with this core
    MemorySystemGeneric* m_memorySystemInst;
    MemorySystemGeneric* m_memorySystemData;
};

#endif /* defined(__mipsim__mipsInterpreterCore__) */
