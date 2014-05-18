//
//  memorySystemGeneric.h
//  mipsim
//  Computer Architecture Assignment 1 2014
//  Jacob Simionato a1175808

#ifndef __mipsim__memorySystemGeneric__
#define __mipsim__memorySystemGeneric__

#include <iostream>

#include "mipsTypes.h"

/*
 ====================== MemorySystemGeneric ======================
 An abstract class which defines the memory system interface in order to allow different memory systems to be easily substituted and compared at a later time.
 */
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
