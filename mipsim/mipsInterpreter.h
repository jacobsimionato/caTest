//
//  mipsInterpreter.h
//  mipsim
//
//  Created by Jacob Simionato on 30/03/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//

#ifndef __mipsim__mipsInterpreter__
#define __mipsim__mipsInterpreter__

#include <iostream>
#include <vector>
#include <map>

#include "mipsTypes.h"
#include "mipsInstructionDef.h"
#include "mipsInterpreterCore.h"

class MipsInstructionDef;

class MipsInterpreter{
public:
    MipsInterpreter(MemorySystemGeneric* memorySystem);
    int fetchAndInterpret(int num = 0);
    int interpret(wordT instructionBin);
    void addInstructionDef(MipsInstructionDef instructionDef);
    void printInstructionDefs();
    void printRegisters();
    void printStats();
    MipsInterpreterCore* getCore();
    void setVerbose(bool val);
private:
    MipsInterpreterCore m_interpreterCore;
    
    bool m_verbose;
    
    int m_cycleCount;
    int m_instrCount;
    
    int genKeyFromInstruction(wordT instructionBin);

    
    std::map<int, MipsInstructionDef> m_instructionDefs;
};


//Adds instruction definitions to the interpreter
void addInstructionsToInterpreter(MipsInterpreter &interpreter);

#endif /* defined(__mipsim__mipsInterpreter__) */
