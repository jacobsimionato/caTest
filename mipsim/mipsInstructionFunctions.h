//
//  mipsInstructionFunctions.h
//  mipsim
//
//  Created by Jacob Simionato on 30/03/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//

#ifndef __mipsim__mipsInstructionFunctions__
#define __mipsim__mipsInstructionFunctions__

#include <iostream>
#include "MipsInterpreterCore.h"

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

void mips_f_add(MipsInterpreterCore* core, int instructionBin);
void mips_f_addi(MipsInterpreterCore* core, int instructionBin);
void mips_f_slti(MipsInterpreterCore* core, int instructionBin);
void mips_f_slt(MipsInterpreterCore* core, int instructionBin);
void mips_f_beq(MipsInterpreterCore* core, int instructionBin);
void mips_f_bne(MipsInterpreterCore* core, int instructionBin);
void mips_f_j(MipsInterpreterCore* core, int instructionBin);
void mips_f_lw(MipsInterpreterCore* core, int instructionBin);
void mips_f_sw(MipsInterpreterCore* core, int instructionBin);

#endif /* defined(__mipsim__mipsInstructionFunctions__) */
