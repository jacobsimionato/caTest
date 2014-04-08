//
//  mipsimTests.h
//  mipsim
//
//  Created by Jacob Simionato on 8/04/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//

#ifndef __mipsim__mipsimTests__
#define __mipsim__mipsimTests__

#include <iostream>

#include "memorySystem.h"
#include "mipsInterpreter.h"
#include "mipsInstructionFunctions.h"
#include "patternMatchers.h"
#include "debugHelperFunctions.h"


void runMipsimTests();

void runPatternMatchersTests();

bool assert(bool result, bool expected, std::string description);
bool assert(std::string result, std::string expected, std::string description);
bool assert(int result, int expected, std::string description);
bool assert(unsigned int result, unsigned int expected, std::string description);
#endif /* defined(__mipsim__mipsimTests__) */
