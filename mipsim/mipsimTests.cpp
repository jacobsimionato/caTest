//
//  mipsimTests.cpp
//  mipsim
//  Computer Architecture Assignment 1 2014
//  Jacob Simionato a1175808

#include <iostream>
#include <string>
#include <sys/time.h>
#include <iomanip>
#include <cstring>

#include "mipsimTests.h"
#include "mipSimPerformance.h"
#include "cmdLineOption.h"
using namespace std;

/*
 =============== Testing framework ===============
 If the first two arguments are equal test is passes and passed tally is incremented
 If the first two argumnets are not equal, test fails and a description is printed
 */
//Global variables to store overall test statistics
int numTestsPassed = 0;
int numTestsFailed = 0;
bool reportPassedEnable = true; //If set to false, then tests will only be reported if they fail

/*
 Booleans
 */
bool assert(bool result, bool expected, string description){
    bool passed = result == expected;
    if(passed){
        numTestsPassed++;
        if(reportPassedEnable){
            cout << "Test Passed: '" << description << "'" << endl;
        }
    }else{
        cout << "Test FAILED: '" << description << "'" << endl;
        cout << "     -> expected " << expected << " but result was " << result << endl;
        numTestsFailed++;
    }
    return passed;
}

/*
 Strings
 */
bool assert(string result, string expected, string description){
    bool passed = result == expected;
    if(passed){
        numTestsPassed++;
        if(reportPassedEnable){
            cout << "Test Passed: '" << description << "'" << endl;
        }
    }else{
        cout << "Test FAILED: '" << description << "'" << endl;
        cout << "     -> Expected '" << expected << "' but result was '" << result << "'" << endl;
        numTestsFailed++;
    }
    return passed;
}

/*
 Integers
 */
bool assert(int result, int expected, string description){
    bool passed = result == expected;
    if(passed){
        numTestsPassed++;
        if(reportPassedEnable){
            cout << "Test Passed: '" << description << "'" << endl;
        }
    }else{
        cout << "Test FAILED: '" << description << "'" << endl;
        cout << "     -> Expected '" << expected << "' but result was '" << result << "'" << endl;
        numTestsFailed++;
    }
    return passed;
}

/*
 Unsigned Integers
 */
bool assert(unsigned int result, unsigned int expected, string description){
    bool passed = result == expected;
    if(passed){
        numTestsPassed++;
        if(reportPassedEnable){
            cout << "Test Passed: '" << description << "'" << endl;
        }
    }else{
        cout << "Test FAILED: '" << description << "'" << endl;
        cout << "     -> Expected '" << expected << "' but result was '" << result << "'" << endl;
        numTestsFailed++;
    }
    return passed;
}

/*
 =============== Test suite ===============
 Unit tests for many of the mipsim components. Higher level functionality and integration testing, including correct interpretation of binary instructions is handled by external test suites
 */
//Run the entire testing suite
void runMipsimTests(){
    numTestsFailed = 0;
    numTestsPassed = 0;
    
    //Run each section of test suite
    runPatternMatchersTests();
    runMipsInterpreterTests();
    runMemorySystemTests();
    runCmdLineOptionTests();
    //Report results
    cout << endl;
    cout << numTestsPassed << " tests PASSED" << endl;
    cout << numTestsFailed << " tests FAILED" << endl;
}

//Run pattern matcher tests
void runPatternMatchersTests(){
    unsigned int decStrVal;
    bool decStrReturnVal = decStrToInt("2959244", decStrVal);
    assert(decStrVal, (unsigned int) 2959244, "Check decStrVal value for valid use");
    assert(decStrReturnVal, true, "Check decStrVal return result for valid use");
    decStrReturnVal = decStrToInt("2959f244", decStrVal);
    assert(decStrReturnVal, false, "Check decStrVal return result for invalid use");
    
    
    unsigned int hexStrVal;
    bool hexStrReturnVal = hexStrToInt("00028f", hexStrVal);
    assert(hexStrVal, (unsigned int) 655, "Check hexStrVal value for valid use");
    assert(hexStrReturnVal, true, "Check hexStrVal return result for valid use");
    hexStrReturnVal = hexStrToInt("37f2r3", hexStrVal);
    assert(hexStrReturnVal, false, "Check hexStrVal return result for invalid use");
    
    hexStrReturnVal = hexStrToInt("80000000", hexStrVal);
    assert(hexStrVal, 2147483648, "Check hexStrVal value for huge int");
    assert(hexStrReturnVal, true, "Check hexStrVal return result for huge int");
    
    
    
    bool inCharsResult = isInChars(' ', "\n919 \r");
    assert(inCharsResult, true, "isInChars space amongst trash");
    
    inCharsResult = isInChars(' ', "\n919\r");
    assert(inCharsResult, false, "isInChars no space amongst trash");
    
    inCharsResult = isInChars('\r', "\n919 \r");
    assert(inCharsResult, true, "isInChars end special case");
    
    inCharsResult = isInChars('\n', "\n919 \r");
    assert(inCharsResult, true, "isInChars start special case");
    
    inCharsResult = isInChars('r', "2929933r23923992");
    assert(inCharsResult, true, "isInChars chars long case");
    
    inCharsResult = isInChars('f', "lsldlj;aj;\n\rhhkf");
    assert(inCharsResult, true, "isInChars end after special chars");
    
    inCharsResult = isInChars('5', "lsldlj;aj;\n\rhhkf");
    assert(inCharsResult, false, "isInChars doesn't exist with special chars");
    
    string commentText = "abcdef#ghi";
    removeComment(commentText);
    assert(commentText, "abcdef", "removeComment with valid comment");
    
    commentText = "abcdefghi";
    removeComment(commentText);
    assert(commentText, "abcdefghi", "removeComment with no valid comment");
    
    commentText = "abcde  $ fghi";
    removeComment(commentText, '$');
    assert(commentText, "abcde  ", "removeComment with custom separator");
    
    
    string equalsText = "  something=another";
    padEquals(equalsText);
    assert(equalsText, "  something = another", "padEquals simple case");
    equalsText = "abcdef123456!@#$%^";
    padEquals(equalsText);
    assert(equalsText, "abcdef123456!@#$%^", "padEquals no equals case");
    equalsText = "=first = second=third  =  fourth";
    padEquals(equalsText);
    assert(equalsText, " = first  =  second = third   =   fourth", "padEquals several equals");
    
    vector<string> exploded = explode("   word1 word2  ", " ");
    assert(static_cast<int>(exploded.size()), static_cast<int>(2), "explode correct number of words simple case");
    if(exploded.size()>=2){
        assert(exploded[0], "word1", "explode first word simple case");
        assert(exploded[1], "word2", "explode second word simple case");
    }
    
    exploded = explode("word1 word2   sc sss #*$", " s");
    assert(static_cast<int>(exploded.size()), static_cast<int>(4), "explode correct number of words complex case");
    if(exploded.size()>=4){
        assert(exploded[0], "word1", "explode first word");
        assert(exploded[1], "word2", "explode second word");
        assert(exploded[2], "c", "explode third word");
        assert(exploded[3], "#*$", "explode fourth word");
    }
    
}

//Run mipsInterpreter tests
void runMipsInterpreterTests(){
    MemorySystem memorySystem(0,0); //Memory system with no penalties
    MipsInterpreter mipsInterpreter(&memorySystem, &memorySystem);
    addInstructionsToInterpreter(mipsInterpreter);
    
    //Check all register values are initialized as zero
    unsigned int regSums = 0;
    for(int i=0; i<32; i++){
        regSums += mipsInterpreter.getCore()->getRegUns(i);
    }
    assert(regSums, (unsigned int) 0, "check regs are initialized as zero");
    assert(mipsInterpreter.getCore()->getPc(), (unsigned int) 0, "check PC is initialized as zero");
    
    //Initialize memory with a couple of add instructions to test execution
    WordTransfer wordTransfer1(0x80000, genInstAdd(1, 2, 3));
    memorySystem.setWord(wordTransfer1);
    WordTransfer wordTransfer2(0x80004, genInstAdd(1, 2, 3));
    memorySystem.setWord(wordTransfer2);
    mipsInterpreter.getCore()->setPc(0x80000);
    mipsInterpreter.getCore()->resetCounts();
    
    //Test execution of instructions
    //Run first instruction
    int interpResult = mipsInterpreter.fetchAndInterpret(1);
    assert(mipsInterpreter.getCore()->getRegUns(3), (unsigned int) 0, "check 0+0 = 0");
    assert(mipsInterpreter.getCore()->getPc(), (unsigned int) 0x80004, "check pc inc 4 after one instruction");
    assert(interpResult, 0, "check interpreter returns 0 under normal operation");
    assert(mipsInterpreter.getCore()->getInstrCount(), 1, "instruction count after add");
    assert(mipsInterpreter.getCore()->getCycleCount(), 4, "cycle count after add");
    //Run second instruction
    mipsInterpreter.getCore()->setRegUns(1, 4564);
    mipsInterpreter.getCore()->setRegUns(2, 1123434);
    interpResult = mipsInterpreter.fetchAndInterpret(1);
    
    assert(mipsInterpreter.getCore()->getInstrCount(), 2, "instruction count after two adds");
    assert(mipsInterpreter.getCore()->getCycleCount(), 8, "cycle count after two adds");
    
    assert(mipsInterpreter.getCore()->getRegUns(3), (unsigned int) 1127998, "check 0+0 = 1127998");
    assert(mipsInterpreter.getCore()->getPc(), (unsigned int) 0x80008, "check pc inc 8 after two instructions");
    assert(interpResult, 0, "check interpreter returns 0 under normal operation");
    
    mipsInterpreter.getCore()->resetCounts();
    assert(mipsInterpreter.getCore()->getInstrCount(), 0, "instruction count zeroed after reset");
    assert(mipsInterpreter.getCore()->getCycleCount(), 0, "cycle count zeroed after reset");
    
    WordTransfer wordTransfer3(0x0, 0xFFFFFFFF);
    memorySystem.setWord(wordTransfer3);
    mipsInterpreter.getCore()->setPc(0x0);
    interpResult = mipsInterpreter.fetchAndInterpret(1);
    assert(interpResult, 1, "check interpreter returns 1 for invalid instruction");
}

//Run memorySystem tests
void runMemorySystemTests(){
    MemorySystem memorySystem(0,0);
    
    WordTransfer wordRetr1(0x283828);
    memorySystem.retrieveWord(wordRetr1);
    assert(wordRetr1.data, (unsigned int) 0, "Check memory 0x283828 initialized to zero");
    
    WordTransfer wordRetr2(0xFFFFFFFF);
    memorySystem.retrieveWord(wordRetr2);
    assert(wordRetr2.data, (unsigned int) 0, "Check memory 0xFFFFFFFF initialized to zero");
    
    
    WordTransfer wordSend1(0x0, 0x456);
    memorySystem.setWord(wordSend1);
    WordTransfer wordSend2(0x4, 0x4);
    memorySystem.setWord(wordSend2);
    WordTransfer wordSend3(0x8, 0x8);
    memorySystem.setWord(wordSend3);
    WordTransfer wordSend4(0x283828, 0x283828);
    memorySystem.setWord(wordSend4);
    WordTransfer wordSend5(0xFFFFFFFC, 0xFFFFFFFC);
    memorySystem.setWord(wordSend5);
    WordTransfer wordSend6(0xFFFFFFF0, 0xFFFFFFF0);
    memorySystem.setWord(wordSend6);
    
    
    WordTransfer wordRetr3(0x0);
    memorySystem.retrieveWord(wordRetr3);
    assert(wordRetr3.data, (unsigned int) 0x456, "Check memory 0x0 set correctly");
    
    WordTransfer wordRetr4(0x4);
    memorySystem.retrieveWord(wordRetr4);
    assert(wordRetr4.data, (unsigned int) 0x4, "Check memory 0x4 set correctly");
    
    WordTransfer wordRetr41(0x8);
    memorySystem.retrieveWord(wordRetr41);
    assert(wordRetr41.data, (unsigned int) 0x8, "Check memory 0x8 set correctly");
    
    WordTransfer wordRetr5(0x283828);
    memorySystem.retrieveWord(wordRetr5);
    assert(wordRetr5.data, (unsigned int) 0x283828, "Check memory 0x283828 set correctly");
    
    WordTransfer wordRetr6(0xFFFFFFFC);
    memorySystem.retrieveWord(wordRetr6);
    assert(wordRetr6.data, (unsigned int) 0xFFFFFFFC, "Check memory 0xFFFFFFFC set correctly");
    
    WordTransfer wordRetr7(0xFFFFFFF0);
    memorySystem.retrieveWord(wordRetr7);
    assert(wordRetr7.data, (unsigned int) 0xFFFFFFF0, "Check memory 0xFFFFFFF0 set correctly");
    
    WordTransfer wordRetr8(0xFFFFFFF8);
    memorySystem.retrieveWord(wordRetr8);
    assert(wordRetr8.data, (unsigned int) 0x0, "Check memory 0xFFFFFFF8 has not been touched");
    
    WordTransfer wordRetr9(0xFFFFFFF4);
    memorySystem.retrieveWord(wordRetr9);
    assert(wordRetr9.data, (unsigned int) 0x0, "Check memory 0xFFFFFFF4 has not been touched");
}

void runCmdLineOptionTests(){
    const char* mockArgv[] = {"-t", "-Ib", "3454", "2048", "dk", "-Ds", "sd", "-Ma", "3454", "-Db", "1024"};
    int mockArgc = sizeof(mockArgv)/sizeof(mockArgv[0]);
    cmdLineOption::clearAllOptions();
    cmdLineOption::parseCmdLineOptions(mockArgc, mockArgv);
    
    cmdLineOption* curOpt;
    curOpt = cmdLineOption::findOpt("-Ds");
    assert(curOpt != NULL, true, "existing cmd line option -Ds is found");
    if(curOpt!=NULL){
        assert(curOpt->getNumArgs(), 1, "-Ds has correct number of args");\
        assert(curOpt->getArgStr(0), "sd", "correct string argument for -Ds");
        assert(curOpt->getArgPosInt(0), -1, "-1 returned when trying to interpret string as int");
    }
    
    curOpt = cmdLineOption::findOpt("-Ib");
    assert(curOpt != NULL, true, "existing cmd line option -Ib is found");
    if(curOpt!=NULL){
        assert(curOpt->getNumArgs(), 3, "-Ds has correct number of args");\
        assert(curOpt->getArgStr(2), "dk", "correct string argument for -Ds");
        assert(curOpt->getArgStr(0), "3454", "get integer argument as str");
        assert(curOpt->getArgPosInt(0), 3454, "get integer argument as int");
        assert(curOpt->getArgPwr2(0), -1, "get non pwr 2 integer argument as pwr 2");
        assert(curOpt->getArgPwr2(1), 2048, "get integer argument");
    }
    
    curOpt = cmdLineOption::findOpt("-ds");
    assert(curOpt == NULL, true, "nonexistant -ds is not found");
    
    curOpt = cmdLineOption::findOpt("3454");
    assert(curOpt == NULL, true, "Check non-tag 3454 is not found but instead collected with previous tag");
    
    

}