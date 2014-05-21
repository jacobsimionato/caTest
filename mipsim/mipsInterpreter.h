//
//  mipsInterpreter.h
//  mipsim
//  Computer Architecture Assignment 1 2014
//  Jacob Simionato a1175808

#ifndef __mipsim__mipsInterpreter__
#define __mipsim__mipsInterpreter__

#include <iostream>
#include <vector>
#include <map>

#include "mipsTypes.h"
#include "mipsInstructionDef.h"
#include "mipsInterpreterCore.h"

//Declare MipsInstructionDef class as they reference each other
class MipsInstructionDef;

/*
 ====================== MipsInterpreter ======================
 A class which performs actions on the state stored in the MipsInterpreterCore
 This includes retrieving and interpreting instructions as well as maintaining statistics.
 InstructionDefs are matched to instructions by generating a key and then retrieving a value from a std::map search tree
 */
class MipsInterpreter{
public:
    //Construct mips interpreter which must be bound to an existing memorySystem
    MipsInterpreter(MemorySystemGeneric* memorySystemInst, MemorySystemGeneric* memorySystemData);
    
    //Fetches and interprets several instructions one-by-one
    int fetchAndInterpret(int num = 1);
    
    //nterprets the given instruction encoded as a binary word
    int interpret(wordT instructionBin);
    
    //Add an InstructionDef instance to the internal table
    void addInstructionDef(MipsInstructionDef instructionDef);
    
    //Print key-value pairs contained in m_instructionDefs for debugging purposes
    void printInstructionDefs();
    
    //Print the register values of the simulator core
    void printRegisters();
    
    //Print the register values of the simulator core
    void printStats();
    
    //Return a pointer to the internal interpreterCore instance
    MipsInterpreterCore* getCore();
    
    //Access instance variables
    int getCycleCount();
    int getInstrCount();
    void resetCounts();
    
    //Sets verbose mode of mipsInterpreter
    void setVerbose(bool val);
private:
    //MipsInterpreterCore contains the state information including registers and a reference to a memorySystem
    MipsInterpreterCore m_interpreterCore;
    
    //If m_verbose == true, notifications or error messages are printed when the instructions are interpreted
    bool m_verbose;
    
    //Counts to maintain global statistics
    //int m_cycleCount;
    //int m_instrCount;
    
    //Generates an integer search key from a binary instruction containing the opcode and modifier
    int genKeyFromInstruction(wordT instructionBin);

    //std::map datastructure to store integer key => instructionDef pairs (implemented as red-black tree) to very quickly retrieve relevant instruction data
    std::map<int, MipsInstructionDef> m_instructionDefs;
};


#endif /* defined(__mipsim__mipsInterpreter__) */
