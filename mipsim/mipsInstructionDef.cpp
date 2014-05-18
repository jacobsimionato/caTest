//
//  mipsInstructionDef.cpp
//  mipsim
//  Computer Architecture Assignment 1 2014
//  Jacob Simionato a1175808

#include <cstring>

#include "mipsInstructionDef.h"

using namespace std;

/*
 ======== Constructor ========
 Requires values with which to initialize the attributes of the InstructionDef, including a pointer to a function which executes the instruction
 */
MipsInstructionDef::MipsInstructionDef(const char* name_input, char opcode_input, char modifier_input, char cpi_input, void (*execute_input)(MipsInterpreterCore* core, int instructionBin) ){
    strncpy(name, name_input, MAX_NAME_LENGTH);
    opcode = opcode_input;
    modifier = modifier_input;
    cpi = cpi_input;
    execute = execute_input;
    numTimesExecuted = 0;
}

/*
 ======== void print() ========
 Prints a summary of the instructionDef's attributes
 */
void MipsInstructionDef::print(){
    cout << "Instruction: " << name << " ---- ";
    cout << "opcode: " << static_cast<int>(opcode);
    //If opcode is zero, modifier value is relevant
    if(opcode == 0){
        cout << " modifier: " << static_cast<int>(modifier);
    }
    cout << endl;
}


/*
 ======== void printFreq() ========
 Prints the name and number of times the instruction has been executed
 */
void MipsInstructionDef::printFreq(){
    cout << name << ": " << numTimesExecuted << endl;
}