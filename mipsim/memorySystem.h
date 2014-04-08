//
//  memorySystem.h
//  mipsim
//
//  Created by Jacob Simionato on 30/03/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//

#ifndef __mipsim__memorySystem__
#define __mipsim__memorySystem__

#include <iostream>

#include "mipsTypes.h"
#include "memorySystemGeneric.h"

#define BLOCKSIZE 4096  //Size of block in bytes
#define NUM_BLOCKS 1048576 //NUM_BLOCKS = 2^16 / BLOCKSIZE

class MemorySystem: public MemorySystemGeneric{
public:
    //Exposed data I/O interface
    void setWord(wordT address, wordT data);
    wordT retrieveWord(wordT address);
    
    MemorySystem();
    ~MemorySystem();
    
    void setVerbose(bool m_verbose_set = true);
    
    void printSummary();
private:
    //Enables error messages for debugging
    bool m_verbose;
    
    //Table of pointers to blocks - NULL indicates block has not been allocated
    wordT** m_blockTable;
    
    //Allocates a block at the given number
    void allocateBlock(int blockNum);
};

#endif /* defined(__mipsim__memorySystem__) */
