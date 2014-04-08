//
//  mipsimTests.cpp
//  mipsim
//
//  Created by Jacob Simionato on 8/04/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//

#include <iostream>
#include <string>
#include <sys/time.h>
#include <iomanip>
#include <cstring>

#include "mipsimTests.h"

using namespace std;

int numTestsPassed = 0;
int numTestsFailed = 0;
bool reportPassedEnable = true;

void runMipsimTests(){
    numTestsFailed = 0;
    numTestsPassed = 0;
    runPatternMatchersTests();
    cout << endl;
    cout << numTestsPassed << " tests PASSED" << endl;
    cout << numTestsFailed << " tests FAILED" << endl;
}

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
    assert(exploded.size(), 2, "explode correct number of words simple case");
    if(exploded.size()>=2){
        assert(exploded[0], "word1", "explode first word simple case");
        assert(exploded[1], "word2", "explode second word simple case");
    }
    
    exploded = explode("word1 word2   sc sss #*$", " s");
    assert(exploded.size(), 4, "explode correct number of words complex case");
    if(exploded.size()>=4){
        assert(exploded[0], "word1", "explode first word");
        assert(exploded[1], "word2", "explode second word");
        assert(exploded[2], "c", "explode third word");
        assert(exploded[3], "#*$", "explode fourth word");
    }
    
}

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