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

using namespace std;


int main(int argc, const char * argv[]){
    //Determines whether the
    bool g_verbose = false;
    
    //Parse command line arguments
    if(argc > 1){
        
        cmdLineOption::defineNew("-t");
        cmdLineOption::defineNew("-v");
        cmdLineOption::defineNew("-p");
        cmdLineOption::defineNew("-Is", 1);
        cmdLineOption::defineNew("-Ib", 1);
        cmdLineOption::defineNew("-Ia", 1);
        cmdLineOption::defineNew("-Ds", 1);
        cmdLineOption::defineNew("-Db", 1);
        cmdLineOption::defineNew("-Da", 1);
        cmdLineOption::defineNew("-Dwt");
        cmdLineOption::defineNew("-Dwb");
        cmdLineOption::defineNew("-Ma", 1);
        cmdLineOption::defineNew("-Mw", 1);

        cmdLineOption::parseCmdLineOptions(argc, argv);
        cmdLineOption::printAll();

    
        if( cmdLineOption::checkOption("-v")->wasFound()){
            //Enable verbose mode
            g_verbose = true;
        }
        if( cmdLineOption::checkOption("-t")->wasFound()){
            //Run unit testing suite and then exit
            cout << "running tests" << endl;
            runMipsimTests();
        }
        if( cmdLineOption::checkOption("-p")->wasFound()){
            //Run execution speed tests and then exit
            testExecutionSpeedPerformance();
            testMemoryPerformance();
        }
        
        if(cmdLineOption::checkOption("-t")->wasFound() || cmdLineOption::checkOption("-p")->wasFound()){
            exit(0);
        }

    
        
        exit(0);
        
    }
    
    //Setup main environment
    MemorySystem memorySystem;
    MipsInterpreter mipsInterpreter(&memorySystem);
    addInstructionsToInterpreter(mipsInterpreter);
    
    if(g_verbose){
        memorySystem.setVerbose(true);
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
                    cout << hex << setw(8) << setfill('0') << memorySystem.retrieveWord(memAddress) << endl;
                    executeSuccess = true;
                }
            //"m address = value"
            }else if(cmdVec[0] == "m" && cmdVec.size() == 4){
                unsigned int memAddress;
                unsigned int memValue;
                if(hexStrToInt(cmdVec[1], memAddress) && hexStrToInt(cmdVec[3], memValue) && cmdVec[2] == "="){
                    memorySystem.setWord(memAddress, memValue);
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




