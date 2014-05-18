//
//  mipSimPerformance.h
//  mipsim
//  Computer Architecture Assignment 1 2014
//  Jacob Simionato a1175808

#ifndef __mipsim__mipSimPerformance__
#define __mipsim__mipSimPerformance__

#include <iostream>

#include "memorySystem.h"
#include "mipsInterpreter.h"
#include "mipsInstructionFunctions.h"
#include "patternMatchers.h"

/*
 =================== Instruction Generation ===================
 Generate binary-encoded 32bit MIPS instructions for debugging purposes
 */

//General helper functions to set the bit fields of register and immediate format instructions
int setInstFieldsReg(int input, int s, int t, int d);
int setInstFieldsImm(int input, int s, int t, int C);

//Generates specific instructions with fixed opcode and variable parameter fields
wordT genInstAdd(int s, int t, int d);
wordT genInstAddi(int s, int t, int C);
wordT genInstSw(int s, int t, int C);
wordT genInstLw(int s, int t, int C);


/*
 =================== Timer Framework ===================
 Times intervals to measure performance
 */
//Get current time since unix epoch in milliseconds
long testTimer_getCurrentTimeMillis();

//Start the duration timer and assign a name which will be used to print later
void testTimer_start(std::string name);

//Get the current number of milliseconds since start time
long testTimer_getDurationMillis();

//Print the timer name and duration since start
void testTimer_print();

/*
 =================== Performance Test Suite ===================
 Runs different simulation tasks and times them to determine performance
 */
//Runs three instructions (add, addi, sw) in succession from random spot in memory 1 000 000 times
void testExecutionSpeedPerformance();

//Runs 100 million random reads and writes and reports time elapsed for each
void testMemoryPerformance();

#endif /* defined(__mipsim__mipSimPerformance__) */
