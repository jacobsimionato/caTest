//
//  mipsInterpreterCore.cpp
//  mipsim
//  Computer Architecture Assignment 1 2014
//  Jacob Simionato a1175808

#include "mipsInterpreterCore.h"

using namespace std;

/*
 ======== MipsInterpreterCore(MemorySystemGeneric* memorySystem) ========
 Initializes register values and binds core to memorySystem
 */
MipsInterpreterCore::    MipsInterpreterCore(MemorySystemGeneric* memorySystemInst, MemorySystemGeneric* memorySystemData){
    resetRegs();
    m_memorySystemInst = memorySystemInst;
    m_memorySystemData = memorySystemData;
}


/*
 ======== void resetRegs() ========
 Initializes register values to zero
 */
void MipsInterpreterCore::resetRegs(){
    for(int i = 0; i < NUM_GP_REGS; i++){
        m_regGp[i] = 0;
    }
    m_regPc = 0;
}

/*
 ======== void print() ========
 Prints each of the register values including PC
 */
void MipsInterpreterCore::print(){
    cout << "====== Mips Interpreter Core ======" << endl;
    cout << "PC: " << m_regPc << endl;
    for(int i = 0; i < NUM_GP_REGS; i++){
        cout << "GP " << i << ": " << m_regGp[i] << endl;
    }
    cout << endl;
}

/*
 ======== get/set methods for general purpose registers and PC ========
 Includes variants that return signed and unsigned types
 References to R0 are caught and treated appropriately
 */
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

//Increment PC forwards by this unsigned value
void MipsInterpreterCore::incPc(wordT val){
    m_regPc += val;
}

//Relative jump by a distance in byte address represented as a signed long
void MipsInterpreterCore::relJumpPc(long val){
    //If offset positive, add as usual
    if(val >= 0){
        m_regPc += val;
    //If value negative, subtract absolute value using unsigned maths
    }else{
        unsigned int absVal = abs(val);
        m_regPc -= absVal;
    }
}

/*
 ======== void fetchInstruction() ========
 Fetch the instruction from instruction memory system at the current PC address
 */
wordT MipsInterpreterCore::fetchInstruction(){
    return m_memorySystemInst->retrieveWord(m_regPc);
}

/*
 ======== void setWordData(wordT address, wordT data) ========
 Set a word in the data memory system
 */
void MipsInterpreterCore::setWordData(wordT address, wordT data){
    m_memorySystemData->setWord(address, data);
}

/*
 ======== wordT retrieveWordData(wordT address) ========
 Retrieve a word from the data memory system
 */

wordT MipsInterpreterCore::retrieveWordData(wordT address){
    return m_memorySystemData->retrieveWord(address);
}

