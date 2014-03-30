//
//  mipsInstructionDef.h
//  mipsim
//
//  Created by Jacob Simionato on 30/03/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//

#ifndef __mipsim__mipsInstructionDef__
#define __mipsim__mipsInstructionDef__

#define MAX_NAME_LENGTH 40

#include <iostream>

#include "mipsInterpreterCore.h"

class MipsInterpreter;

class MipsInstructionDef{
public:
    char name[MAX_NAME_LENGTH];
    char opcode;
    char modifier;
    char cpi;
    int numTimesExecuted;
    void (*execute)(MipsInterpreterCore* core, int args);
    MipsInstructionDef(const char* name_input, char opcode_input, char modifier_input, char cpi_input, void (*execute_input)(MipsInterpreterCore* core, int instructionBin) );
    //Prints all of the attributes of the object including name, opcode, modifier, cpi
    void print();
    //Prints only the frequency in the required format
    void printFreq();
};

#endif /* defined(__mipsim__mipsInstructionDef__) */
