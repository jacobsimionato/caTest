//
//  memorySystem.cpp
//  mipsim
//  Computer Architecture Assignment 1 2014
//  Jacob Simionato a1175808

#include "memorySystem.h"

using namespace std;

/*
 ======== setWord(int address, int data) ========
 1. allocates relevant block if not yet allocated
 2. sets word at given address to given data
 
 */
void MemorySystem::setWord(WordTransfer &wordTrans){
    wordTrans.numCycles = m_transferTime; //Add transfer time to transfer
    
    wordT address = wordTrans.address;
    
    int blockNum = address / BLOCKSIZE;
    
    //Abort if blockNum not in range - should not happen if BLOCKSIZE and NUM_BLOCKS are consistent
    if(blockNum >= NUM_BLOCKS){
        if(m_verbose){
            cout << "MemorySystem::setWord ERROR - address out of range" << endl;
        }
        return;
    }
    
    //If relevant block does not exist, then allocate it
    if(m_blockTable[blockNum] == NULL){
        allocateBlock(blockNum);
    }
    
    //Set relevant word of relevant block
    (m_blockTable[blockNum])[(address % BLOCKSIZE)/4] = wordTrans.data;
    
    if(m_verbose){
        cout << "MemorySystem: Word at address " << address << " in block " << blockNum << ", offset " << address % BLOCKSIZE << " set to " << wordTrans.data << endl;
    }
}

/*
 ======== retrieveWord(int address) ========
 retrieves word from memory address provided
 if block is not yet allocated, 0 is returned and the block remains unallocated, simulating a memory where each location is initialized to zero
 */
void MemorySystem::retrieveWord(WordTransfer &wordTrans){
    wordTrans.numCycles = m_transferTime; //Add transfer time to transfer
    
    wordT address = wordTrans.address;
    int blockNum = address / BLOCKSIZE;
    
    //Abort if blockNum not in range - should not happen if BLOCKSIZE and NUM_BLOCKS are consistent
    if(blockNum >= NUM_BLOCKS){
        if(m_verbose){
            cout << "MemorySystem::setWord ERROR - address out of range" << endl;
        }
        wordTrans.data = 0;
        return;
    }
    
    //If the block is not allocated, then return 0 as memory should be initialized to zero. We could allocate block here, but it wouldn't make a functional difference
    if(m_blockTable[blockNum] == NULL){
        //Print warning as no program should need to retrieve uninitialized memory locations
        if(m_verbose){
            cout << "MemorySystem: WARNING - retrieved address " << address << " is in unallocated block" << endl;
        }
        wordTrans.data = 0;
        return;
    //Else return the desired address
    }else{
        if(m_verbose){
            cout << "MemorySystem: Word at address " << address << " retrieved from block " << blockNum << endl;
        }
        wordTrans.data = (m_blockTable[blockNum])[(address % BLOCKSIZE)/4];
        return;
    }
}


/*
 ======== int getAddressAccessCycles() ========
 Returns number of cycles taken to access the memory added to the transfer time for the number of blocks transferred
 */
int MemorySystem::getAddressAccessCycles(){
    return m_accessTime;
}

/*
 ======== MemorySystem() ========
 Constructor sets each pointer in m_blockTable to NULL to indicate they have not yet been allocated
 */
MemorySystem::MemorySystem(int accessTime, int transferTime){
    //Allocate blocktable - must be dynamic to avoid stack size limits
    m_blockTable = new wordT*[NUM_BLOCKS];
    
    //Initialize m_blockTable pointer array to all NULLS to indicate unallocated blocks
    for(int i = 0; i<NUM_BLOCKS; i++){
        m_blockTable[i] = NULL;
    }
    
    m_verbose = false;
    
    m_accessTime = accessTime;
    m_transferTime = transferTime;
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
    //Allocate storage for new block
    wordT* newBlock = new wordT[BLOCKSIZE/4];
    
    //Initialize new block to zero at every location
    for(int i = 0; i < BLOCKSIZE/4; i++){
        newBlock[i] = 0;
    }
    
    //Save pointer to new block in the blockTable
    m_blockTable[blockNum] = newBlock;
    
    //Print message if in verbose mode
    if(m_verbose){
        cout << "MemorySystem: Block " << blockNum << " allocated at host address " << m_blockTable[blockNum] << " - " << m_blockTable[blockNum] + BLOCKSIZE <<  endl;
    }
}