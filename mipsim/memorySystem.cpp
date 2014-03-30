//
//  memorySystem.cpp
//  mipsim
//
//  Created by Jacob Simionato on 30/03/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//

#include "memorySystem.h"

using namespace std;

/*
 ======== setWord(int address, int data) ========
 1. allocates relevant block if not yet allocated
 2. sets word at given address to given data
 
 returns 0 on success, or -1 on error
 */
void MemorySystem::setWord(int address, wordT data){
    int blockNum = address / BLOCKSIZE;
    if(m_blockTable[blockNum] == NULL){
        allocateBlock(blockNum);
    }
    
    (m_blockTable[blockNum])[(address % BLOCKSIZE)/4] = data;
    if(m_verbose){
        cout << "MemorySystem: Word at address " << address << " in block " << blockNum << ", offset " << address % BLOCKSIZE << " set to " << data << endl;
    }
}

/*
 ======== retrieveWord(int address) ========
 1. allocates relevant block if not yet allocated
 2. sets word at given address to given data
 
 returns data as unsigned word 
 */
wordT MemorySystem::retrieveWord(int address){
    int blockNum = address / BLOCKSIZE;
    //If the block is not allocated, then return -1 to indicate error
    if(m_blockTable[blockNum] == NULL){
        if(m_verbose){
            cout << "MemorySystem: ERROR - address " << address << " is in unallocated block" << endl;
        }
        return 0;
    //Else return the desired address
    }else{
        if(m_verbose){
            cout << "MemorySystem: Word at address " << address << " retrieved from block " << blockNum << endl;
        }
        return (m_blockTable[blockNum])[(address % BLOCKSIZE)/4];
    }
}

/*
 ======== MemorySystem() ========
 Constructor sets each pointer in m_blockTable to NULL to indicate they have not yet been allocated
 */
MemorySystem::MemorySystem(){
    //Initialize m_blockTable pointer array to all NULLS to indicate unallocated blocks
    for(int i = 0; i<NUM_BLOCKS; i++){
        m_blockTable[i] = NULL;
    }
    
    m_verbose = true;
}

/*
 ======== ~MemorySystem() ========
 Destructor deallocates any blocks that have been allocated by checking for non-null m_blockTable pointers
 */
MemorySystem::~MemorySystem(){
    for(int i = 0; i<NUM_BLOCKS; i++){
        if(m_blockTable[i] != NULL){
            delete(m_blockTable[i]);
        }
    }
}


/*
 ======== setVerbose(bool m_verbose_set) ========
 Sets verbose mode on or off
 */
void MemorySystem::setVerbose(bool m_verbose_set){
    m_verbose = m_verbose_set;
}

/*
 ======== printSummary() ========
 Prints a summary of the memory state
 */
void MemorySystem::printSummary(){
    cout << "Blocks allocated: ";
    for(int i = 0; i < NUM_BLOCKS; i++){
        if(m_blockTable[i] != NULL){
            cout << i << " ";
        }
    }
    cout << endl;
}

/*
 ======== allocateBlock(int blockNum) ========
 Allocates the given block num with an array representing the desired data area
 Does NOT check if the block has already been allocated
 */
void MemorySystem::allocateBlock(int blockNum){
    wordT* newBlock = new wordT[BLOCKSIZE/4];
    m_blockTable[blockNum] = newBlock;
    if(m_verbose){
        cout << "MemorySystem: Block " << blockNum << " allocated at host address " << m_blockTable[blockNum] << " - " << m_blockTable[blockNum] + BLOCKSIZE <<  endl;
    }
}