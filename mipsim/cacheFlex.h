//
//  cacheFlex.h
//  mipsim
//
//  Created by Jacob Simionato on 20/05/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//

#ifndef __mipsim__cacheFlex__
#define __mipsim__cacheFlex__

#include <iostream>

#include "cacheGeneric.h"
#include "cacheBlock.h"

enum WriteStrat{
    WRITE_THROUGH_AROUND,
    WRITE_BACK_ALLOCATE,
};

class CacheFlex: public CacheGeneric{
public:
    CacheFlex(MemorySystemGeneric* parent, int cacheSizeKiloByte, int blockSizeBytes, int associativity, WriteStrat writeStrategy);
    
    //Exposed data I/O interface
    virtual void setWord(WordTransfer &wordTrans);
    virtual void retrieveWord(WordTransfer &wordTrans);
    
private:
    CacheTag* m_tags;
    wordT* m_blockWords;
    
    WriteStrat m_writeStrategy;
    int m_numBlocks;
    int m_blockSizeBytes;
    int m_numBlocksInSet;
    int m_numSets;
    int m_numBits_setNum;
    int m_numBits_offset;
    int m_numBits_tag;
    
    //Helper function to calculate how many bits in each field
    int log2(int input);
};

#endif /* defined(__mipsim__cacheFlex__) */
