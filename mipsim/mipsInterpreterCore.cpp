//
//  mipsInterpreterCore.cpp
//  mipsim
//
//  Created by Jacob Simionato on 30/03/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//

#include "mipsInterpreterCore.h"

using namespace std;

MipsInterpreterCore::MipsInterpreterCore(MemorySystemGeneric* memorySystem){
    resetRegs();
    m_memorySystem = memorySystem;
}

void MipsInterpreterCore::resetRegs(){
    for(int i = 0; i < NUM_GP_REGS; i++){
        m_regGp[i] = 0;
    }
    m_regPc = 0;
}

void MipsInterpreterCore::print(){
    cout << "====== Mips Interpreter Core ======" << endl;
    cout << "PC: " << m_regPc << endl;
    for(int i = 0; i < NUM_GP_REGS; i++){
        cout << "GP " << i << ": " << m_regGp[i] << endl;
    }
    cout << endl;
}

wordT MipsInterpreterCore::getRegUns(int regNum){
    if(regNum == 0){
        return 0;
    }else{
        return m_regGp[regNum];
    }
}

void MipsInterpreterCore::setRegUns(int regNum, wordT val){
    if(regNum == 0){
        //do nothing
    }else{
        m_regGp[regNum] = val;
    }
}

wordST MipsInterpreterCore::getRegSig(int regNum){
    if(regNum == 0){
        return 0;
    }else{
        return static_cast<wordST>(m_regGp[regNum]);
    }
}

void MipsInterpreterCore::setRegSig(int regNum, wordST val){
    if(regNum == 0){
        //do nothing
    }else{
        m_regGp[regNum] = static_cast<wordT>(val);
    }
}

wordT MipsInterpreterCore::getPc(){
    return m_regPc;
}

void MipsInterpreterCore::setPc(wordT val){
    m_regPc = val;
}

void MipsInterpreterCore::incPc(wordT val){
    m_regPc += val;
}

wordT MipsInterpreterCore::fetchInstruction(){
    return m_memorySystem->retrieveWord(m_regPc);
}

MemorySystemGeneric* MipsInterpreterCore::getMemorySystem(){
    return m_memorySystem;
}