//
//  main.cpp
//  mipsim
//
//  Created by Jacob Simionato on 30/03/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//


/*TODO
 -Add checking for out of range block address
 -Add commments
 -Add tests for basic core functionality
 -Assume tests are already written for higher-level functionality eg interpreting instructions
 */

#include <iostream>
#include <string>
#include <sys/time.h>
#include <iomanip>
#include <cstring>

#include "memorySystem.h"
#include "mipsInterpreter.h"
#include "mipsInstructionFunctions.h"
#include "patternMatchers.h"
#include "debugHelperFunctions.h"
#include "mipSimPerformance.h"
#include "mipsimTests.h"


using namespace std;

bool g_verbose = false;



int main(int argc, const char * argv[]){
    
    //Use args to stuff up and run tests
    if(argc > 1){
        for(int argNum = 1; argNum < argc; argNum++){
            if(strcmp(argv[1], "-v") == 0){
                //Verbose mode
                g_verbose = true;
            }else if(strcmp(argv[1], "-p") == 0){
                testArithmeticPerformance();
                testExecutionSpeedPerformance();
                testMemoryPerformance();
            }else if(strcmp(argv[1], "-t") == 0){
                runMipsimTests();
            }
        }
    }
    
    //Setup main environment
    MemorySystem memorySystem;
    MipsInterpreter mipsInterpreter(&memorySystem);
    addInstructionsToInterpreter(mipsInterpreter);
    
    //int hexInt;
    //string input = "Ff";
    //bool success = hexStrToInt(input, hexInt);
    //cout << "hex str FF success: " << success << " and result: " << hexInt << endl;
    //g_verbose = false;
    do {
        string cmdStr;
        std::getline(std::cin,cmdStr);
        removeComment(cmdStr);
        padEquals(cmdStr);
        vector<string> cmdVec = explode(cmdStr, " \n\r");
        //
        if(g_verbose || false){
            //cout << endl;
            cout << cmdStr << endl;
            //cout << "Command Breakdown: " << endl;
            //printStrVector(cmdVec);
            //printStrInts(cmdStr);
        }
        
        if(cmdVec.size() > 0){
            bool executeSuccess = false;
            //If we have a 1 or 3 length cmdVec with 'r' at the start
            if(cmdVec[0][0] == 'r' && (cmdVec.size() == 1 || cmdVec.size() == 3)){
                string regNumStr = cmdVec[0].substr(1, string::npos);
                unsigned int regNumInt;
                if(decStrToInt(regNumStr, regNumInt)){
                    if(cmdVec.size() == 1){
                        //"rn" - print reg rn
                        cout << hex << setw(8) << setfill('0') << mipsInterpreter.getCore()->getRegUns(regNumInt) << endl;
                        executeSuccess = true;
                    }else if(cmdVec[1] == "="){
                        unsigned int regVal;
                        if(hexStrToInt(cmdVec[2], regVal)){
                            //"rn = value" - set register n to value (in hex)
                            mipsInterpreter.getCore()->setRegUns(regNumInt, regVal);
                            executeSuccess = true;
                        }
                    }
                }
            }else if(cmdVec[0] == "m" && cmdVec.size() == 2){
                unsigned int memAddress;
                if(hexStrToInt(cmdVec[1], memAddress)){
                    //"m address"
                    cout << hex << setw(8) << setfill('0') << memorySystem.retrieveWord(memAddress) << endl;
                    executeSuccess = true;
                }
            }else if(cmdVec[0] == "m" && cmdVec.size() == 4){
                unsigned int memAddress;
                unsigned int memValue;
                if(hexStrToInt(cmdVec[1], memAddress) && hexStrToInt(cmdVec[3], memValue) && cmdVec[2] == "="){
                    //"m address = value"
                    memorySystem.setWord(memAddress, memValue);
                    executeSuccess = true;
                }
            }else if(cmdVec[0] == "pc" && cmdVec.size() == 1){
                //"pc"
                cout << hex << setw(8) << setfill('0') << mipsInterpreter.getCore()->getPc() << endl;
                executeSuccess = true;
            }else if(cmdVec[0] == "pc" && cmdVec.size() == 3){
                unsigned int pcAddress;
                if(hexStrToInt(cmdVec[2], pcAddress) && cmdVec[1] == "="){
                    //"pc = address"
                    mipsInterpreter.getCore()->setPc(pcAddress);
                    executeSuccess = true;
                }
            }else if(cmdVec[0] == "." && cmdVec.size() == 1){
                //"." - Execute one instruction
                mipsInterpreter.fetchAndInterpret(1);
                executeSuccess = true;
            }else if(cmdVec[0] == "." && cmdVec.size() == 2){
                unsigned int numInstrs;
                if(decStrToInt(cmdVec[1], numInstrs)){
                    //". n" - Execute n instructions
                    mipsInterpreter.fetchAndInterpret(numInstrs);
                    executeSuccess = true;
                }
            }
            
            if(!executeSuccess){
                if(g_verbose){
                    cout << "Sorry command not recognized!" << endl;
                }
            }
        }
         
         
         
        
    }while(!cin.eof());
    mipsInterpreter.printStats();
    
    return 0;
}




