//
//  mipsInterpreter.cpp
//  mipsim
//  Computer Architecture Assignment 1 2014
//  Jacob Simionato a1175808

#include <iomanip>
#include <stdexcept>

#include "mipsInterpreter.h"
#include "mipsInstructionFunctions.h"


using namespace std;

/*
 ======== MipsInterpreter(MemorySystemGeneric* memorySystem) ========
 Construct mips interpreter which must be bound to an existing memorySystem
 */
MipsInterpreter::MipsInterpreter(MemorySystemGeneric* memorySystemInst, MemorySystemGeneric* memorySystemData): m_interpreterCore(memorySystemInst, memorySystemData){
    m_instrCount = 0;
    m_cycleCount = 0;
    
    m_verbose = false;
}

/*
 ======== int fetchAndInterpret(int num) ========
 Fetches and interprets num instructions one-by-one
 If there is an error in interpreting an instruction, exit immediately and return the error code
 */
int MipsInterpreter::fetchAndInterpret(int num){
    int result;
    for(int i = 0; i < num; i++){
        wordT instruction = m_interpreterCore.fetchInstruction();
        result = interpret(instruction);
        //If there is an error whilst interpreting
        if(result != 0){
            return result;
        }
    }
    return 0;
}

/*
 ======== int interpret(wordT instructionBin) ========
 Interprets the given instruction encoded as a binary word
 Returns 0 if instruction successfully interpreted or 1 if key could not be found
 */
int MipsInterpreter::interpret(wordT instructionBin){
    //Generate a key for the instructionDefs table
    int key = genKeyFromInstruction(instructionBin);
    
    MipsInstructionDef* instructionDef = NULL;
    
    //Try to find matching InstructionDef instance in std::map search tree using key
    try{
        instructionDef = &m_instructionDefs.at(key);
    }
    //Catch error if key not found, ie instruction binary code is invalid
    catch (const out_of_range &outOfRangeE) {
        if(m_verbose){
            cout << "MipsInterpreter::interpret ERROR: instruction key not found" << outOfRangeE.what();
        }
        return 1;
    }
    
    //Execute instruction
    int cyclesElapsed = instructionDef->execute(&m_interpreterCore, instructionBin);
    //Update statistics for this particular instruction type
    instructionDef->numTimesExecuted++;
    
    m_interpreterCore.incPc(4);
    
    //Maintain overall statistics
    m_cycleCount += cyclesElapsed;
    m_instrCount++;
    
    if(m_verbose){
        cout << "MipsInterpreter: Executing " << instructionDef->name << endl;
    }
    
    return 0;
}

/*
 ======== void addInstructionDef(MipsInstructionDef instructionDef) ========
 Add an InstructionDef instance to the internal table
 */
void MipsInterpreter::addInstructionDef(MipsInstructionDef instructionDef){
    //Create key by placing opcode in more significant position than modifier
    int key = (instructionDef.opcode << 6) + instructionDef.modifier;
    m_instructionDefs.insert(pair<int,MipsInstructionDef>(key,instructionDef));
}

/*
 ======== void printInstructionDefs() ========
 Print key-value pairs contained in m_instructionDefs for debugging purposes
 */
void MipsInterpreter::printInstructionDefs(){
    cout << "MipsInterpreter: Printing Instruction Defs" << endl;
    map<int, MipsInstructionDef>::iterator iter;
    for (iter = m_instructionDefs.begin(); iter != m_instructionDefs.end(); ++iter){
        cout << "Key: " << iter->first << " : ";
        iter->second.print();
    }
    cout << endl;
}

/*
 ======== void printRegisters() ========
 Print the register values of the simulator core
 */
void MipsInterpreter::printRegisters(){
    m_interpreterCore.print();
}

/*
 ======== void printStats() ========
 Print the register values of the simulator core
 */
void MipsInterpreter::printStats(){
    cout << dec;
    //Uses the search keys of the map to print the frequency report for each instruction in the required order
    int instructionReportOrder[9] = {32, 512, 42, 640, 256, 320, 2240, 2752, 128};
    for(int i = 0; i < sizeof(instructionReportOrder)/sizeof(int); i++){
        m_instructionDefs.at(instructionReportOrder[i]).printFreq();
    }
    
    //Print the other statistics
    cout << "Instruction count: " << m_instrCount << endl;
    cout << "Cycle count: " << m_cycleCount << endl;
    //Print CPI if instructions have been executed
    if(m_instrCount != 0){
        double avCpi = static_cast<double>(m_cycleCount) / static_cast<double>(m_instrCount);
        cout << "Average CPI: " << std::fixed << std::setprecision(4) << avCpi << endl;
    }
}

/*
 ======== MipsInterpreterCore* getCore() ========
 Return a pointer to the internal interpreterCore instance to allow register values to be tampered with etc.
 */
MipsInterpreterCore* MipsInterpreter::getCore(){
    return &m_interpreterCore;
}

/*
 ======== Count accessors / mutators ========
 Access and modify cycle accounting system
 */
int MipsInterpreter::getCycleCount(){
    return m_cycleCount;
}

int MipsInterpreter::getInstrCount(){
    return m_instrCount;
}

void MipsInterpreter::resetCounts(){
    m_cycleCount = 0;
    m_instrCount = 0;
}

/*
 ======== void setVerbose(bool val) ========
 Sets verbose mode of mipsInterpreter
 */
void MipsInterpreter::setVerbose(bool val){
    m_verbose = val;
}

/*
 ======== int genKeyFromInstruction(wordT instructionBin) ========
 Generates an integer search key from a binary instruction containing the opcode and modifier
 */
int MipsInterpreter::genKeyFromInstruction(wordT instructionBin){
    int opcode = (instructionBin >> 26) & 63;
    //If the opcode is zero, then include the modifier in the key
    if(opcode == 0){
        int modifier = instructionBin & 63;
        //Modifier in least sigificant position and opcode in next most sigificant position
        return (opcode << 6) + modifier;
    }else{
        return opcode << 6;
    }
}