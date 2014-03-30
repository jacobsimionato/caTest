//
//  mipsInstructionDef.cpp
//  mipsim
//
//  Created by Jacob Simionato on 30/03/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//

#include "mipsInstructionDef.h"

using namespace std;

MipsInstructionDef::MipsInstructionDef(char* name_input, int opcode_input, int modifier_input, void (*execute_input)(MipsInterpreter interpreter, int* args) ){
    strncpy(name, name_input, MAX_NAME_LENGTH);
    opcode = opcode_input;
    modifier = modifier_input;
    execute = execute_input;
}

void MipsInstructionDef::print(){
    cout << "Instruction: " << name << " ---- ";
    cout << "opcode: " << opcode;
    //If opcode is zero, modifier value is relevant
    if(opcode == 0){
        cout << " modifier: " << modifier;
    }
}