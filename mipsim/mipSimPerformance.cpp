//
//  mipSimPerformance.cpp
//  mipsim
//  Computer Architecture Assignment 1 2014
//  Jacob Simionato a1175808

#include "mipSimPerformance.h"

#include <iostream>
#include <string>
#include <sys/time.h>
#include <iomanip>
#include <cstring>

using namespace std;

/*
 Generate binary-encoded 32bit MIPS instructions for debugging purposes
 */
//Set the bit fields in register and immediate instruction formats
int setInstFieldsReg(int input, int s, int t, int d){
    input = input & ~(32767 << 11);
    input += s << 21;
    input += t << 16;
    input += d << 11;
    return input;
}

int setInstFieldsImm(int input, int s, int t, int C){
    input = input & ~(67108863);
    input += s << 21;
    input += t << 16;
    input += C;
    return input;
}

//Generates specific instructions with fixed opcode and variable parameter fields
wordT genInstAdd(int s, int t, int d){
    return setInstFieldsReg(0x20, s, t, d);
}

wordT genInstAddi(int s, int t, int C){
    return setInstFieldsImm(0x20000000, s, t, C);
}

wordT genInstSw(int s, int t, int C){
    return setInstFieldsImm(0xAC000000, s, t, C);
}

wordT genInstLw(int s, int t, int C){
    return setInstFieldsImm(0x8C000000, s, t, C);
}


/*
 =================== Instruction Generation ===================
 Generate binary-encoded 32bit MIPS instructions for debugging purposes
 */
//Get current time since unix epoch in milliseconds
long testTimer_getCurrentTimeMillis(){
    timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

//Global variables to store the timer offset since epoch and name
unsigned long testTimer_startTime = testTimer_getCurrentTimeMillis();
string testTime_name;

//Start the duration timer and assign a name which will be used to print later
void testTimer_start(string name){
    testTimer_startTime = testTimer_getCurrentTimeMillis();
    testTime_name = name;
}

//Get the current number of milliseconds since start time
long testTimer_getDurationMillis(){
    return testTimer_getCurrentTimeMillis() - testTimer_startTime;
}

//Print the timer name and duration since start
void testTimer_print(){
    float durationSeconds = testTimer_getDurationMillis() / 1000.0;
    cout << "TIMER: " << testTime_name << " - " << durationSeconds << " seconds" << endl;
}

/*
 =================== Performance Test Suite ===================
 Runs different simulation tasks and times them to determine performance
 */
//Runs three instructions (add, addi, sw) in succession from random spot in memory 1 000 000 times
void testExecutionSpeedPerformance(){
    cout << "================== Testing Random Arithmetic Performance ===================" << endl;
    MemorySystem memorySystem;
    MipsInterpreter mipsInterpreter(&memorySystem, &memorySystem);
    addInstructionsToInterpreter(mipsInterpreter);
    
    //Set registers to ascending numbers
    for(int i=1; i<32; i++){
        mipsInterpreter.getCore()->setRegUns(i, i);
    }
    
    srand(time(0));
    testTimer_start("3 000 000 random operations");
    for(int i=0; i < 1000000; i++){
        int PC = rand()%5000*4;
        mipsInterpreter.getCore()->setPc(PC);
        //Generate instructions
        int addInst = genInstAdd(rand()%32,rand()%32,rand()%31+1);
        int addiInst = genInstAddi(rand()%32,rand()%31+1,rand()%1000);
        int swInst = genInstSw(0, rand()%32, 100);
        //Load instructions
        
        WordTransfer wordSet1(PC+0, addInst);
        memorySystem.setWord(wordSet1);
        
        WordTransfer wordSet2(PC+4, addiInst);
        memorySystem.setWord(wordSet2);
        
        WordTransfer wordSet3(PC+8, swInst);
        memorySystem.setWord(wordSet3);
        
        //Run instructions
        mipsInterpreter.fetchAndInterpret(3);
    }
    //mipsInterpreter.printRegisters();
    //mipsInterpreter.printStats();
    
    testTimer_print();
    
}

//Runs 100 million random reads and writes and reports time elapsed for each
void testMemoryPerformance(){
    cout << "================== Testing Memory System Performance ===================" << endl;
    MemorySystem memorySystem;
    
    memorySystem.setVerbose(false);
    
    srand(time(0));
    testTimer_start("100 000 000 random writes");
    for(int i=0; i < 100000000; i++){
        WordTransfer wordSet1((rand()%1073741824) * 4, rand());
        memorySystem.setWord(wordSet1);
    }
    testTimer_print();
    
    memorySystem.setVerbose(false);
    
    testTimer_start("100 000 000 random reads");
    for(int i=0; i < 100000000; i++){
        WordTransfer wordRetr1((rand()%1073741824) * 4);
        memorySystem.retrieveWord(wordRetr1);
    }
    testTimer_print();
}