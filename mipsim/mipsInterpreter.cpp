//
//  mipsInterpreter.cpp
//  mipsim
//
//  Created by Jacob Simionato on 30/03/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//
#include <iomanip>

#include "mipsInterpreter.h"
#include "mipsInstructionFunctions.h"


using namespace std;

MipsInterpreter::MipsInterpreter(MemorySystemGeneric* memorySystem): m_interpreterCore(memorySystem){
    m_instrCount = 0;
    m_cycleCount = 0;
    
    m_verbose = false;
}

int MipsInterpreter::fetchAndInterpret(int num){
    int result;
    for(int i = 0; i < num; i++){
        wordT instruction = m_interpreterCore.fetchInstruction();
        result = interpret(instruction);
        //If there is an error whilst interpreting
        if(result != 0){
            return result;
        }
    }
    return 0;
}

int MipsInterpreter::interpret(wordT instructionBin){
    int key = genKeyFromInstruction(instructionBin);
    MipsInstructionDef* instructionDef = &m_instructionDefs.at(key);
    
    instructionDef->execute(&m_interpreterCore, instructionBin);
    instructionDef->numTimesExecuted++;
    
    m_interpreterCore.incPc(4);
    m_cycleCount += instructionDef->cpi;
    m_instrCount++;
    
    if(m_verbose){
        cout << "MipsInterpreter: Executing " << instructionDef->name << endl;
    }
    
    return 0;
}

void MipsInterpreter::addInstructionDef(MipsInstructionDef instructionDef){
    //Create key by placing opcode in more significant position than modifier
    int key = (instructionDef.opcode << 6) + instructionDef.modifier;
    m_instructionDefs.insert(pair<int,MipsInstructionDef>(key,instructionDef));
}


void MipsInterpreter::printInstructionDefs(){
    cout << "MipsInterpreter: Printing Instruction Defs" << endl;
    map<int, MipsInstructionDef>::iterator iter;
    for (iter = m_instructionDefs.begin(); iter != m_instructionDefs.end(); ++iter){
        cout << "Key: " << iter->first << " : ";
        iter->second.print();
    }
    cout << endl;
}

void MipsInterpreter::printRegisters(){
    m_interpreterCore.print();
}

void MipsInterpreter::printStats(){
    cout << dec;
    //Uses the search keys of the map to print the frequency report for each instruction in the required order
    int instructionReportOrder[9] = {32, 512, 42, 640, 256, 320, 2240, 2752, 128};
    for(int i = 0; i < sizeof(instructionReportOrder)/sizeof(int); i++){
        m_instructionDefs.at(instructionReportOrder[i]).printFreq();
    }
    
    //Print the other statistics
    cout << "Instruction count: " << m_instrCount << endl;
    cout << "Cycle count: " << m_cycleCount << endl;
    //Print CPI if instructions have been executed
    if(m_instrCount != 0){
        double avCpi = static_cast<double>(m_cycleCount) / static_cast<double>(m_instrCount);
        cout << "Average CPI: " << std::fixed << std::setprecision(4) << avCpi << endl;
    }
}

MipsInterpreterCore* MipsInterpreter::getCore(){
    return &m_interpreterCore;
}

void MipsInterpreter::setVerbose(bool val){
    m_verbose = val;
}

int MipsInterpreter::genKeyFromInstruction(wordT instructionBin){
    int opcode = (instructionBin >> 26) & 63;
    //If the opcode is zero, then include the modifier in the key
    if(opcode == 0){
        int modifier = instructionBin & 63;
        return (opcode << 6) + modifier;
    }else{
        return opcode << 6;
    }
}




//Adds instruction definitions to the interpreter
void addInstructionsToInterpreter(MipsInterpreter &interpreter){
    /*
     Add instruction defs corresponding to all 9 of the supported instructions. The behaviour of the instructions is defined by including a pointer to a function defined in "mipsInstructionFunctions.h"
     */
    interpreter.addInstructionDef(MipsInstructionDef("add", 0, 32, 4, mips_f_add));
    interpreter.addInstructionDef(MipsInstructionDef("addi", 8, 0, 4, mips_f_addi));
    interpreter.addInstructionDef(MipsInstructionDef("slti", 10, 0, 4, mips_f_slti));
    interpreter.addInstructionDef(MipsInstructionDef("slt", 0, 42, 4, mips_f_slt));
    interpreter.addInstructionDef(MipsInstructionDef("beq", 4, 0, 3, mips_f_beq));
    interpreter.addInstructionDef(MipsInstructionDef("bne", 5, 0, 3, mips_f_bne));
    interpreter.addInstructionDef(MipsInstructionDef("j", 2, 0, 2, mips_f_j));
    interpreter.addInstructionDef(MipsInstructionDef("lw", 35, 0, 5, mips_f_lw));
    interpreter.addInstructionDef(MipsInstructionDef("sw", 43, 0, 4, mips_f_sw));
}