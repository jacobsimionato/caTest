//
//  memorySystem.h
//  mipsim
//  Computer Architecture Assignment 1 2014
//  Jacob Simionato a1175808

#ifndef __mipsim__memorySystem__
#define __mipsim__memorySystem__

#include <iostream>

#include "mipsTypes.h"
#include "memorySystemGeneric.h"

#define BLOCKSIZE 4096  //Size of block in bytes
#define NUM_BLOCKS 1048576 //NUM_BLOCKS = 2^16 / BLOCKSIZE

/*
 ====================== MemorySystem ======================
 An implementation of a memory system which uses 2^16 / BLOCKSIZE memory blocks referred to by a table
 */
class MemorySystem: public MemorySystemGeneric{
public:
    //Exposed data I/O interface
    void setWord(wordT address, wordT data);
    wordT retrieveWord(wordT address);
    
    MemorySystem();
    ~MemorySystem();
    
    //Sets verbose mode
    void setVerbose(bool m_verbose_set = true);
    
    //Prints a list of allocated blocks for debugging
    void printSummary();
private:
    //Enables error messages for debugging
    bool m_verbose;
    
    //Table of pointers to blocks - NULL pointer indicates block has not been allocated yet
    wordT** m_blockTable;
    
    //Allocates a block at the given number
    void allocateBlock(int blockNum);
};

#endif /* defined(__mipsim__memorySystem__) */
