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

#include "mipsInterpreter.h"

class MipsInterpreter;

class MipsInstructionDef{
public:
    char name[MAX_NAME_LENGTH];
    int opcode;
    int modifier;
    void (*execute)(MipsInterpreter interpreter, int* args);
    MipsInstructionDef(char* name_input, int opcode_input, int modifier_input, void (*execute_input)(MipsInterpreter interpreter, int* args) );
    void print();
};

#endif /* defined(__mipsim__mipsInstructionDef__) */
