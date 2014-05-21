//
//  main.cpp
//  mipsim
//  Computer Architecture Assignment 1 2014
//  Jacob Simionato a1175808


/*
 =================== MIPS Simulator ===================
 The system simulates the MIPS microprocessor but with only a small subset of the MIPS instruction set.
 Whilst the command line instructions are interpreted using a fairly inefficient cascading conditional statement method, the actual binary instruction interpreter uses a search tree with a combination of opcode and modifier as the key to quickly determine the correct instruction to execute!
 
 =================== Command Line Instructions ===================
 rn                 Show the content of register n in hex (n from 0 to 31)
 rn = value         Set register n to value (hex)
 m address          Show the content of memory word at address (hex)
 m address = value  Set memory word at address (hex) to value (hex)
 pc                 Show content of PC register in hex
 pc = address       Set PC register to address (hex)
 .                  Execute one instruction
 .n                 Execute n instructions
 
 =================== Command Line Arguments ===================
 Verbose : -v
    Print notifications and error messages
 Performance test : -p
    Run performance tests then exit
 Test Suite : -t
    Run unit testing suite then exit
 */

#include <iostream>
#include <string>
#include <sys/time.h>
#include <iomanip>
#include <cstring>

#include "memorySystem.h"               //Main Memory Simulator
#include "mipsInterpreter.h"            //Main CPU emulation which executes binary instructions
#include "mipsInstructionFunctions.h"   //Functions to execute each MIPS instruction
#include "patternMatchers.h"            //String manipulation functions to parse command line input
#include "mipSimPerformance.h"          //Performance testing functions
#include "mipsimTests.h"                //Unit testing suite
#include "cmdLineOption.h"
#include "cacheFlex.h"

using namespace std;


int main(int argc, const char * argv[]){
    //Determines whether the
    bool g_verbose = false;
    
    //Parse command line arguments
    if(argc > 1){

        cmdLineOption::parseCmdLineOptions(argc, argv);
        //cmdLineOption::printAll();

        cmdLineOption *o_v, *o_t, *o_p;
        if((o_v = cmdLineOption::findOpt("-v"))){
            //Enable verbose mode
            g_verbose = true;
        }
        
        if((o_t = cmdLineOption::findOpt("-t"))){
            //Run unit testing suite and then exit
            cout << "running tests" << endl;
            runMipsimTests();
        }
        
        if((o_p = cmdLineOption::findOpt("-p"))){
            //Run execution speed tests and then exit
            testExecutionSpeedPerformance();
            testMemoryPerformance();
        }
        
        if(o_t || o_p){
            //If we run tests or performance, then exit and don't run regular program
            exit(0);
        }
        
    }
    
    cmdLineOption *Is = cmdLineOption::findOpt("-Is");
    cmdLineOption *Ib = cmdLineOption::findOpt("-Ib");
    cmdLineOption *Ia = cmdLineOption::findOpt("-Ia");
    cmdLineOption *Ds = cmdLineOption::findOpt("-Ds");
    cmdLineOption *Db = cmdLineOption::findOpt("-Db");
    cmdLineOption *Da = cmdLineOption::findOpt("-Da");
    cmdLineOption *Dwt = cmdLineOption::findOpt("-Dwt");
    cmdLineOption *Dwb = cmdLineOption::findOpt("-Dwb");
    cmdLineOption *Ma = cmdLineOption::findOpt("-Ma");
    cmdLineOption *Mw = cmdLineOption::findOpt("-Mw");
    
    int IsVal, IbVal, IaVal, DsVal, DbVal, DaVal, MaVal, MwVal;
    
    WriteStrat instWriteStrat = WRITE_THROUGH_AROUND;
    WriteStrat dataWriteStrat;
    
    MemorySystem *memorySystem;
    CacheFlex *instCache, *dataCache;
    MemorySystemGeneric *instCacheGeneric, *dataCacheGeneric;
    
    /*
     =============== Memory System Configuration ===============
     */
    if(!Ma || !Mw){
        cout << "Error: Must include -Ma and -Mw options" << endl;
        exit(1);
    }
    
    MaVal = Ma->getArgPosInt(0);
    MwVal = Mw->getArgPosInt(0);
    
    
    if(MaVal == -1 || MwVal == -1){
        cout << "Error: -Ma and -Mw must be positive integers" << endl;
        exit(1);
    }
    
    memorySystem = new MemorySystem(MaVal, MwVal);
    

    
    /*
     =============== Instruction Cache Configuration ===============
     */
    
    if(Is && Ib && Ia){
        //If there IS an instruction case
        IsVal = Is->getArgPwr2(0);
        IbVal = Ib->getArgPwr2(0);
        if(Ia->getArgStr(0) == "full"){
            IaVal = IsVal * 1024 / IbVal; //Calculate full associativity = number of blocks in total
        }else{
            IaVal = Ia->getArgPwr2(0);
        }
        
        if(IsVal == -1 || IbVal == -1 || IaVal == -1){
            cout << "Error: -Is, -Ib, -Ia must be powers of two" << endl;
        }
        
        instCache = new CacheFlex(memorySystem, IsVal, IbVal, IaVal, instWriteStrat);
        instCacheGeneric = instCache;
        
    }else if(Is || Ib || Ia){
        cout << "Error: must include all of Is, Ib, Ia or none of them" << endl;
        exit(1);
    }else{
        //If there is NO instruction case
        instCache = NULL;
        instCacheGeneric = memorySystem;
    }
    
    /*
     =============== Data Cache Configuration ===============
     */
    
    if(Ds && Db && Da){
        //If there IS a data cache
        DsVal = Ds->getArgPwr2(0);
        DbVal = Db->getArgPwr2(0);
        if(Da->getArgStr(0) == "full"){
            DaVal = DsVal * 1024 / DbVal; //Calculate full associativity = number of blocks in total
        }else{
            DaVal = Da->getArgPwr2(0);
        }
        
        if(DsVal == -1 || DbVal == -1 || DaVal == -1){
            cout << "Error: -Ds, -Db, -Da must be powers of two" << endl;
        }
        
        if((!Dwt && !Dwb) || (Dwt && Dwb)){
            cout << "Error: must include exactly one of -Dwt or -Dwb" << endl;
            exit(1);
        }
        
        if(Dwt){
            dataWriteStrat = WRITE_THROUGH_AROUND;
        }else{
            dataWriteStrat = WRITE_BACK_ALLOCATE;
        }
        
        
        dataCache = new CacheFlex(memorySystem, DsVal, DbVal, DaVal, dataWriteStrat);
        dataCacheGeneric = dataCache;
        
    }else if(Ds || Db || Da){
        cout << "Error: must include all of Ds, Db, Da or none of them" << endl;
        exit(1);
    }else{
        //If there is NO data case
        dataCache = NULL;
        dataCacheGeneric = memorySystem;
    }
    
    
    //Setup main environment
    
    MipsInterpreter mipsInterpreter(instCacheGeneric, dataCacheGeneric);
    addInstructionsToInterpreter(mipsInterpreter);
    
    if(g_verbose){
        memorySystem->setVerbose(true);
        mipsInterpreter.setVerbose(true);
    }
    
    //Continually get lines of std input until an "end of file" character is received
    do {
        string cmdStr;
        std::getline(std::cin,cmdStr);
        removeComment(cmdStr);                              //Strip comments with #
        padEquals(cmdStr);                                  //Pad equals signs with spaces
        vector<string> cmdVec = explode(cmdStr, " \n\r");   //Tokenize command string
        
        if(g_verbose){
            cout << "Command Breakdown: " << endl;
            printStrVector(cmdVec);
        }
        
        //Accept input and interpret commands
        if(cmdVec.size() > 0){
            bool executeSuccess = false;
            //If we have a 1 or 3 length cmdVec with 'r' at the start
            if(cmdVec[0][0] == 'r' && (cmdVec.size() == 1 || cmdVec.size() == 3)){
                string regNumStr = cmdVec[0].substr(1, string::npos);
                unsigned int regNumInt;
                if(decStrToInt(regNumStr, regNumInt)){
                    //"rn" - print reg rn
                    if(cmdVec.size() == 1){
                        cout << hex << setw(8) << setfill('0') << mipsInterpreter.getCore()->getRegUns(regNumInt) << endl;
                        executeSuccess = true;
                    //"rn = value" - set register n to value (in hex)
                    }else if(cmdVec[1] == "="){
                        unsigned int regVal;
                        if(hexStrToInt(cmdVec[2], regVal)){
                            mipsInterpreter.getCore()->setRegUns(regNumInt, regVal);
                            executeSuccess = true;
                        }
                    }
                }
            //"m address"
            }else if(cmdVec[0] == "m" && cmdVec.size() == 2){
                unsigned int memAddress;
                if(hexStrToInt(cmdVec[1], memAddress)){
                    WordTransfer wordRetr(memAddress);
                    memorySystem->retrieveWord(wordRetr);
                    cout << hex << setw(8) << setfill('0') << wordRetr.data << endl;
                    executeSuccess = true;
                }
            //"m address = value"
            }else if(cmdVec[0] == "m" && cmdVec.size() == 4){
                unsigned int memAddress;
                unsigned int memValue;
                if(hexStrToInt(cmdVec[1], memAddress) && hexStrToInt(cmdVec[3], memValue) && cmdVec[2] == "="){
                    WordTransfer wordSet(memAddress, memValue);
                    memorySystem->setWord(wordSet);
                    executeSuccess = true;
                }
            //"pc"
            }else if(cmdVec[0] == "pc" && cmdVec.size() == 1){
                cout << hex << setw(8) << setfill('0') << mipsInterpreter.getCore()->getPc() << endl;
                executeSuccess = true;
            //"pc = address"
            }else if(cmdVec[0] == "pc" && cmdVec.size() == 3){
                unsigned int pcAddress;
                if(hexStrToInt(cmdVec[2], pcAddress) && cmdVec[1] == "="){
                    mipsInterpreter.getCore()->setPc(pcAddress);
                    executeSuccess = true;
                }
            //"." - Execute one instruction
            }else if(cmdVec[0] == "." && cmdVec.size() == 1){
                mipsInterpreter.fetchAndInterpret(1);
                executeSuccess = true;
            //". n" - Execute n instructions
            }else if(cmdVec[0] == "." && cmdVec.size() == 2){
                unsigned int numInstrs;
                if(decStrToInt(cmdVec[1], numInstrs)){
                    mipsInterpreter.fetchAndInterpret(numInstrs);
                    executeSuccess = true;
                }
            }else if(cmdVec[0] == "pi" && cmdVec.size() == 2){
                unsigned int address;
                if(hexStrToInt(cmdVec[1], address)){
                    cout << "Probe instruction cache" << endl;
                    
                    
                     
                    executeSuccess = true;
                }
            }else if(cmdVec[0] == "pd" && cmdVec.size() == 2){
                unsigned int address;
                if(hexStrToInt(cmdVec[1], address)){
                    cout << "Probe data cache" << endl;
                    
                    
                    
                    executeSuccess = true;
                }
            }
            
            
            //If no command was matched, then print warning
            if(!executeSuccess){
                if(g_verbose){
                    cout << "Sorry command not recognized!" << endl;
                }
            }
        }
    }while(!cin.eof());
    
    //Print statistics before exiting
    mipsInterpreter.printStats();
    
    return 0;
}




