//
//  wordTransfer.h
//  mipsim
//
//  Created by Jacob Simionato on 20/05/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//

#ifndef __mipsim__wordTransfer__
#define __mipsim__wordTransfer__

#include <iostream>

#include "mipsTypes.h"

class WordTransfer{
public:
    WordTransfer(wordT addressIn, wordT dataIn = 0);
    wordT address;
    wordT data;
    int numCycles;
};

#endif /* defined(__mipsim__wordTransfer__) */
