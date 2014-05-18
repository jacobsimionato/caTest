//
//  mipsimTests.h
//  mipsim
//  Computer Architecture Assignment 1 2014
//  Jacob Simionato a1175808

#ifndef __mipsim__mipsimTests__
#define __mipsim__mipsimTests__

#include <iostream>

#include "memorySystem.h"
#include "mipsInterpreter.h"
#include "mipsInstructionFunctions.h"
#include "patternMatchers.h"


/*
 =============== Testing framework ===============
 If the first two arguments are equal test is passes and passed tally is incremented
 If the first two arguments are not equal, test fails and a description is printed
 */
bool assert(bool result, bool expected, std::string description);
bool assert(std::string result, std::string expected, std::string description);
bool assert(int result, int expected, std::string description);
bool assert(unsigned int result, unsigned int expected, std::string description);

/*
 =============== Test suite ===============
 Unit tests for many of the mipsim components. Higher level functionality and integration testing, including correct interpretation of binary instructions is handled by external test suites
 */
//Run the entire testing suite
void runMipsimTests();

//Individual sections of the test suite
void runPatternMatchersTests();
void runMipsInterpreterTests();
void runMemorySystemTests();
void runCmdLineOptionTests();


#endif /* defined(__mipsim__mipsimTests__) */
