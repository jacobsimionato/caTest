//
//  mipsInstructionFunctions.h
//  mipsim
//  Computer Architecture Assignment 1 2014
//  Jacob Simionato a1175808

#ifndef __mipsim__mipsInstructionFunctions__
#define __mipsim__mipsInstructionFunctions__

#include <iostream>
#include "mipsInterpreterCore.h"
#include "mipsInterpreter.h"

/*
 ================ Decode Instructions ===============
 Decode different types of instructions into the corresponding parameter struct by extracting bit fields
 */
struct ParamsReg{
    char d;
    char s;
    char t;
};

struct ParamsImm{
    char t;
    char s;
    halfT C;
};

struct ParamsJump{
    wordT C;
};

ParamsImm decodeInstImm(wordT instructionBin);
ParamsJump decodeInstJump(wordT instructionBin);
ParamsReg decodeInstReg(wordT instructionBin);


/*
 ================ Execute Instructions ===============
 Each function emulates a different mips instruction. It is assumed that the opcode / modifier of the instruction binary has already been checked to match the relevant instruction. The  argument fields in the appropriate format are now extracted from the binary value. The state of the machine is represented by the mipsInterpreterCore.
 */
int mips_f_add(MipsInterpreterCore* core, int instructionBin);
int mips_f_addi(MipsInterpreterCore* core, int instructionBin);
int mips_f_slti(MipsInterpreterCore* core, int instructionBin);
int mips_f_slt(MipsInterpreterCore* core, int instructionBin);
int mips_f_beq(MipsInterpreterCore* core, int instructionBin);
int mips_f_bne(MipsInterpreterCore* core, int instructionBin);
int mips_f_j(MipsInterpreterCore* core, int instructionBin);
int mips_f_lw(MipsInterpreterCore* core, int instructionBin);
int mips_f_sw(MipsInterpreterCore* core, int instructionBin);

/*
 ================ Add Instructions To Interpreter ===============
 Constructs MipsIntstructionDef objects and links them to each of the instruction functions defined above. Adds the objects to the MipsInterpreter.
 */

void addInstructionsToInterpreter(MipsInterpreter &interpreter);

#endif /* defined(__mipsim__mipsInstructionFunctions__) */
