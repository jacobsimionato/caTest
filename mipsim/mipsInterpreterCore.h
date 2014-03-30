//
//  mipsInterpreterCore.h
//  mipsim
//
//  Created by Jacob Simionato on 30/03/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//

#ifndef __mipsim__mipsInterpreterCore__
#define __mipsim__mipsInterpreterCore__

#include <iostream>

#include "mipsTypes.h"
#include "memorySystem.h"

#define NUM_GP_REGS 32 //Number of general purpose registers

class MipsInterpreterCore{
public:
    //Initializes register values to zero and sets memory system pointer to null
    MipsInterpreterCore(MemorySystemGeneric* memorySystem);
    
    //Initializes register values to zero;
    void resetRegs();
    wordT getRegUns(int regNum);
    void setRegUns(int regNum, wordT val);
    wordST getRegSig(int regNum);
    void setRegSig(int regNum, wordST val);
    wordT getPc();
    void setPc(wordT val);
    void incPc(wordT val);
    wordT fetchInstruction();
    MemorySystemGeneric* getMemorySystem();
    
    //Prints values of registers
    void print();
private:
    
    wordT m_regPc;
    wordT m_regGp[NUM_GP_REGS];
    
    //Pointer to memory system associated with this core
    MemorySystemGeneric* m_memorySystem;
};

#endif /* defined(__mipsim__mipsInterpreterCore__) */
