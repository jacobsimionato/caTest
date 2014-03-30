//
//  main.cpp
//  mipsim
//
//  Created by Jacob Simionato on 30/03/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//

#include <iostream>
#include <string>
#include <sys/time.h>

#include "memorySystem.h"
#include "mipsInterpreter.h"
#include "mipsInstructionFunctions.h"

using namespace std;

//Timer Stuff
long testTimer_getCurrentTimeMillis(){
    timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

unsigned long testTimer_startTime = testTimer_getCurrentTimeMillis();
string testTime_name;

void testTimer_start(string name){
    testTimer_startTime = testTimer_getCurrentTimeMillis();
    testTime_name = name;
}

long testTimer_getDurationMillis(){
    return testTimer_getCurrentTimeMillis() - testTimer_startTime;
}

void testTimer_print(){
    float durationSeconds = testTimer_getDurationMillis() / 1000.0;
    cout << "TIMER: " << testTime_name << " - " << durationSeconds << " seconds" << endl;
}

//Test suite
void testArithmetic();
void testMemory();


//Adds instruction definitions to the interpreter
void addInstructionsToInterpreter(MipsInterpreter &interpreter);

int main(int argc, const char * argv[]){
    MemorySystem memorySystem;
    MipsInterpreter mipsInterpreter(&memorySystem);
    addInstructionsToInterpreter(mipsInterpreter);
    
    mipsInterpreter.printInstructionDefs();
    
    testArithmetic();
    testMemory();
    
    //mipsInterpreter.printRegisters();
    //mipsInterpreter.printStats();
    
    return 0;
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

void testArithmetic(){
    cout << "================== Testing Arithmetic Functions ===================" << endl;
    MemorySystem memorySystem;
    MipsInterpreter mipsInterpreter(&memorySystem);
    addInstructionsToInterpreter(mipsInterpreter);
    mipsInterpreter.getCore()->setRegSig(1, -8);
    mipsInterpreter.getCore()->setRegSig(2, 3);
    memorySystem.setWord(0x0, 0x00221820);
    mipsInterpreter.fetchAndInterpret(1);
    cout << "R3 is ";
    cout << mipsInterpreter.getCore()->getRegSig(3) << endl;
    mipsInterpreter.getCore()->setRegUns(1, 0x1001);
    mipsInterpreter.getCore()->setRegUns(2, 0x0342);
    memorySystem.setWord(0x4, 0x00221820);
    mipsInterpreter.fetchAndInterpret(1);
    cout << "R3 is ";
    cout << hex << mipsInterpreter.getCore()->getRegUns(3) << endl;
    mipsInterpreter.printStats();
    
    //Set registers to ascending numbers
    for(int i=1; i<32; i++){
        mipsInterpreter.getCore()->setRegUns(i, i);
    }
    
    srand(time(0));
    testTimer_start("2 000 000 random arithmetic operations");
    for(int i=0; i < 1000000; i++){
        memorySystem.setWord(i*4, 0x00221820); //Add R3 <- R1, R2
        memorySystem.setWord(i*4, 0x00221820); //Add R3 <- R1, R2
        memorySystem.setWord(i*4, 0x00221820); //Add R3 <- R1, R2
        
        memorySystem.setWord((rand()%16384) * 4, rand());
    }
    testTimer_print();
    
    
}

void testMemory(){
    cout << "================== Testing Memory System ===================" << endl;
    MemorySystem memorySystem;
    //MipsInterpreter mipsInterpreter(&memorySystem);
    //addInstructionsToInterpreter(mipsInterpreter);
    
    memorySystem.setWord(3400, 4667);
    memorySystem.setWord(50000, 12345);
    memorySystem.setWord(0, 3);
    cout << memorySystem.retrieveWord(3400) << endl;
    
    memorySystem.printSummary();
    memorySystem.setVerbose(false);
    
    srand(time(0));
    testTimer_start("100 000 000 random writes");
    for(int i=0; i < 100000000; i++){
        memorySystem.setWord((rand()%16384) * 4, rand());
    }
    testTimer_print();
    
    memorySystem.setVerbose(false);
    
    testTimer_start("100 000 000 random reads");
    for(int i=0; i < 100000000; i++){
        memorySystem.retrieveWord((rand()%16384) * 4);
    }
    testTimer_print();
    //mipsInterpreter.printStats();
    //mipsInterpreter.printRegisters();
    
    
}