//
//  mipsInstructionFunctions.cpp
//  mipsim
//
//  Created by Jacob Simionato on 30/03/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//

#include "mipsInstructionFunctions.h"
#include <math.h>

#define BITMASK_5 31
#define BITMASK_16 65535
#define BITMASK_26 67108863

using namespace std;

/*
 Instruction decode functions extract the bit fields from each instruction
 Each parameter field is saved as an integer into the destination array in the order they appear in the binary number from most significant to least significant section
 */

/*
 Decode different types of instructions in the corresponding parameter struct by extracting bit fields
 */
ParamsImm decodeInstImm(wordT instructionBin){
    ParamsImm params;
    params.s = (instructionBin >> 21) & BITMASK_5;
    params.t = (instructionBin >> 16) & BITMASK_5;
    params.C = instructionBin & BITMASK_16;
    return params;
}

ParamsJump decodeInstJump(wordT instructionBin){
    ParamsJump params;
    params.C = instructionBin & BITMASK_26;
    return params;
}

ParamsReg decodeInstReg(wordT instructionBin){
    ParamsReg params;
    params.s = (instructionBin >> 21) & BITMASK_5;
    params.t = (instructionBin >> 16) & BITMASK_5;
    params.d = (instructionBin >> 11) & BITMASK_5;
    return params;
}


/*
 add
 */
void mips_f_add(MipsInterpreterCore* core, int instructionBin){
    ParamsReg params = decodeInstReg(instructionBin);
    wordST result = core->getRegSig(params.s) + core->getRegSig(params.t);
    core->setRegSig(params.d, result);
}

/*
 addi
 */
void mips_f_addi(MipsInterpreterCore* core, int instructionBin){
    ParamsImm params = decodeInstImm(instructionBin);
    wordT result = core->getRegSig(params.s) + static_cast<halfST>(params.C);
    core->setRegSig(params.t, result);
}

/*
 slti
 */
void mips_f_slti(MipsInterpreterCore* core, int instructionBin){
    ParamsImm params = decodeInstImm(instructionBin);
    wordT result;
    if(core->getRegSig(params.s) < static_cast<halfST>(params.C)){
        result = 1;
    }else{
        result = 0;
    }
    core->setRegSig(params.t, result);
}

/*
 slt
 */
void mips_f_slt(MipsInterpreterCore* core, int instructionBin){
    ParamsReg params = decodeInstReg(instructionBin);
    wordT result;
    if(core->getRegSig(params.s) < core->getRegSig(params.t)){
        result = 1;
    }else{
        result = 0;
    }
    core->setRegSig(params.d, result);
}


void mips_f_beq(MipsInterpreterCore* core, int instructionBin){
    ParamsImm params = decodeInstImm(instructionBin);
    if(core->getRegUns(params.s) == core->getRegUns(params.t)){
        //Interpret offset as signed 16 bit integer
        halfST jumpOffsetWords = static_cast<halfST>(params.C);
        //Multiply word address by 4 to obtain byte address
        long jumpOffsetBytes = jumpOffsetWords * 4;
        core->relJumpPc(jumpOffsetBytes);
    }
}


void mips_f_bne(MipsInterpreterCore* core, int instructionBin){
    ParamsImm params = decodeInstImm(instructionBin);
    if(core->getRegUns(params.s) != core->getRegUns(params.t)){
        //Interpret offset as signed 16 bit integer
        halfST jumpOffsetWords = static_cast<halfST>(params.C);
        //Multiply word address by 4 to obtain byte address
        long jumpOffsetBytes = jumpOffsetWords * 4;
        core->relJumpPc(jumpOffsetBytes);
    }
}


void mips_f_j(MipsInterpreterCore* core, int instructionBin){
    ParamsJump params = decodeInstJump(instructionBin);
    
    wordT lower28bits = params.C * 4;
    wordT curPc = core->getPc();
    curPc = curPc & 0xF0000000;
    curPc = curPc | lower28bits;
    //cout << "jumpOffsetBytes: " << jumpOffsetBytes << endl;
    core->setPc(curPc - 4);
}


void mips_f_lw(MipsInterpreterCore* core, int instructionBin){
    ParamsImm params = decodeInstImm(instructionBin);
    wordT address = core->getRegUns(params.s) + static_cast<halfST>(params.C);
    wordT data = core->getMemorySystem()->retrieveWord(address);
    core->setRegUns(params.t, data);
}


void mips_f_sw(MipsInterpreterCore* core, int instructionBin){
    ParamsImm params = decodeInstImm(instructionBin);
    wordT address = core->getRegUns(params.s) + static_cast<halfST>(params.C);
    wordT data = core->getRegUns(params.t);
    core->getMemorySystem()->setWord(address, data);
}

