//
//  patternMatchers.cpp
//  mipsim
//  Computer Architecture Assignment 1 2014
//  Jacob Simionato a1175808

#include "patternMatchers.h"

using namespace std;

//Takes a string and tokenizes it using the provided delimiters, returning a vector of strings representing each token
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

//Returns true if the input character matches any characters in the string. Used by explode to check for delimiters.
bool isInChars(char inputChar, string checkList){
    char curCheckChar;
    int curCheckPos = 0;
    //Iterate through string and check for inputChar
    do{
        curCheckChar = checkList[curCheckPos];
        if(inputChar == curCheckChar){
            //Return true immediately if there is a match
            return true;
        }
        curCheckPos++;
    }while(curCheckPos < checkList.length());
    return false;
}

//Takes an input string and checks if there is a comment at the end of the line indicated by the provided separator character. If a comment is found, the string is truncated to remove it.
void removeComment(string &input, char separator){
    int index = 0;
    char curChar = 0;
    //Search through string for the first ocurrence of the separator character
    do{
        curChar = input[index];
        index++;
    }while(curChar != separator && index < input.length());
    //If a separator was found, then truncate string
    if(curChar == separator){
        input.resize(index-1);
    }
}

//Takes an input string and returns a new string where each equals sign in the string has a space character inserted immediately before and after it. eg "num=5" becomes "num = 5"
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


/*
 Helper functions for decStrToInt and hexStrToInt
 */
//Returns true if input is a numeral
bool isNum(char input){
    return input >= '0' && input <= '9';
}

//Returns true if input is an uppercase letter hex digit
bool isUpperHex(char input){
    return input >= 'A' && input <= 'F';
}

//Returns true if input is a lower case letter hex digit
bool isLowerHex(char input){
    return input >= 'a' && input <= 'f';
}

//Returns true if input is a valid hex digit
bool isHex(char input){
    return isNum(input) || isUpperHex(input) || isLowerHex(input);
}

//Extracts numerical value of a single hex digit
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

//Attempts to convert a string containing hex digits to an integer
//If any of the digits are not valid hex, then we return false and do not set output
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

//Attempts to convert a string containing decimal digits to an integer
//If any of the digits are not valid numerals, then we return false and do not set output
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


/*
 =================== Pattern Matching Debug Helpers ===================
 */

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