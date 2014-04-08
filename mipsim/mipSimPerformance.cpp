//
//  mipSimPerformance.cpp
//  mipsim
//
//  Created by Jacob Simionato on 8/04/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//

#include "mipSimPerformance.h"

#include <iostream>
#include <string>
#include <sys/time.h>
#include <iomanip>
#include <cstring>

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


void testExecutionSpeedPerformance(){
    cout << "================== Testing Random Arithmetic Performance ===================" << endl;
    MemorySystem memorySystem;
    MipsInterpreter mipsInterpreter(&memorySystem);
    addInstructionsToInterpreter(mipsInterpreter);
    
    //Set registers to ascending numbers
    for(int i=1; i<32; i++){
        mipsInterpreter.getCore()->setRegUns(i, i);
    }
    
    srand(time(0));
    testTimer_start("2 000 000 random operations");
    for(int i=0; i < 1000000; i++){
        int PC = rand()%5000*4;
        mipsInterpreter.getCore()->setPc(PC);
        int addInst = genInstAdd(rand()%32,rand()%32,rand()%31+1);
        int addiInst = genInstAddi(rand()%32,rand()%31+1,rand()%1000);
        int swInst = genInstSw(0, rand()%32, 100);
        //int swInst = genInstSw(
        memorySystem.setWord(PC+0, addInst); //Add R3 <- R1, R2
        memorySystem.setWord(PC+4, addiInst); //Add R3 <- R1, R2
        memorySystem.setWord(PC+8, swInst); //Add R3 <- R1, R2
        mipsInterpreter.fetchAndInterpret(3);
        //mipsInterpreter.fetchAndInterpret(1);
    }
    mipsInterpreter.printRegisters();
    mipsInterpreter.printStats();
    
    testTimer_print();
    
}

void testArithmeticPerformance(){
    cout << "================== Testing Arithmetic Function Performance ===================" << endl;
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
    
    mipsInterpreter.getCore()->setRegSig(4, -140);
    mipsInterpreter.getCore()->setRegSig(5, 40);
    memorySystem.setWord(0x8, genInstAdd(4,5,6));
    mipsInterpreter.fetchAndInterpret(1);
    cout << dec << "R6 is " << mipsInterpreter.getCore()->getRegSig(6) << endl;
    mipsInterpreter.printStats();
    
    
}

void testMemoryPerformance(){
    cout << "================== Testing Memory System Performance ===================" << endl;
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