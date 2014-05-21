//
//  cacheFlex.cpp
//  mipsim
//
//  Created by Jacob Simionato on 20/05/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//

#include "cacheFlex.h"

CacheFlex::CacheFlex(MemorySystemGeneric* parent, int cacheSizeKiloByte, int blockSizeBytes, int associativity, WriteStrat writeStrategy): CacheGeneric(parent){
    m_numBlocks = cacheSizeKiloByte * 1024 / blockSizeBytes;
    m_numBlocksInSet = associativity;
    m_numSets = m_numBlocks / m_numBlocksInSet;
    m_blockSizeBytes = blockSizeBytes;
    
    m_numBits_setNum = log2(m_numSets);
    m_numBits_offset = log2(m_blockSizeBytes);
    m_numBits_tag = 32 - m_numBits_setNum - m_numBits_offset;
    
    //Allocate and initialize cache blocks
    m_tags = new CacheTag[m_numBlocks];
    for(int i=0; i<m_numBlocks; i++){
        m_tags[i].init(m_blockSizeBytes);
    }
    
    //Allocate storage for the entire cache in one big array
    m_blockWords = new wordT[m_numBlocks * m_blockSizeBytes / 4];
}


void CacheFlex::setWord(WordTransfer &wordTrans){
    
}

void CacheFlex::retrieveWord(WordTransfer &wordTrans){
    
}

int CacheFlex::log2(int input){
    int result = 0;
    while (input >>= 1){
        ++result;
    }
    return result;
}