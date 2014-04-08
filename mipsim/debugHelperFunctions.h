//
//  debugHelperFunctions.h
//  mipsim
//
//  Created by Jacob Simionato on 30/03/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//

#ifndef __mipsim__debugHelperFunctions__
#define __mipsim__debugHelperFunctions__

#include <iostream>
#include "mipsTypes.h"

wordT genInstAdd(int s, int t, int d);

wordT genInstAddi(int s, int t, int C);

wordT genInstSw(int s, int t, int C);

wordT genInstLw(int s, int t, int C);

#endif /* defined(__mipsim__debugHelperFunctions__) */

