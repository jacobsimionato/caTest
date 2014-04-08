//
//  mipSimPerformance.h
//  mipsim
//
//  Created by Jacob Simionato on 8/04/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//

#ifndef __mipsim__mipSimPerformance__
#define __mipsim__mipSimPerformance__

#include <iostream>

#include "memorySystem.h"
#include "mipsInterpreter.h"
#include "mipsInstructionFunctions.h"
#include "patternMatchers.h"
#include "debugHelperFunctions.h"

//Performance suite
void testExecutionSpeedPerformance();
void testArithmeticPerformance();
void testMemoryPerformance();

#endif /* defined(__mipsim__mipSimPerformance__) */
