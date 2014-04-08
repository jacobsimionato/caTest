//
//  mipsInstructionDef.cpp
//  mipsim
//
//  Created by Jacob Simionato on 30/03/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//
#include <cstring>

#include "mipsInstructionDef.h"

using namespace std;

MipsInstructionDef::MipsInstructionDef(const char* name_input, char opcode_input, char modifier_input, char cpi_input, void (*execute_input)(MipsInterpreterCore* core, int instructionBin) ){
    strncpy(name, name_input, MAX_NAME_LENGTH);
    opcode = opcode_input;
    modifier = modifier_input;
    cpi = cpi_input;
    execute = execute_input;
    numTimesExecuted = 0;
}

void MipsInstructionDef::print(){
    cout << "Instruction: " << name << " ---- ";
    cout << "opcode: " << static_cast<int>(opcode);
    //If opcode is zero, modifier value is relevant
    if(opcode == 0){
        cout << " modifier: " << static_cast<int>(modifier);
    }
    cout << endl;
}

void MipsInstructionDef::printFreq(){
    cout << name << ": " << numTimesExecuted << endl;
}