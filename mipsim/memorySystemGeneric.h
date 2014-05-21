//
//  memorySystemGeneric.h
//  mipsim
//  Computer Architecture Assignment 1 2014
//  Jacob Simionato a1175808

#ifndef __mipsim__memorySystemGeneric__
#define __mipsim__memorySystemGeneric__

#include <iostream>

#include "mipsTypes.h"
#include "wordTransfer.h"
/*
 ====================== MemorySystemGeneric ======================
 An abstract class which defines the memory system interface in order to allow different memory systems to be easily substituted and compared at a later time.
 */
class MemorySystemGeneric{
public:
    //Exposed data I/O interface
    virtual void setWord(WordTransfer &wordTrans) = 0;
    virtual void retrieveWord(WordTransfer &wordTrans) = 0;
    
    //Return number of address access cycles for this memory to assist with accounting
    virtual int getAddressAccessCycles() = 0;
    
    //Sets memory system to verbose or non-verbose modes
    virtual void setVerbose(bool m_verbose_set = true);
protected:
    //Enables error messages for debugging
    bool m_verbose;
};

#endif /* defined(__mipsim__memorySystemGeneric__) */
