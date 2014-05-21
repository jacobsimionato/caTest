//
//  cacheGeneric.h
//  mipsim
//
//  Created by Jacob Simionato on 18/05/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//

#ifndef __mipsim__cacheGeneric__
#define __mipsim__cacheGeneric__

#include <iostream>

#include "memorySystemGeneric.h"


class CacheGeneric: public MemorySystemGeneric{
public:
    CacheGeneric(MemorySystemGeneric* parent);
    
    //Exposed data I/O interface
    virtual void setWord(WordTransfer &wordTrans) = 0;
    virtual void retrieveWord(WordTransfer &wordTrans) = 0;
    virtual int getAddressAccessCycles(); //Usually zero address access time for a cache, so set to zero by default
    
    int getMissCycleCount();
    int getMissCount();
    int getAccessCount();
    float getMissRate();
    float getDirtyOnReplacementRate();
    int getDirtyOnReplacementInstrs();
    
    void resetStats();
    
    MemorySystemGeneric* getParent();
protected:
    int m_missCycleCount;
    int m_missCount;
    int m_accessCount;
    int m_dirtyOnReplacementInstrs;
    
    MemorySystemGeneric* m_parent;
};

#endif /* defined(__mipsim__cacheGeneric__) */
