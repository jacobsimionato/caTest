//
//  memorySystemGeneric.h
//  mipsim
//
//  Created by Jacob Simionato on 30/03/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//

#ifndef __mipsim__memorySystemGeneric__
#define __mipsim__memorySystemGeneric__

#include <iostream>

#include "mipsTypes.h"

class MemorySystemGeneric{
public:
    //Exposed data I/O interface
    virtual void setWord(wordT address, wordT data) = 0;
    virtual wordT retrieveWord(wordT address) = 0;
    
    //Sets memory system to verbose or non-verbose modes
    virtual void setVerbose(bool m_verbose_set = true) = 0;
    
    //Print a summary of the memory system state
    virtual void printSummary() = 0;
};

#endif /* defined(__mipsim__memorySystemGeneric__) */
