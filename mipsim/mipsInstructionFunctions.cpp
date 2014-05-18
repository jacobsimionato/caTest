//
//  mipsInstructionFunctions.cpp
//  mipsim
//  Computer Architecture Assignment 1 2014
//  Jacob Simionato a1175808

#include "mipsInstructionFunctions.h"
#include <math.h>

#define BITMASK_5 31
#define BITMASK_16 65535
#define BITMASK_26 67108863

using namespace std;



/*
 ================ Decode Instructions ===============
 Decode different types of instructions into the corresponding parameter struct by extracting bit fields
 Returns the number of cycles that is needed by the instruction to complete
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
int mips_f_add(MipsInterpreterCore* core, int instructionBin){
    ParamsReg params = decodeInstReg(instructionBin);
    wordST result = core->getRegSig(params.s) + core->getRegSig(params.t);
    core->setRegSig(params.d, result);
    return 4;
}

/*
 addi
 */
int mips_f_addi(MipsInterpreterCore* core, int instructionBin){
    ParamsImm params = decodeInstImm(instructionBin);
    wordT result = core->getRegSig(params.s) + static_cast<halfST>(params.C);
    core->setRegSig(params.t, result);
    return 4;
}

/*
 slti
 */
int mips_f_slti(MipsInterpreterCore* core, int instructionBin){
    ParamsImm params = decodeInstImm(instructionBin);
    wordT result;
    if(core->getRegSig(params.s) < static_cast<halfST>(params.C)){
        result = 1;
    }else{
        result = 0;
    }
    core->setRegSig(params.t, result);
    return 4;
}

/*
 slt
 */
int mips_f_slt(MipsInterpreterCore* core, int instructionBin){
    ParamsReg params = decodeInstReg(instructionBin);
    wordT result;
    if(core->getRegSig(params.s) < core->getRegSig(params.t)){
        result = 1;
    }else{
        result = 0;
    }
    core->setRegSig(params.d, result);
    return 4;
}

/*
 beq
 */
int mips_f_beq(MipsInterpreterCore* core, int instructionBin){
    ParamsImm params = decodeInstImm(instructionBin);
    if(core->getRegUns(params.s) == core->getRegUns(params.t)){
        //Interpret offset as signed 16 bit integer
        halfST jumpOffsetWords = static_cast<halfST>(params.C);
        //Multiply word address by 4 to obtain byte address
        long jumpOffsetBytes = jumpOffsetWords * 4;
        core->relJumpPc(jumpOffsetBytes);
    }
    return 3;
}

/*
 bne
 */
int mips_f_bne(MipsInterpreterCore* core, int instructionBin){
    ParamsImm params = decodeInstImm(instructionBin);
    if(core->getRegUns(params.s) != core->getRegUns(params.t)){
        //Interpret offset as signed 16 bit integer
        halfST jumpOffsetWords = static_cast<halfST>(params.C);
        //Multiply word address by 4 to obtain byte address
        long jumpOffsetBytes = jumpOffsetWords * 4;
        core->relJumpPc(jumpOffsetBytes);
    }
    return 3;
}

/*
 j
 */
int mips_f_j(MipsInterpreterCore* core, int instructionBin){
    ParamsJump params = decodeInstJump(instructionBin);
    
    wordT lower28bits = params.C * 4;
    wordT curPc = core->getPc();
    curPc = curPc & 0xF0000000;
    curPc = curPc | lower28bits;
    core->setPc(curPc - 4);
    return 2;
}

/*
 lw
 */
int mips_f_lw(MipsInterpreterCore* core, int instructionBin){
    ParamsImm params = decodeInstImm(instructionBin);
    wordT address = core->getRegUns(params.s) + static_cast<halfST>(params.C);
    wordT data = core->retrieveWordData(address);
    core->setRegUns(params.t, data);
    return 5;
}

/*
 sw
 */
int mips_f_sw(MipsInterpreterCore* core, int instructionBin){
    ParamsImm params = decodeInstImm(instructionBin);
    wordT address = core->getRegUns(params.s) + static_cast<halfST>(params.C);
    wordT data = core->getRegUns(params.t);
    core->setWordData(address, data);
    return 4;
}


/*
 ================ Add Instructions To Interpreter ===============
 Constructs MipsIntstructionDef objects and links them to each of the instruction functions defined above. Adds the objects to the MipsInterpreter.
 */
void addInstructionsToInterpreter(MipsInterpreter &interpreter){
    /*
     The attributes of the instructions are packaged with one of the functions above by adding a function pointer to the MipsInstructionDef object.
     */
    interpreter.addInstructionDef(MipsInstructionDef("add", 0, 32, mips_f_add));
    interpreter.addInstructionDef(MipsInstructionDef("addi", 8, 0, mips_f_addi));
    interpreter.addInstructionDef(MipsInstructionDef("slti", 10, 0, mips_f_slti));
    interpreter.addInstructionDef(MipsInstructionDef("slt", 0, 42, mips_f_slt));
    interpreter.addInstructionDef(MipsInstructionDef("beq", 4, 0, mips_f_beq));
    interpreter.addInstructionDef(MipsInstructionDef("bne", 5, 0, mips_f_bne));
    interpreter.addInstructionDef(MipsInstructionDef("j", 2, 0, mips_f_j));
    interpreter.addInstructionDef(MipsInstructionDef("lw", 35, 0, mips_f_lw));
    interpreter.addInstructionDef(MipsInstructionDef("sw", 43, 0, mips_f_sw));
}
