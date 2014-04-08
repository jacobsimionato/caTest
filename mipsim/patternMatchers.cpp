//
//  patternMatchers.cpp
//  mipsim
//
//  Created by Jacob Simionato on 31/03/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//

#include "patternMatchers.h"

using namespace std;


bool isInChars(char inputChar, string checkList){
    char curCheckChar;
    int curCheckPos = 0;
    do{
        curCheckChar = checkList[curCheckPos];
        //cout << "checking " << inputChar << " vs " << curCheckChar;
        if(inputChar == curCheckChar){
            //cout << inputChar << " true!" << endl;
            return true;
        }else{
        }
        curCheckPos++;
    }while(curCheckPos < checkList.length());
    //cout << inputChar << " false!" << endl;
    return false;
}


void removeComment(string &input, char separator){
    int index = 0;
    char curChar = 0;
    do{
        curChar = input[index];
        index++;
    }while(curChar != separator && index < input.length());
    
    if(curChar == separator){
        input.resize(index-1);
    }
}

void padEquals(std::string &input){
    string output;
    for(int i=0; i<input.length(); i++){
        char curChar = input[i];
        if(curChar == '='){
            output.push_back(' ');
            output.push_back('=');
            output.push_back(' ');
        }else{
            output.push_back(curChar);
        }
    }
    input = output;
}

vector<string> explode(std::string input, string separators){
    vector<string> output;
    int start = -1;
    int end;
    while(1){
        char startChar = 0;
        //Look for a new starting position
        do{
            start++;
            startChar = input[start];
        }while(isInChars(startChar, separators) && start < input.length());
        
        //Finish the process if we don't find any new starting position
        if(start >= input.length()){
            break;
        }
    
        //Look for ending position
        char endChar = 0;
        end = start;
        do{
            end++;
            endChar = input[end];
        }while((!isInChars(endChar, separators)) && end < input.length());
        
        //add string segment to output vector
        string newSegmentStr = input.substr(start, end-start);
        output.push_back(newSegmentStr);
        
        //Finish the process if end is right at the end
        if(end >= input.length()){
            break;
        }
        
        start = end - 1;
    }
    return output;
}

void printStrVector(const std::vector<std::string> input){
    for(int i = 0; i<input.size(); i++){
        cout << i << ": " << input[i];
        cout << " - length = " << input[i].length() << " chars" << endl;
    }
}

void printStrInts(const std::string input){
    cout << "String as numbers: ";
    for(int i=0; i<input.length(); i++){
        int charInt = input[i];
        cout << dec << charInt << " ";
    }
    cout << endl;
}

//int decStrToInt(string input){
//    int x;
//    stringstream ss;
//    ss << input;
//    ss >> x;
//    return x;
//}
//
//int hexStrToInt(string input){
//    int x;
//    stringstream ss;
//    ss << std::hex << input;
//    ss >> x;
//    return x;
//}

/*
 Helper functions for decStrToInt and hexStrToInt
 */
bool isNum(char input){
    return input >= '0' && input <= '9';
}

bool isUpperHex(char input){
    return input >= 'A' && input <= 'F';
}

bool isLowerHex(char input){
    return input >= 'a' && input <= 'f';
}

bool isHex(char input){
    return isNum(input) || isUpperHex(input) || isLowerHex(input);
}

int hexDigVal(char input){
    if(isNum(input)){
        return input - '0';
    }else if(isUpperHex(input)){
        return input - 'A' + 10;
    }else if(isLowerHex(input)){
        return input - 'a' + 10;
    }
    return -1;
}


bool hexStrToInt(const std::string &input, unsigned int &output){
    unsigned int accum = 0;
    int pos = 0;
    while(isHex(input[pos]) && pos < input.length() ){
        char curChar = input[pos];
        accum *= 16;
        accum += hexDigVal(curChar);
        pos++;
    }
    //Return false if part of the string could not be converted
    if(pos < input.length()){
        return false;
    }
    output = accum;
    return true;
}

bool decStrToInt(const std::string &input, unsigned int &output){
    unsigned int accum = 0;
    int pos = 0;
    while(isNum(input[pos]) && pos < input.length()){
        char curChar = input[pos];
        accum *= 10;
        accum += curChar - '0';
        pos++;
    }
    output = accum;
    //Return false if part of the string could not be converted
    if(pos < input.length()){
        return false;
    }
    return true;
}












bool parseRegExp(string inputLine, string instrPatternString, vector<string> &result){
    regex instrPattern(instrPatternString);
    smatch instrMatch;
    //cout << "attempting to match for '" << inputLine << endl;
    
    bool searchSuccess = regex_search(inputLine, instrMatch, instrPattern);
    if(searchSuccess){
        for (size_t i = 0; i < instrMatch.size(); i++) {
            string resultStr = instrMatch[i].str();
            if(resultStr.length() == 0){
                return 0;
            }
            result.push_back(resultStr);
            //cout << i << ": " << instrMatch[i].str() << endl;
        }
    }else{
        return 0;
    }
    return 1;
}






bool saveCharImmediate(std::string &input, int &pos, std::vector<int> &output){
    output.push_back(input[pos]);
    pos++;
    //Avoid pos overrun and return false if we are at end of line
    if(pos >= input.length()){
        return false;
    }
    return true;
}
//to find inital character

//Returns true if next immedaite char is given char. Advances if it is, doesn't advance if not
bool checkCharImmediate(std::string &input, int &pos, char checkChar){
    if(input[pos] == checkChar){
        pos++;
        return true;
    }
    return false;
}


//Returns 1 if equals found, 0 if not
bool checkAdvanceEquals(std::string &input, int &pos){
    advancePastWhiteSpace(input, pos);
    bool output = checkCharImmediate(input, pos, '=');
    if(output == true){
        advancePastWhiteSpace(input, pos);
    }
    return output;
}

bool advancePastWhiteSpace(std::string &input, int pos){
    while(pos < input.length()){
        if(pos >= input.length() - 1){
            return false;
        }
        char curChar = input[pos];
        //If it is not whitespace
        if(curChar > 15 && curChar!=32){
            return true;
        }
        pos++;
    }
    if(pos >= input.length() - 1){
        pos = input.length() - 1;
    }
    return false;
}//returns false if we reach end of line

/*
std::vector<int> parseInput(std::string input){
    vector<int> output;
    vector<int> blank;
    int pos = 0;
    if(!advancePastWhiteSpace(input, pos)){
        return blank;
    }
    if(!saveCharImmediate(input, pos, output)){
        return output;
    }
    switch(output[0]){
        case 'r':
            saveDecImmediate(input, pos, output);
            break;
        case 'p':
            if(!checkCharImmediate(input, pos, 'c')){
                return blank;
            }
        case 'm':
            if(!advancePastWhiteSpace(input, pos)){
                return blank;
            };
            saveHexImmediate(input, pos, output);
            break;
        case '.':
            if(!advancePastWhiteSpace(input, pos)){
                return output;
            }
            saveCharImmediate(input, pos, output);
    }
    return output;
}
*/