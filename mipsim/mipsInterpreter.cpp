//
//  mipsInterpreter.cpp
//  mipsim
//
//  Created by Jacob Simionato on 30/03/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//

#include "mipsInterpreter.h"



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
        cout << "Average CPI: " << avCpi << endl;
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
    int modifier = instructionBin & 63;
    return (opcode << 6) + modifier;
}
