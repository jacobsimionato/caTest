//
//  mipsInstructionDef.h
//  mipsim
//  Computer Architecture Assignment 1 2014
//  Jacob Simionato a1175808

#ifndef __mipsim__mipsInstructionDef__
#define __mipsim__mipsInstructionDef__

#define MAX_NAME_LENGTH 40

#include <iostream>

#include "mipsInterpreterCore.h"

class MipsInterpreter;

/*
 ====================== MipsInstructionDef ======================
 Instances of MipsInstructionDef each represent a type of MIPS instruction (eg add, sw, beq) and can be aggregated to create a working system with functional and analystical features.
 */

class MipsInstructionDef{
public:
    //Human-readable name used for reporting
    char name[MAX_NAME_LENGTH];
    
    //Opcode stored as a single 8-bit value
    char opcode;
    
    //Modifier - should be set to zero if there is no modifier
    char modifier;
    
    //CPI value for instruction - used for statistical reports
    char cpi;
    
    //Tracks number of times instruction has been executed
    int numTimesExecuted;
    
    //Pointer to 'execute' function which takes the instruction binary and an interpreterCore reference and carries out the instruction by changing the state of the interpreterCore and associated memorySystem
    int (*execute)(MipsInterpreterCore* core, int instructionBin);
    
    //Constructor requires values with which to initialize the attributes of the InstructionDef, including a pointer to a function which executes the instruction
    MipsInstructionDef(const char* name_input, char opcode_input, char modifier_input, int (*execute_input)(MipsInterpreterCore* core, int instructionBin) );
    
    //Prints all of the attributes of the object including name, opcode, modifier, cpi
    void print();
    
    //Prints only the frequency in the required format
    void printFreq();
};

#endif /* defined(__mipsim__mipsInstructionDef__) */
